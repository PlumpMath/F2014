#include <stdlib.h>

typedef struct {
  int data;
  int priority;
} heap_elem_t;

typedef struct  {
  int size, alloc;
  heap_elem_t * elements;
} heap_t;

heap_t * newHeap();
void freeHeap(heap_t * heap);
int getSize(heap_t * heap);
int getCount(heap_t * heap);
int elementInHeap(heap_t * heap, int data);
void heapifyUp(heap_t * heap);
void heapifyDown(heap_t * heap);
void increaseHeapSize(heap_t * heap);
void insertValue(heap_t * heap, int value, int priority);
void addElement(heap_t * heap, heap_elem_t element);
void updatePriority(heap_t * heap, int value, int priority);
heap_elem_t getMinValue(heap_t * heap);
heap_elem_t popMinValue(heap_t * heap);
