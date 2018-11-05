#include"assignment3.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>


/*
struct SLnode {
    int         key;
    struct      SLnode *next;
};
typedef struct SLnode *SLnodePtr;


struct HBnode
{
    int         key;
    struct      HBnode *next;
    SLnodePtr   bottom; 
};
*/
void printHBlist(const HBnodePtr L)
{
    HBnodePtr p = L;
    while(p=p->next)
    {
        printf("%d\n", p->key);
        
    }
}
static void addDown(SLnodePtr reference, int key)
{
    SLnodePtr next = malloc(sizeof(SLnodePtr));
    reference->next = next; //RANDOM NUMBER
    next->key = key;
    next->next = NULL;
}
static void addRight(HBnodePtr reference, int key, SLnodePtr bottom)
{
    HBnodePtr next = malloc(sizeof(HBnodePtr));
    reference->next = next; //RANDOM NUMBER
    next->key = key;
    next->next = NULL;
    next->bottom = bottom;
}
// static int getRandom(int upperBound)
// {
//     srand(time(NULL));
//     int range = rand()%(upperBound+1); // [0, upperBound]
//     int i;
    
//     for(i = 0; i<range;i++)

// }

// HBnodePtr createHBList(int n, int m)
// {
//     for (;n != 0; n--){
//         int k;
//         //Maybe combine random number and sorted array.
//         int *A = getRandom(m);
//         // for(k = 0; k < range; k++)
//     }
//     //For i in range n
//         //for i in range getRandom of m
// }
main(int argc, char const *argv[])
{
    HBnodePtr first = malloc(sizeof(HBnodePtr));
    first->key = 1;
    SLnodePtr second = malloc(sizeof(SLnodePtr));
    second->key = 2;
    first->bottom = second;
    first->next = NULL;
    printHBlist(first);
    return 0;
}
