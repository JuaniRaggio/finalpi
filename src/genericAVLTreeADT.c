#include "genericStackADT.c"

struct  {
    TNode ** elems;
    size_t size;
    size_t count;
};


addElem();
static TNode * rightRotate(TNode * y);
static TNode * leftRotate(TNode * x);
static void freeAgencyTreeRec(TNode * root);
static void updateDiff(TNode * root, size_t amount);

