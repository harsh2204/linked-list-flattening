#include "assignment3.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void printHBlist(const HBnodePtr L);
void printSLlist(const SLnodePtr L);
HBnodePtr createHBlist(int n, int m);
SLnodePtr flattenList(const HBnodePtr L);
void freeSLlist(SLnodePtr L);
void freeHBlist(HBnodePtr L);
static void addbottom(HBnodePtr reference, int key);
static void addRight(HBnodePtr reference, int key);
static int comparfunc(const void *head, const void *second);
static int getRandom(int *A, int upperBound);
static void sortHBList(const HBnodePtr head);
static SLnodePtr mergeSLlist(const SLnodePtr head, const SLnodePtr second);

void printHBlist(const HBnodePtr L) {
  HBnodePtr p = L;
  while (p != NULL) {
    printf(" %d ->", p->key);
    printSLlist(p->bottom);
    if (p->next != NULL)
      printf("\n | \n");
    p = p->next;
  }
  printf("\n");
}
void printSLlist(const SLnodePtr L) {
  SLnodePtr p = L;
  while (p != NULL) {
    printf("%d", p->key);
    if (p->next != NULL)
      printf(" - ");
    p = p->next;
  }
}
static void addbottom(HBnodePtr reference, int key) {
  /*
  Adds an SLnode to a HBnode reference head pointer that either creates a bottom
  node for
  the HBnode or finds the last pointer on the HBnode's SLlist and appends the
  key to it.
  */
  SLnodePtr p = reference->bottom;
  if (p == NULL) {
    SLnodePtr node = malloc(sizeof(SLnodePtr));
    node->key = key;
    node->next = NULL;
    reference->bottom = node;
  } else {
    SLnodePtr next = malloc(sizeof(SLnodePtr));
    while (p->next != NULL) {
      p = p->next;
    }
    p->next = next;
    next->key = key;
    next->next = NULL;
  }
}

static void addRight(HBnodePtr reference, int key) {
  /*
  Adds a HBnode to a reference head pointer with a desired key and an empty
  next, bottom list.
  */
  HBnodePtr next = malloc(sizeof(HBnodePtr));
  reference->next = next;
  next->key = key;
  next->next = NULL;
  next->bottom = NULL;
}
static int comparfunc(const void *head, const void *second) { // Refered from
  // https://www.tutorialspoint.com/c_standard_library/c_function_qsort.htm
  return (*(int *)head - *(int *)second);
}

static int getRandom(int *A, int upperBound) {
  int range = rand() % (upperBound + 1);
  // [0, upperBound+1] +1 to compensate for the head node taking head value
  int i;
  for (i = 0; i < range; i++)
    A[i] = rand() % 1000; // Upper limit on the random numbers is 1000
  qsort(A, range, sizeof(int), comparfunc);
  return range;
}

static void sortHBList(const HBnodePtr head) {
  /*
  Simple selection sort algorithm that works on HBLists iteratively sorting
  only the parent keys and preserving its SL nodes.
  */
  HBnodePtr i, j;
  for (i = head; i != NULL; i = i->next) {
    for (j = i->next; j != NULL; j = j->next) {
      if (i->key > j->key) {
        int temp_key = i->key;
        SLnodePtr temp_bottom = i->bottom;
        i->key = j->key;
        i->bottom = j->bottom;
        j->key = temp_key;
        j->bottom = temp_bottom;
        // free(temp_bottom);
      }
    }
  }
}

HBnodePtr createHBlist(int n, int m) {
  srand(time(NULL));
  // Random seed
  HBnodePtr head = malloc(sizeof(HBnodePtr));
  HBnodePtr ref = head;
  //   ref->key = -1;
  ref->next = NULL;
  ref->bottom = NULL;
  /*
  Logical workings
  a -> b -> c
  |    |    |
  d    f    h
  |    |
  e    g

  We can consolidate the random number problem to each of the vertical trees
  regardless of their
  data type. This way, we can generate a list of random numbers of n+1 which
  includes the HBnode
  and can be used to make sure the our list is vertically sorted without
  setting up for a new type
  of sorting algorithm. Therefore, random numbers are returned in the
  following order in an array
  [a, d, e] to help keep the HBlist sorted vertically.
  */
  for (; n != 0; n--) {
    int A[m + 1];
    // getRandom makes A an m+1 array which accounts for the HBnode key as well.
    int range = getRandom(A, m);
    // Range returns the random length of array A between [0, m+1]
    ref->key = A[0];
    // Therefore we assign each HBnode their respective keys individually.
    for (int i = 1; i < range; i++) {
      addbottom(ref, A[i]);
      // printf("ADDING %d\n", A[i]);
    }
    // Adds HBnodes to the main list.
    if (n != 1)
      addRight(ref, -1);
    ref = ref->next;
  }
  sortHBList(head);
  // Sort the parent NODES!!!!!!!
  return head;
}

static SLnodePtr mergeSLlist(const SLnodePtr head, const SLnodePtr second) {
  /*
  Base case. End of list means the other list is larger and must be used as a
  merging destination.
  */
  if (head == NULL)
    return second;
  if (second == NULL)
    return head;

  SLnodePtr merged_list = malloc(sizeof(SLnodePtr));
  /*
  merged_list is at most a SL list with two node pointers. The node pointers can
  be linked
  to other lists as well, meaning it works in more efficient manner
  */
  if (head->key < second->key) {
    merged_list->key = head->key; // Copy the key.
    /*
    Copying the key makes sure that we don't modify any of the pointers in the
    original HBList
    Move to the next node in the head list and keep the second pointer
    unchanged.
    */
    merged_list->next = mergeSLlist(head->next, second);
  } else {
    merged_list->key = second->key; // Copy the key.
    /*
    Move to the next node in the second list while keeping the head pointer
    the same
    */
    merged_list->next = mergeSLlist(head, second->next);
  }
  return merged_list;
}

SLnodePtr flattenList(const HBnodePtr L) {
  /*
  Base case if the head is null then return NULL. This works both as a solution
  an empty HBList input and the recursive base case
  */
  if (L == NULL)
    return NULL;
  /*
  We have to allocate separate memory for the flattened instead of using
  the pointers of the HBnode which will modify the original list
  */
  SLnodePtr flattened = malloc(sizeof(SLnodePtr));
  flattened->key = L->key; // Copy the key
  flattened->next = L->bottom;
  /*
  The above block of code specifically manages the HBnodes compared to the
  following block
  of code which works on the SLlists only
  */
  if (L->next == NULL)
    return flattened; // Base case for SLlist and management of its emptiness
  SLnodePtr merged_list = mergeSLlist(flattened, flattenList(L->next));
  // Flatten list causes the outer recursion which leads to coverage of the
  // entire list
  return merged_list;
}
void freeSLlist(SLnodePtr L) {
  // Works on the same principal of the printReverse function shown in class.
  if (!L)
    return;
  freeSLlist(L->next);
  free(L);
}
void freeHBlist(HBnodePtr L) {
  // Works on the same principal of the printReverse function shown in class.
  if (!L)
    return;
  freeSLlist(L->bottom);
  freeHBlist(L->next);
  free(L);
}
