#include <stdlib.h>
#include <assert.h>
#include "heap.h"

struct Heap * newHeap() {
    struct Heap * heap = malloc(sizeof(*heap));
    heap->size = 1;
    heap->values = malloc(sizeof(void *) * 2);

    int i;
    for (i = 0; i < heap->size; i++) {
        heap->values[i] = 0 ;
    }

    return heap;
}

void freeHeap(struct Heap * heap) {
    // Free values memory.
    free(heap->values);
    free(heap);
}

int getSize(struct Heap * heap) {
    return heap->size;
}

/**
 * Enforces the min heap conditions after an insert or removal.
 */
void heapifyUp(struct Heap * heap) {
    // Check value in final slot.
    int index = heap->size - 1, parent;

    while (index > 0) {
        parent = (index - 1) / 2;
        if (heap->values[index] < heap->values[parent]) {
            int temp = heap->values[index];
            heap->values[index] = heap->values[parent];
            heap->values[parent] = temp;

            index = parent;
        } else {
            index = 0;
        }
    }
}

void heapifyDown(struct Heap * heap) {
    int index = 0, c1, c2, current;

    while(index < heap->size - 1) {
        c1 = ((index + 1) * 2) - 1;
        c2 = ((index  + 1) * 2);

        // Compare to children.
        current = heap->values[index];

        // If c1 and c2 are both allocated.
        if (c1 <= (heap->size - 1) && c2 <= (heap->size - 1)) {
            if (current < heap->values[c1] && current >= heap->values[c2]) {
                // Swap index w/ c1.
                int temp = heap->values[c1];
                heap->values[c1] = current;
                heap->values[index] = temp;

                index = c1;

            } else if (current >= heap->values[c1] && current < heap->values[c2]) {
                // Swap index w/ c2.
                int temp = heap->values[c2];
                heap->values[c2] = current;
                heap->values[index] = temp;

                index = c2;

            } else if (current < heap->values[c1] && current < heap->values[c2]) {
                // Do nothing. Stop checking.
                index = heap->size - 1;
            }

        } else if (c2 > heap->size - 1 && c1 <= heap->size - 1) {
            // Don't check c2. Doesn't exist yet.
            if (current > heap->values[c1]) {
                int temp = heap->values[c1];
                heap->values[c1] = heap->values[index];
                heap->values[index] = temp;

                index = c1;
            } else {
                index = heap->size - 1;
            }
        } else if (c1 > heap->size - 1 && c2 > heap->size - 1) {
            // No children. STAHP!
            index = heap->size - 1;
        }
    }
}

/**
 * Increments the heap size by 1. Used if you are inserting more items than the heap
 * can currently hold.
 */
void increaseHeapSize(struct Heap * heap) {
    // Get current heap size.
    int currentSize = heap->size;

    // Increment heap size.
    heap->size = currentSize + 1;
    heap->values[currentSize] = 0;
}

/**
 * Insert a value into the heap. Calls increaseHeapSize if it would exceed
 * size of backing array.
 */
void insertValue(struct Heap * heap, int value) {
    // Check if we can insert to bottom.
    int index = heap->size - 1;
    if (heap->values[index] != 0) {
        // Can't, double heap size.
        increaseHeapSize(heap);
        index = heap->size - 1;
    }

    heap->values[index] = value;

    heapifyUp(heap);
}

/**
 * Return the minimum value from the heap without removing it.
 */
int getMinValue(struct Heap * heap) {
    return heap->values[0];
}

/**
 * Return the minimum value from the heap AND remove it.
 */
int popMinValue(struct Heap * heap) {
    int min = heap->values[0];
    heap->values[0] = heap->values[heap->size - 1];

    heap->size -= 1;

    heapifyDown(heap);

    return min;
}

void main(int args, char ** argv) {
    struct Heap * heap = newHeap();

    insertValue(heap, 26);
    insertValue(heap, 54);
    insertValue(heap, 12);

    assert(getMinValue(heap) != 54);
    assert(getMinValue(heap) == 12);

    popMinValue(heap);

    assert(getMinValue(heap) == 26);

    freeHeap(heap);
}
