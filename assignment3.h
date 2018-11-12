#ifndef ASSIGNMENT3_H
#define ASSIGNMENT3_H

// Node in a singly linked list

struct SLnode {
    int         key;
    struct      SLnode *next; /* Pointer to the next item in a  list */
};
typedef struct SLnode *SLnodePtr;


struct HBnode
{
    int         key;
    struct      HBnode *next; /* Next item in the horizontal list*/
    SLnodePtr   bottom; /* Pointer to the bottom list */
};

typedef struct HBnode *HBnodePtr;

HBnodePtr createHBlist(int n, int m);
SLnodePtr flattenList(const HBnodePtr L);
void freeSLlist(SLnodePtr L);
void freeHBlist(HBnodePtr L);
void printHBlist(const HBnodePtr L);
void printSLlist(const SLnodePtr L);

#endif