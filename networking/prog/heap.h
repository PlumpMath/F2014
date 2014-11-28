#include <stdlib.h>

struct Heap {
  int size;
  void * values;
};

struct Heap * newHeap();
void freeHeap(struct Heap * heap);
int getSize(struct Heap * heap);
void heapifyUp(struct Heap * heap);
void heapifyDown(struct Heap * heap);
void increaseHeapSize(struct Heap * heap);
void insertValue(struct Heap * heap, void * value);
int getMinValue(struct Heap * heap);
int popMinValue(struct Heap * heap);
