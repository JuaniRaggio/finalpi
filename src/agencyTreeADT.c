#include "../include/agencyTreeADT.h"

#define BLOCK 150

typedef struct LTicket {
    DTicket ticketData;
    struct LTicket * next;
} LTicket;

typedef struct LYear {
    DYear yearData;
    struct LYear * next;
} LYear;

// Posible optimizacion: ticketList -> ticketTree
// firstYear -> tree
typedef struct agency {
    char agencyName[AGENCY_LEN + 1];
    LTicket * ticketList;
    LTicket * ticketIterator;
    LYear * firstYear;
    LYear * yearIterator;
    DDiff amountLimits;
} TAgency;

typedef struct node {
    TAgency agencyData;
    unsigned char nodeHeight;
    struct node * left;
    struct node * right;
} TNode;

struct agencyTreeCDT {
    validIDADT validIDs;
    genericStackADT stack;
    TNode * root;
    TNode * inorderIterator;
    TNode * inorderIteratorNext;
    nDDiff * diffOrder;
    size_t diffIterator;
    size_t agencyCounter;
};

// Adds to the list @param firstYear a ticket of @param year, @param amount, @param month
// If added -> sets @param added = true
static bool addYear(LYear ** firstYear, size_t year, size_t amount, size_t month);
static LYear * addYearRec(LYear * firstYear, size_t year, size_t amount, size_t month, bool * added);
// Adds to the list @param firstTicket a ticket of @param id
// The order of the list is given by the description of each id so the function needs
// @param validIDs to look for it
static bool addTicket(validIDADT validIDs, LTicket ** firstTicket, ID_TYPE id);
static LTicket * addTicketRec(validIDADT validIDs, LTicket * firstTicket, ID_TYPE id, bool * added);
// Calculates the balance factor of @param root
static int balanceFactor(TNode * root); 
// Returns @param node 's height
static unsigned int nodeHeight(TNode * node);
// Rotations for AVL tree
static TNode * rightRotate(TNode * y);
static TNode * leftRotate(TNode * x);
// Updates @param root 's amountLimits
static void updateDiff(TNode * root, size_t amount);
// Frees @param root -> First element in Agency tree
static void freeAgencyTreeRec(TNode * root);
// Frees @param diffVector 's resources
static void freeDiffVector(nDDiff * diffVector);

/* // Creates a new empty stack */
/* static stackADT newStack(void); */
/* // Push @param elem into the top of the stack */
/* static void push(stackADT stack, TNode * elem); */
/* // Pops first element in stack. If agency->stack is empty -> pop returns null */
/* static TNode * pop(stackADT stack); */
/* // Frees stack's resources */
/* static void freeStack(stackADT stack); */
/* // True if stack is empty */
/* static int isEmpty(const stackADT stack); */

static LTicket * addTicketRec(validIDADT validIDs, LTicket * firstTicket, ID_TYPE id, bool * added) {
    int c;
    if ( firstTicket == NULL || (c = compareIDsDescription(validIDs, firstTicket->ticketData.id, id)) > 0 ) {
        LTicket * new = calloc(1, sizeof(LTicket));
        new->ticketData.id = id;
        new->ticketData.units = 1;
        new->next = firstTicket;
        (*added) = true;
        return new;
    } else if (c < 0) {
        firstTicket->next = addTicketRec(validIDs, firstTicket->next, id, added);
        return firstTicket;
    }
    firstTicket->ticketData.units++;
    (*added) = false;
    return firstTicket;
}

static bool addTicket(validIDADT validIDs, LTicket ** firstTicket, ID_TYPE id){
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
    if (firstYear == NULL || (year < firstYear->yearData.yearN)) {
        LYear * newYear = calloc(1, sizeof(LYear));
        assert(newYear == NULL, ENOMEM, firstYear);
        newYear->yearData.yearN = year;
        newYear->yearData.collected[month-1] = amount;
        newYear->yearData.totalCollected = amount;
        newYear->next = firstYear;
        (*added) = true;
        return newYear;
    } else if(year == firstYear->yearData.yearN){
        firstYear->yearData.collected[month-1] += amount; 
        firstYear->yearData.totalCollected += amount;
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

static int balanceFactor(TNode * root) {
    return nodeHeight(root->left) - nodeHeight(root->right);
} 

static void updateDiff(TNode * root, size_t amount){
    if (root->agencyData.amountLimits.maxAmount < amount){
        root->agencyData.amountLimits.maxAmount = amount;
    } else if(root->agencyData.amountLimits.minAmount > amount){
        root->agencyData.amountLimits.minAmount = amount;
    }
}

static TNode * insertAgencyRec(TNode * root, TNode ** added, char * agencyName, TTicket * tData, bool * newAgency) {
    if (root == NULL) {
        TNode * newNode = malloc(sizeof(TNode));
        assert(newNode == NULL, ENOMEM, NULL);
        myStrcpy(newNode->agencyData.agencyName, AGENCY_LEN + 1, agencyName, SEPARATOR);
        newNode->agencyData.ticketList = newNode->agencyData.ticketIterator = NULL;
        newNode->agencyData.firstYear = newNode->agencyData.yearIterator = NULL;
        newNode->left = newNode->right = NULL;
        newNode->agencyData.amountLimits.minAmount = newNode->agencyData.amountLimits.maxAmount = tData->amount;
        newNode->agencyData.amountLimits.id = tData->infractionID;
        newNode->nodeHeight = 1;
        *added = newNode;
        *newAgency = true;
        return newNode;
    }
    int cmp = strcasecmp(agencyName, root->agencyData.agencyName);
    if (cmp == 0) {
        updateDiff(root, tData->amount);
        *added = root;
        *newAgency = false;
        return root;
    } else if (cmp < 0) {
        root->left = insertAgencyRec(root->left, added, agencyName, tData, newAgency);
    } else if (cmp > 0) {
        root->right = insertAgencyRec(root->right, added, agencyName, tData, newAgency);
    }
    root->nodeHeight = max(nodeHeight(root->left), nodeHeight(root->right)) + 1;
    int balance = balanceFactor(root);
    if (balance > UPPERLIMIT && strcasecmp(agencyName, root->left->agencyData.agencyName) < 0) {
        return rightRotate(root);
    } else if (balance < LOWERLIMIT && strcasecmp(agencyName, root->right->agencyData.agencyName) > 0) {
        return leftRotate(root);
    } else if (balance > UPPERLIMIT && strcasecmp(agencyName, root->left->agencyData.agencyName) > 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    } else if (balance < LOWERLIMIT && strcasecmp(agencyName, root->right->agencyData.agencyName) < 0) {
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
    addTicket(agency->validIDs, &addedAgency->agencyData.ticketList, tData->infractionID);
    assert(errno != NOERRORSFOUND, errno, false);

    // Thread 2
    addYear(&addedAgency->agencyData.firstYear, tData->issueYear, tData->amount, tData->issueMonth);
    assert(errno != NOERRORSFOUND, errno, false);

    if (added) {
        agency->agencyCounter++;
        if ((agency->agencyCounter - 1) % BLOCK == 0) {
            nDDiff * tmp = realloc(agency->diffOrder, sizeof(nDDiff) * (agency->agencyCounter + BLOCK));
            assert(tmp == NULL, ENOMEM, false);
            agency->diffOrder = tmp;
        }
        agency->diffOrder[agency->agencyCounter - 1].data = &addedAgency->agencyData.amountLimits;
        agency->diffOrder[agency->agencyCounter - 1].agencyName = addedAgency->agencyData.agencyName;
    }
    return added;
}

void toBeginAgency(agencyTreeADT agency) {
    assert(agency == NULL, NULLARG,);
    agency->stack = newStack();
    assert(agency->stack == NULL, ENOMEM,);
    agency->inorderIterator = agency->root;
    agency->inorderIteratorNext = agency->root;
}

bool hasNextAgency(agencyTreeADT agency) {
    return agency->inorderIterator != NULL;
}

bool nextAgency(agencyTreeADT agency) {
    assert(agency == NULL || agency->stack == NULL || (!hasNextAgency(agency) && isEmpty(agency->stack)), NULLARG, false);
    while (agency->inorderIteratorNext != NULL) {
        push(agency->stack, agency->inorderIteratorNext);
        agency->inorderIteratorNext = agency->inorderIteratorNext->left;
    }
    // If agency->stack is empty -> pop returns null
    agency->inorderIterator = (TNode *)pop(agency->stack);
    if (agency->inorderIterator != NULL) {
        agency->inorderIteratorNext = agency->inorderIterator->right;
        return true;
    }
    agency->inorderIteratorNext = NULL;
    return false;
}

void toBeginYear(agencyTreeADT agency){
    assert(agency == NULL || !hasNextAgency(agency), NULLARG,);
    agency->inorderIterator->agencyData.yearIterator = agency->inorderIterator->agencyData.firstYear;
}

bool hasNextYear(agencyTreeADT agency){
    return hasNextAgency(agency) && agency->inorderIterator->agencyData.yearIterator != NULL;
}

DYear nextYear(agencyTreeADT agency){
    assert(!hasNextYear(agency), INVALIDARG, (DYear){0});
    DYear yData = agency->inorderIterator->agencyData.yearIterator->yearData;
    agency->inorderIterator->agencyData.yearIterator = agency->inorderIterator->agencyData.yearIterator->next;
    return yData;
}

void toBeginTicket(agencyTreeADT agency){
    assert(agency == NULL || !hasNextAgency(agency), NULLARG,);
    agency->inorderIterator->agencyData.ticketIterator = agency->inorderIterator->agencyData.ticketList;
}

bool hasNextTicket(agencyTreeADT agency){
    return hasNextAgency(agency) && agency->inorderIterator->agencyData.ticketIterator != NULL;
}

DTicket nextTicket(agencyTreeADT agency){
    assert(!hasNextTicket(agency), INVALIDARG, (DTicket){0});
    DTicket tData = agency->inorderIterator->agencyData.ticketIterator->ticketData;
    agency->inorderIterator->agencyData.ticketIterator = agency->inorderIterator->agencyData.ticketIterator->next;
    return tData;
}

const char * getNameOfIterator(agencyTreeADT agency) {
    assert(!hasNextAgency(agency), INVALIDARG, NULL);
    return agency->inorderIterator->agencyData.agencyName;
}

const char * getDescriptionOfidAtAgency(agencyTreeADT agency, ID_TYPE id) {
    return getDescriptionOfID(agency->validIDs, id);
}

int compareAmounts(const void * a, const void * b) { 
    const nDDiff * aData1 = (const nDDiff *)a;
    const nDDiff * aData2 = (const nDDiff *)b;
    size_t diff1 = aData1->data->maxAmount - aData1->data->minAmount;
    size_t diff2 = aData2->data->maxAmount - aData2->data->minAmount;
    if (diff1 < diff2) {
        return -1;
    } else if (diff1 > diff2) {
        return 1;
    }
    return strcasecmp(aData2->agencyName, aData1->agencyName);
}

void toBeginDiff(agencyTreeADT agency) {
    assert(agency == NULL, NULLARG,);
    nDDiff * tmp = realloc(agency->diffOrder, sizeof(nDDiff) * agency->agencyCounter);
    assert(tmp == NULL, ENOMEM,);
    agency->diffOrder = tmp;
    agency->diffIterator = agency->agencyCounter - 1;
    qsort(agency->diffOrder, agency->agencyCounter, sizeof(nDDiff), compareAmounts);
}

bool hasNextDiff(agencyTreeADT agency) {
    return agency->diffIterator < agency->agencyCounter;
}

nDDiff nextDiff(agencyTreeADT agency) {
    assert(!hasNextDiff(agency), INVALIDARG, (nDDiff){0});
    nDDiff retValue = agency->diffOrder[(agency->diffIterator)--];
    return retValue;
}

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

static unsigned int nodeHeight(TNode * node) {
    if (node == NULL) {
        return 0;
    }
    return node->nodeHeight;
}

static TNode * rightRotate(TNode * y) {
    TNode * x = y->left;
    TNode * T2 = x->right;
    x->right = y;
    y->left = T2;
    y->nodeHeight = max(nodeHeight(y->left), nodeHeight(y->right)) + 1;
    x->nodeHeight = max(nodeHeight(x->left), nodeHeight(x->right)) + 1;
    return x;
}

static TNode * leftRotate(TNode * x) {
    TNode * y = x->right;
    TNode * T2 = y->left;
    y->left = x;
    x->right = T2;
    x->nodeHeight = max(nodeHeight(x->left), nodeHeight(x->right)) + 1;
    y->nodeHeight = max(nodeHeight(y->left), nodeHeight(y->right)) + 1;
    return y;
}

static void freeYears(LYear * year) {
    if (year == NULL) {
        return;
    }
    freeYears(year->next);
    free(year);
}

static void freeTickets(LTicket * tickets) {
    if (tickets == NULL) {
        return;
    }
    freeTickets(tickets->next);
    free(tickets);
}

static void freeAgencyTreeRec(TNode * root) {
    if (root == NULL) {
        return;
    }
    freeAgencyTreeRec(root->left);
    freeAgencyTreeRec(root->right);
    freeTickets(root->agencyData.ticketList);
    freeYears(root->agencyData.firstYear);
    free(root);
}

static void freeDiffVector(nDDiff * diffVector) {
    free(diffVector);
}

void freeAgencys(agencyTreeADT agencys) {
    freeValidIDs(agencys->validIDs);
    freeDiffVector(agencys->diffOrder);
    freeStack(agencys->stack);
    freeAgencyTreeRec(agencys->root);
    free(agencys);
}

