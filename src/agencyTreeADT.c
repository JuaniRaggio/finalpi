#include <errno.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include "../include/stackADT.h"
#include "../include/formats.h"
#include "../include/validIDADT.h"
#include "../include/errorManagement.h"
#include "../include/agencyTreeADT.h"
#include "../include/lib.h"

typedef struct LTicket {
    DTicket ticketData;
    struct LTicket * next;
} LTicket;

typedef struct LYear {
    DYear yearData;
    struct LYear * next;
} LYear;

typedef struct agency {
    char agencyName[AGENCY_LEN];
    LTicket * ticketList;
    LTicket * ticketIterator;
    LYear * firstYear;
    LYear * yearIterator;
} TAgency;

typedef struct node {
    TAgency * agencyData;
    size_t nodeHeight;
    struct node * left;
    struct node * right;
} TNode;

struct agencyTreeCDT {
    validIDADT validIDs;
    stackADT stack;
    TNode * root;
    TNode * inorderIterator;
    size_t agencyCounter;
};

static void freeBstRec(TNode * root);
static bool addYear(LYear ** firstYear, size_t year, size_t amount, size_t month);
static LYear * addYearRec(LYear * firstYear, size_t year, size_t amount, size_t month, bool * added);
static bool addTicket(validIDADT validIDs, LTicket ** firstTicket, unsigned char id);
static LTicket * addTicketRec(validIDADT validIDs, LTicket * firstTicket, unsigned char id, bool * added);
static void addHeight( TNode * vec, size_t dim );
static int balanceFactor ( TNode * root );
static unsigned int nodeHeight(TNode * node);
static TNode * rightRotate(TNode *y);
static TNode * leftRotate(TNode *x);
static void freeBstRec(TNode * root);

static LTicket * addTicketRec(validIDADT validIDs, LTicket * firstTicket, unsigned char id, bool * added) {
    int c;
    if ( firstTicket == NULL || (c = compareIDsDescription(validIDs, firstTicket->ticketData.id, id)) < 0 ) {
        LTicket * new = malloc(sizeof(LTicket));
        new->ticketData.id = id;
        new->ticketData.units = 1;
        new->next = firstTicket;
        (*added) = true;
        return new;
    } else if (c > 0) {
        firstTicket->next = addTicketRec(validIDs, firstTicket->next, id, added);
    }
    (*added) = false;
    return firstTicket;
}

static bool addTicket(validIDADT validIDs, LTicket ** firstTicket, unsigned char id){
    errno = NOERRORSFOUND;
    assert(validIDs == NULL, NULLARG, false);
    if (!isValidID(validIDs, id)) {
        return false;
    }
    bool added = false;
    *firstTicket = addTicketRec(validIDs, *firstTicket, id, &added);
    return true;
}

static LYear * addYearRec(LYear * firstYear, size_t year, size_t amount, size_t month, bool * added) {
    if (firstYear == NULL || (year > firstYear->yearData.yearN)) {
        LYear * newYear = malloc(sizeof(LYear));
        assert(newYear == NULL, ENOMEM, firstYear);
        newYear->yearData.yearN = year;
        newYear->yearData.collected[month-1] += amount;
        newYear->next = firstYear;
        (*added) = true;
        return newYear;
    } else if(year == firstYear->yearData.yearN){
        firstYear->yearData.collected[month-1] += amount; 
        (*added) = false;
        return firstYear;
    }
    firstYear->next = addYearRec(firstYear->next,year,amount,month,added);
    return firstYear;
}

static bool addYear(LYear ** firstYear, size_t year, size_t amount, size_t month) {
    errno = NOERRORSFOUND;
    assert(firstYear == NULL, NULLARG, false);
    if (amount == 0 || month > MONTHS || month == 0) {
        return false;
    }
    bool added = false;
    *firstYear = addYearRec(*firstYear, year, amount, month, &added);
    return added;
}

static void addHeight( TNode * vec, size_t dim ) {
    while ( dim > 0 ) {
        vec->nodeHeight++;
        dim--;
    }
}

static int balanceFactor ( TNode * root ) {
    return root->left->nodeHeight - root->right->nodeHeight;
} 

static TNode * insertAgencyRec(TNode * root, TNode ** added, char * agencyName, TTicket * tData, bool * newAgency) {
    if (root == NULL) {
        TNode * newNode = malloc(sizeof(TNode));
        assert(newNode == NULL, ENOMEM, NULL);
        newNode->agencyData = malloc(sizeof(TAgency));
        assert(newNode->agencyData == NULL, ENOMEM, NULL);
        myStrcpy(newNode->agencyData->agencyName, AGENCY_LEN, agencyName, SEPARATOR);
        newNode->agencyData->ticketList = NULL;
        newNode->agencyData->firstYear = NULL;
        newNode->left = newNode->right = NULL;
        newNode->nodeHeight = 1;
        *added = newNode;
        *newAgency = true;
        return newNode;
    }
    // VER SI LO SACAMOS
    /* assert(root->agencyData == NULL || root->agencyName == NULL, ); */
    int cmp = strncmp(agencyName, root->agencyData->agencyName, AGENCY_LEN);
    if (cmp < 0) {
        root->left = insertAgencyRec(root->left, added, agencyName, tData, newAgency);
    } else if (cmp > 0) {
        root->right = insertAgencyRec(root->right, added, agencyName, tData, newAgency);
    } else {
        *added = root;
        *newAgency = false;
        return root;
    }
    root->nodeHeight = max(nodeHeight(root->left), nodeHeight(root->right)) + 1;
    int balance = balanceFactor(root);
    if (balance > UPPERLIMIT && strcmp(agencyName, root->left->agencyData->agencyName) < 0) {
        return rightRotate(root);
    } else if (balance < LOWERLIMIT && strcmp(agencyName, root->right->agencyData->agencyName) > 0) {
        return leftRotate(root);
    } else if (balance > UPPERLIMIT && strcmp(agencyName, root->left->agencyData->agencyName) > 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    } else if (balance < LOWERLIMIT && strcmp(agencyName, root->right->agencyData->agencyName) < 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}

bool insertAgency(agencyTreeADT agency, char * agencyName, TTicket * tData) {
    errno = NOERRORSFOUND;
    assert(!isValidID(agency->validIDs, tData->infractionID), INVALIDARG, false);
    assert(agency == NULL || agencyName == NULL, NULLARG, false);
    bool added = false;
    TNode * addedAgency = NULL;
    agency->root = insertAgencyRec(agency->root, &addedAgency, agencyName, tData, &added);
    assert(errno != NOERRORSFOUND, errno, false);
    
    // Thread 1
    addTicket(agency->validIDs, &addedAgency->agencyData->ticketList, tData->infractionID);
    assert(errno != NOERRORSFOUND, errno, false);

    // Thread 2
    addYear(&addedAgency->agencyData->firstYear, tData->issueYear, tData->amount, tData->issueMonth);
    assert(errno != NOERRORSFOUND, errno, false);

    // ???
    agency->agencyCounter += added;

    return added;
}

void toBeginAgency(agencyTreeADT agency) {
    agency->stack = newStack(sizeof(TNode *));
    agency->inorderIterator = agency->root;
}

bool hasNextAgency(agencyTreeADT agency) {
    return agency->inorderIterator != NULL;
}

char * nextAgency(agencyTreeADT agency) {
    assert(agency == NULL || agency->stack == NULL || (!hasNextAgency(agency) && isEmpty(agency->stack)), NULLARG, NULL);
    char * retAgency = NULL;
    while (agency->inorderIterator != NULL) {
        push(agency->stack, agency->inorderIterator);
        agency->inorderIterator = agency->inorderIterator->left;
    }
    agency->inorderIterator = pop(agency->stack);
    if (agency->inorderIterator->agencyData != NULL) {
        retAgency = agency->inorderIterator->agencyData->agencyName;
    } else {
        return NULL;
    }
    retAgency = agency->inorderIterator->agencyData->agencyName;
    agency->inorderIterator = agency->inorderIterator->right;
    return retAgency;
}

void toBeginTicket(agencyTreeADT agency);
bool hasNextTicket(agencyTreeADT agency);
DTicket nextTicket(agencyTreeADT agency);

void toBeginYear(agencyTreeADT agency);
bool hasNextYear(agencyTreeADT agency);
DYear nextYear(agencyTreeADT agency);

agencyTreeADT newAgencys(validIDADT validInfractions) {
    errno = NOERRORSFOUND;
    assert(validInfractions == NULL, NULLARG, NULL);
    agencyTreeADT newTree = calloc(1, sizeof(struct agencyTreeCDT));
    assert(newTree == NULL, ENOMEM, NULL);
    newTree->validIDs = validInfractions;
    return newTree;
}

unsigned int sizeBST(const agencyTreeADT agencys) {
    return agencys->agencyCounter;
}

/* unsigned int heightBST(const agencyTreeADT agencys) { */
/*     return agencys->treeHeight; */
/* } */

static unsigned int nodeHeight(TNode * node) {
    if (node == NULL) {
        return 0;
    }
    return node->nodeHeight;
}

TNode * rightRotate(TNode *y) {
    TNode * x = y->left;
    TNode * T2 = x->right;
    x->right = y;
    y->left = T2;
    y->nodeHeight = max(nodeHeight(y->left), nodeHeight(y->right)) + 1;
    x->nodeHeight = max(nodeHeight(x->left), nodeHeight(x->right)) + 1;
    return x;
}

TNode * leftRotate(TNode *x) {
    TNode * y = x->right;
    TNode * T2 = y->left;
    y->left = x;
    x->right = T2;
    x->nodeHeight = max(nodeHeight(x->left), nodeHeight(x->right)) + 1;
    y->nodeHeight = max(nodeHeight(y->left), nodeHeight(y->right)) + 1;
    return y;
}

static void freeBstRec(TNode * root) {
    if (root == NULL) return;
    freeBstRec(root->left);
    freeBstRec(root->right);
    free(root);
}

void freeBst(agencyTreeADT agencys) {
    freeBstRec(agencys->root);
    free(agencys);
}

