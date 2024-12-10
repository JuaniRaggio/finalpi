#include "../include/agencyTreeADT.h"

#define BLOCK 150

typedef struct RTicket {
    DTicket ticketData;
    unsigned char nodeHeight;
    struct RTicket * left;
    struct RTicket * right;
} RTicket;

typedef struct RYear {
    DYear yearData;
    unsigned char nodeHeight;
    struct RYear * left;
    struct RYear * right;
} RYear;

typedef struct agency {
    char agencyName[AGENCY_LEN + 1];
    genericStackADT stackT;
    RTicket * rootTicket;
    RTicket * ticketIterator;
    RTicket * ticketIteratorNext;
    genericStackADT stackY;
    RYear * rootYear;
    RYear * yearIterator;
    RYear * yearIteratorNext;
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
static bool insertYear(RYear ** firstYear, size_t year, size_t amount, size_t month);
static RYear * insertYearRec(RYear * firstYear, size_t year, size_t amount, size_t month, bool * added);
// Adds to the list @param firstTicket a ticket of @param id
// The order of the list is given by the description of each id so the function needs
// @param validIDs to look for it
static bool insertTicket(validIDADT validIDs, RTicket ** firstTicket, ID_TYPE id);
static RTicket * insertTicketRec(validIDADT validIDs, RTicket * firstTicket, ID_TYPE id, bool * added);
// Inserts agencies in the agency tree
static TNode * insertAgencyRec(TNode * root, TNode ** added, char * agencyName, TTicket * tData, bool * newAgency);
// Calculates the balance factor of @param root
static int balanceFactor(TNode * root); 
static int balanceFactorYear(RYear * root); 
static int balanceFactorTicket(RTicket * root); 
// Returns @param node 's height
static unsigned int nodeHeight(TNode * node);
static unsigned int nodeHeightYear(RYear * node);
static unsigned int nodeHeightTicket(RTicket * node);
// Rotations for AVL tree
static TNode * rightRotate(TNode * y);
static TNode * leftRotate(TNode * x);
static RYear * rightRotateYear(RYear * y);
static RYear * leftRotateYear(RYear * x);
static RTicket * rightRotateTicket(RTicket * y);
static RTicket * leftRotateTicket(RTicket * x);
// Updates @param root 's amountLimits
static void updateDiff(TNode * root, size_t amount);
// Frees @param root -> First element in Agency tree
static void freeAgencyTreeRec(TNode * root);
// Frees @param diffVector 's resources
static void freeDiffVector(nDDiff * diffVector);
static void freeYears(RYear * year);
static void freeTickets(RTicket * year);

static RTicket * insertTicketRec(validIDADT validIDs, RTicket * root, ID_TYPE id, bool * added) {
    if (root == NULL) {
        RTicket * new = calloc(1, sizeof(RTicket));
        *added = false;
        assert(new == NULL, ENOMEM, root);
        new->ticketData.id = id;
        new->ticketData.units = 1;
        new->nodeHeight = 1;
        *added = true;
        return new;
    }
    int c = compareIDsDescription(validIDs, root->ticketData.id, id);
    if (c == 0) {
        root->ticketData.units++;
        *added = false;
        return root;
    } else if (c < 0) {
        root->right = insertTicketRec(validIDs, root->right, id, added);
    } else if (c > 0) {
        root->left = insertTicketRec(validIDs, root->left, id, added);
    } 
    root->nodeHeight = max(nodeHeightTicket(root->left), nodeHeightTicket(root->right)) + 1;
    int balance = balanceFactorTicket(root);
    if (balance > UPPERLIMIT && (c < 0)) {
        if (c < 0) {
            return rightRotateTicket(root);
        }
        root->left=leftRotateTicket(root->left);
        return rightRotateTicket(root);
    } else if (balance < LOWERLIMIT && (c > 0)) {
        if (c > 0) {
            return leftRotateTicket(root);
        }
        root->right = rightRotateTicket(root->right);
        return leftRotateTicket(root);
    }
    return root;
}

static bool insertTicket(validIDADT validIDs, RTicket ** firstTicket, ID_TYPE id){
    errno = NOERRORSFOUND;
    assert(validIDs == NULL, NULLARG, false);
    if (!isValidID(validIDs, id)) {
        return false;
    }
    bool added = false;
    *firstTicket = insertTicketRec(validIDs, *firstTicket, id, &added);
    return added;
}

static RYear * insertYearRec(RYear * root, size_t year, size_t amount, size_t month, bool * added) {
    if (root == NULL ) {
        RYear * newYear = calloc(1, sizeof(RYear));
        *added = false;
        assert(newYear == NULL, ENOMEM, root);
        newYear->yearData.yearN = year;
        newYear->yearData.collected[month-1] = amount;
        newYear->yearData.totalCollected = amount;
        newYear->nodeHeight = 1;
        *added = true;
        return newYear;
    }
    int cmp = year - root->yearData.yearN;
    if (cmp < 0) {
        root->left = insertYearRec(root->left, year, amount, month, added);
    } else if (cmp > 0) {
        root->right = insertYearRec(root->right, year, amount, month, added);
    } else {
        root->yearData.collected[month - 1] += amount;
        root->yearData.totalCollected += amount;
        *added = false;
        return root;
    }
    root->nodeHeight = max(nodeHeightYear(root->left), nodeHeightYear(root->right)) + 1;
    int balance = balanceFactorYear(root);
    if (balance > UPPERLIMIT && (cmp < 0)) {
        if (cmp < 0) {
            return rightRotateYear(root);
        }
        root->left=leftRotateYear(root->left);
        return rightRotateYear(root);
    } else if (balance < LOWERLIMIT && (cmp > 0)) {
        if (cmp > 0) {
            return leftRotateYear(root);
        }
        root->right = rightRotateYear(root->right);
        return leftRotateYear(root);
    }
    return root;
}

static bool insertYear(RYear ** firstYear, size_t year, size_t amount, size_t month) {
    errno = NOERRORSFOUND;
    assert(firstYear == NULL, NULLARG, false);
    if (amount == 0 || month > MONTHS || month == 0) {
        return false;
    }
    bool added = false;
    *firstYear = insertYearRec(*firstYear, year, amount, month, &added);
    return added;
}

static TNode * insertAgencyRec(TNode * root, TNode ** added, char * agencyName, TTicket * tData, bool * newAgency) {
    if (root == NULL) {
        TNode * newNode = malloc(sizeof(TNode));
        assert(newNode == NULL, ENOMEM, NULL);
        myStrcpy(newNode->agencyData.agencyName, AGENCY_LEN + 1, agencyName, SEPARATOR);
        newNode->agencyData.rootTicket = newNode->agencyData.ticketIterator = NULL;
        newNode->agencyData.rootYear = newNode->agencyData.yearIterator = NULL;
        newNode->agencyData.amountLimits.minAmount = newNode->agencyData.amountLimits.maxAmount = tData->amount;
        newNode->agencyData.amountLimits.id = tData->infractionID;
        newNode->left = newNode->right = NULL;
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
    if (balance > UPPERLIMIT && (cmp < 0)) {
        if (cmp < 0) {
            return rightRotate(root);
        }
        root->left = leftRotate(root->left);
        return rightRotate(root);
    } else if (balance < LOWERLIMIT && (cmp > 0)) {
        if (cmp > 0) {
            return leftRotate(root);
        }
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}

static void updateDiff(TNode * root, size_t amount){
    if (root->agencyData.amountLimits.maxAmount < amount){
        root->agencyData.amountLimits.maxAmount = amount;
    } else if(root->agencyData.amountLimits.minAmount > amount){
        root->agencyData.amountLimits.minAmount = amount;
    }
}

void updateAgencyNode(const void * root, const void * agencyData) {
    TTicket * data = (TTicket *)agencyData;
    updateDiff((TNode *)root, data->amount);
}

bool insertAgency(agencyTreeADT agency, char * agencyName, TTicket * tData) {
    errno = NOERRORSFOUND;
    assert(!isValidID(agency->validIDs, tData->infractionID), INVALIDARG, false);
    assert(agency == NULL || agencyName == NULL, NULLARG, false);
    bool added = false;
    TNode * addedAgency = NULL;
    agency->root = insertAgencyRec(agency->root, &addedAgency, agencyName, tData, &added);
    assert(errno != NOERRORSFOUND, errno, false);

    insertTicket(agency->validIDs, &addedAgency->agencyData.rootTicket, tData->infractionID);
    assert(errno != NOERRORSFOUND, errno, false);

    insertYear(&addedAgency->agencyData.rootYear, tData->issueYear, tData->amount, tData->issueMonth);
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
    assert(agency == NULL, NULLARG,);
    agency->inorderIterator->agencyData.stackY = newStack();
    assert(agency->stack == NULL, ENOMEM,);
    agency->inorderIterator->agencyData.yearIterator = agency->inorderIterator->agencyData.rootYear;
    agency->inorderIterator->agencyData.yearIteratorNext = agency->inorderIterator->agencyData.rootYear;
}

bool hasNextYear(agencyTreeADT agency){
    return hasNextAgency(agency) && agency->inorderIterator->agencyData.yearIterator != NULL;
}

DYear nextYear(agencyTreeADT agency){
    assert(!hasNextAgency(agency) || agency->inorderIterator->agencyData.stackY == NULL || (!hasNextYear(agency) && isEmpty(agency->inorderIterator->agencyData.stackY)), NULLARG, (DYear){0});
    TAgency * aux = &agency->inorderIterator->agencyData;
    while(aux->yearIteratorNext != NULL) {
        push(aux->stackY, aux->yearIteratorNext);
        aux->yearIteratorNext = aux->yearIteratorNext->left;
    }
    aux->yearIterator = pop(aux->stackY);
    if (aux->yearIterator != NULL) {
        aux->yearIteratorNext = aux->yearIterator->right;
        return aux->yearIterator->yearData;
    }
    aux->yearIteratorNext = NULL;
    return (DYear){0};
}

void toBeginTicket(agencyTreeADT agency){
    assert(agency == NULL || !hasNextAgency(agency), NULLARG,);
    agency->inorderIterator->agencyData.stackT = newStack();
    assert(agency->stack == NULL, ENOMEM, );
    agency->inorderIterator->agencyData.ticketIterator = agency->inorderIterator->agencyData.rootTicket;
    agency->inorderIterator->agencyData.ticketIteratorNext = agency->inorderIterator->agencyData.rootTicket;
}

bool hasNextTicket(agencyTreeADT agency){
    return hasNextAgency(agency) && agency->inorderIterator->agencyData.ticketIterator != NULL;
}

DTicket nextTicket(agencyTreeADT agency){
    assert(!hasNextAgency(agency) || agency->inorderIterator->agencyData.stackT == NULL || (!hasNextTicket(agency) && isEmpty(agency->inorderIterator->agencyData.stackT)), INVALIDARG, (DTicket){0});
    TAgency * aux = &agency->inorderIterator->agencyData;
    while(aux->ticketIteratorNext != NULL){
        push(aux->stackT,aux->ticketIteratorNext);
        aux->ticketIteratorNext = aux->ticketIteratorNext->left;
    }
    aux->ticketIterator = pop(aux->stackT);
    if(aux->ticketIterator != NULL){
        aux->ticketIteratorNext = aux->ticketIterator->right;
        return aux->ticketIterator->ticketData;
    }
    aux->ticketIteratorNext = NULL;
    return (DTicket){0};
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

static unsigned int nodeHeightTicket(RTicket * node) {
    if (node == NULL) {
        return 0;
    }
    return node->nodeHeight;
}

static unsigned int nodeHeightYear(RYear * node) {
    if (node == NULL) {
        return 0;
    }
    return node->nodeHeight;
}

static unsigned int nodeHeight(TNode * node) {
    if (node == NULL) {
        return 0;
    }
    return node->nodeHeight;
}

static RTicket * rightRotateTicket(RTicket * y) {
    RTicket * x = y->left;
    RTicket * T2 = x->right;
    x->right = y;
    y->left = T2;
    y->nodeHeight = max(nodeHeightTicket(y->left), nodeHeightTicket(y->right)) + 1;
    x->nodeHeight = max(nodeHeightTicket(x->left), nodeHeightTicket(x->right)) + 1;
    return x;
}

static RTicket * leftRotateTicket(RTicket * x) {
    RTicket * y = x->right;
    RTicket * T2 = y->left;
    y->left = x;
    x->right = T2;
    x->nodeHeight = max(nodeHeightTicket(x->left), nodeHeightTicket(x->right)) + 1;
    y->nodeHeight = max(nodeHeightTicket(y->left), nodeHeightTicket(y->right)) + 1;
    return y;
}

static RYear * rightRotateYear(RYear * y) {
    RYear * x = y->left;
    RYear * T2 = x->right;
    x->right = y;
    y->left = T2;
    y->nodeHeight = max(nodeHeightYear(y->left), nodeHeightYear(y->right)) + 1;
    x->nodeHeight = max(nodeHeightYear(x->left), nodeHeightYear(x->right)) + 1;
    return x;
}

static RYear * leftRotateYear(RYear * x) {
    RYear * y = x->right;
    RYear * T2 = y->left;
    y->left = x;
    x->right = T2;
    x->nodeHeight = max(nodeHeightYear(x->left), nodeHeightYear(x->right)) + 1;
    y->nodeHeight = max(nodeHeightYear(y->left), nodeHeightYear(y->right)) + 1;
    return y;
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

static int balanceFactorYear(RYear * root) {
    return nodeHeightYear(root->left) - nodeHeightYear(root->right);
} 

static int balanceFactorTicket(RTicket * root) {
    return nodeHeightTicket(root->left) - nodeHeightTicket(root->right);
} 

static int balanceFactor(TNode * root) {
    return nodeHeight(root->left) - nodeHeight(root->right);
} 

static void freeYears(RYear * year) {
    if (year == NULL) {
        return;
    }
    freeYears(year->left);
    freeYears(year->right);
    free(year);
}

static void freeTickets(RTicket * tickets) {
    if (tickets == NULL) {
        return;
    }
    freeTickets(tickets->left);
    freeTickets(tickets->right);
    free(tickets);
}

static void freeAgencyTreeRec(TNode * root) {
    if (root == NULL) {
        return;
    }
    freeAgencyTreeRec(root->left);
    freeAgencyTreeRec(root->right);
    freeTickets(root->agencyData.rootTicket);
    freeYears(root->agencyData.rootYear);
    freeStack(root->agencyData.stackT);
    freeStack(root->agencyData.stackY);
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

