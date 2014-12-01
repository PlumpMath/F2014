#include <stdlib.h>

typedef struct {
  int data;
  int priority;
} heap_elem;

typedef struct  {
  int size, alloc;
  heap_elem * elements;
} Heap;

Heap * newHeap();
void freeHeap(Heap * heap);
int getSize(Heap * heap);
void heapifyUp(Heap * heap);
void heapifyDown(Heap * heap);
void increaseHeapSize(Heap * heap);
void insertValue(Heap * heap, int value, int priority);
heap_elem getMinValue(Heap * heap);
heap_elem popMinValue(Heap * heap);
