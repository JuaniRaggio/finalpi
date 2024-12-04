#include <stdlib.h>
#include "../include/stackADT.h"
#include "../include/validIDADT.h"
#include "../include/formats.h"
#include "../include/errorManagement.h"
#include "../include/lib.h"
#include "../include/diffTreeADT.h"


typedef struct diffNode {
    DDiff diffData;
    struct diffNode * left;
    struct diffNode * right;
    unsigned char nodeHeight;
} TDiff;

struct diffTreeCDT {
    TDiff * root;
    TDiff * iterator;
    stackADT stack;
    validIDADT validIDs;
};

static void freeDiffRec(TDiff * root);
static TDiff * insertDiffRec(validIDADT validIDs,TDiff * root, TTicket * ticket, char * agencyName);
/*VER SI LO HACEMOS GENERICO*/
static int balanceFactor (TDiff * root); 

diffTreeADT newDiff(validIDADT validIDs){
    assert(validIDs == NULL, NULLARG, NULL);
    diffTreeADT newDiff = calloc(1,sizeof(struct diffTreeCDT));
    assert(newDiff == NULL, ENOMEM, NULL);
    newDiff->validIDs = validIDs;
    return newDiff;
}

void toBeginDiff(diffTreeADT diffTree){
    diffTree->stack = newStack(sizeof(TDiff *));
    diffTree->iterator = diffTree->root;
}

bool hasNextDiff(diffTreeADT diffTree){
    return diffTree->iterator !=NULL;
}

DDiff nextDiff(diffTreeADT diffTree){
    DDiff retDiff = {0};
    assert(diffTree == NULL || diffTree->stack == NULL || (!hasNextDiff(diffTree) && isEmpty(diffTree->stack)), NULLARG, retDiff);
    while(diffTree->iterator != NULL){
        push(diffTree->stack, diffTree->iterator);
        diffTree->iterator = diffTree->iterator->left;
    }
    diffTree->iterator = pop(diffTree->stack);
    retDiff = diffTree->iterator->diffData;
    diffTree->iterator = diffTree->iterator->right;
    return retDiff;
}

static void updateDiff(TDiff * root, size_t amount){
    if(root->diffData.maxAmount < amount){
        root->diffData.maxAmount = amount;
    }else if(root->diffData.minAmount > amount){
        root->diffData.minAmount = amount;
    }
}

static int balanceFactor (TDiff * root ) {
    return root->left->nodeHeight - root->right->nodeHeight;
} 

// static int compareDiff()
static TDiff * insertDiffRec(validIDADT validIDs,TDiff * root, TTicket * ticket, char * agencyName){
    if(root == NULL){
        TDiff * newDiff = malloc(sizeof(TDiff));
        newDiff->diffData.id = ticket->infractionID;
        newDiff->diffData.maxAmount = newDiff->diffData.minAmount = ticket->amount;
        newDiff->diffData.diffAmount = INIT_DIFF;
        newDiff->left =  newDiff->right = NULL;
        return newDiff;
    }    
    int cmp = compareIDvsDescription(validIDs,root->diffData.id,agencyName);
    if(cmp < 0){
        root->left = insertDiffRec(validIDs, root->left, ticket, agencyName);
    }else if(cmp > 0){
        root->right = insertDiffRec(validIDs,root->right,ticket,agencyName);
    }else{
        updateDiff(root,ticket->amount);
    }
    root->nodeHeight = max(root->left->nodeHeight, root->right->nodeHeight) + 1;
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

void insertDiff(diffTreeADT diffTree,TTicket * ticket, char * agencyName){
    assert(diffTree == NULL || ticket == NULL || agencyName == NULL || (!isValidID(diffTree->validIDs,ticket->infractionID)), INVALIDARG,);
    diffTree->root = insertDiffRec(diffTree->validIDs,diffTree->root, ticket, agencyName);
}

static void freeDiffRec(TDiff * root){
    if(root == NULL){
        return;
    }
    freeDiffRec(root->left);
    freeDiffRec(root->right);
    free(root);
}

void freeDiff(diffTreeADT diffTree){
    freeDiffRec(diffTree->root);
    free(diffTree);
}

