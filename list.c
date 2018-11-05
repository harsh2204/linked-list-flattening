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
    while(p!=NULL)
    {
        printf(" %d ->", p->key);
        printSLlist(p->bottom);
        if(p->next != NULL)
            printf("\n | \n");
    	p = p->next;    
    }
    printf("\n");
}
void printSLlist(const SLnodePtr L)
{
    SLnodePtr p = L;
    while(p!=NULL)
    {
        if(p->key != -1){
        printf("%d", p->key);
        if(p->next != NULL)
            printf(" - ");
        }
    	p = p->next;    
    }
}
static void addDown(HBnodePtr reference, int key)
{
    SLnodePtr p = reference->bottom;
    if(p->key == -1)
    {
        // printf("P IS NULL!\n");
        // p = next; //RANDOM NUMBER
        // p = malloc(sizeof(SLnodePtr));
        p->key = key;
        // printf("%d\n", p->key);
        p->next = NULL;    
    }else{
        SLnodePtr next = malloc(sizeof(SLnodePtr));
        while(p->next != NULL)
        {
            p = p -> next;
        }
        p->next = next; //RANDOM NUMBER
        next->key = key;
        next->next = NULL;
    }
}


// -----------------------------------------------------
static void swap(int* a, int* b) 
{ 
    int t = *a; 
    *a = *b; 
    *b = t; 
} 
  
static int split (int arr[], int low, int high) 
{ 
    int pivot = arr[high];    // pivot 
    int i = (low - 1);  // Index of smaller element 
  
    for (int j = low; j <= high- 1; j++) 
    { 
        // If current element is smaller than or 
        // equal to pivot 
        if (arr[j] <= pivot) 
        { 
            i++;    // increment index of smaller element 
            swap(&arr[i], &arr[j]); 
        } 
    } 
    swap(&arr[i + 1], &arr[high]); 
    return (i + 1); 
} 
static void quickSort(int arr[], int low, int high) 
{ 
    if (low < high) 
    { 
        int pi = split(arr, low, high); 
        quickSort(arr, low, pi - 1); 
        quickSort(arr, pi + 1, high); 
    } 
}
// -----------------------------------------------------



static void addRight(HBnodePtr reference, int key)
{
    HBnodePtr next = malloc(sizeof(HBnodePtr));
    reference->next = next; //RANDOM NUMBER
    next->key = key;
    next->next = NULL;
    next->bottom = malloc(sizeof(SLnodePtr));
    next->bottom->key = -1;
}
static int getRandom(int *A, int upperBound)
{
    int range = rand()%(upperBound+1); // [0, upperBound]
    // printf("range:\t%d\n", range);
    int i;
    for(i = 0; i<range;i++)
        A[i] = rand()%1000; 
    quickSort(A, 0, range-1);
    // for(int i = 0; i < range; i++)
    // {
    //     printf("%d, ",A[i]);
    // }
    // printf("\n");
    // return A;
    return range;
}
static void sortHBList(const HBnodePtr first)
{
    HBnodePtr i, j;    
    for(i = first; i != NULL; i=i->next)
    {
        for(j = i->next; j != NULL; j=j->next)
            {
                if(i->key > j->key)
                {
                    int temp_key = i->key;
                    SLnodePtr temp_bottom = i->bottom;
                    i->key = j->key;
                    i->bottom = j->bottom;
                    j->key = temp_key;
                    j->bottom = temp_bottom;
                }
            }
    }
    
}

HBnodePtr createHBList(int n, int m)
{
    srand(time(NULL));
    HBnodePtr first = malloc(sizeof(HBnodePtr));
    HBnodePtr ref = first;
    ref->key = -1;
    ref->next = NULL;
    ref->bottom = malloc(sizeof(SLnodePtr));
    ref->bottom->key = -1;
    for (;n != 0; n--){
        int A[m];
        int range = getRandom(A, m);
        ref->key = A[0];
        for(int i = 1; i < range; i++)
        {
            addDown(ref, A[i]);
            // printf("ADDING %d\n", A[i]);
        }
        // printf("\n");
        // for(k = 0; k < range; k++)
        if(n != 1)
            addRight(ref,-1);
        ref = ref->next;
    }
    // sortHBList(first);
    // Sort the parent NODES!!!!!!!
    return first;
}
int main(int argc, char const *argv[])
{
    
    HBnodePtr L = createHBList(10, 10);
    printHBlist(L);
    sortHBList(L);
    printf("\n------------------------------\n");
    printHBlist(L);
    // int A[10];
    // int *p = getRandom(A, 10);
    
    
    return 0;
}
