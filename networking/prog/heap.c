#include <stdlib.h>
#include <assert.h>
#include "heap.h"

Heap * newHeap() {
    Heap * heap = malloc(sizeof(Heap));
    heap->size = 4;
    heap->alloc = 0;
    heap->elements = malloc(sizeof(heap_elem) * heap->size);

    return heap;
}

void freeHeap(Heap * heap) {
    // Free values memory.
    free(heap->elements);
    free(heap);
}

int getSize(Heap * heap) {
    return heap->size;
}

/**
 * Enforces the min heap conditions after an insert or removal.
 */
void heapifyUp(Heap * heap) {
    // Check value in final slot.
    int index = heap->alloc - 1, parent;

    while (index > 0) {
        parent = (index - 1) / 2;
        if (heap->elements[index].priority < heap->elements[parent].priority) {
            heap_elem temp = heap->elements[index];
            heap->elements[index] = heap->elements[parent];
            heap->elements[parent] = temp;

            index = parent;
        } else {
            index = 0;
        }
    }
}

void heapifyDown(Heap * heap) {
    int index = 0, c1, c2;
    heap_elem current;

    // Loop through allocated indices only.
    while(index < heap->alloc) {

        c1 = ((index + 1) * 2) - 1;
        c2 = ((index + 1) * 2);

        // Compare to children.
        current = heap->elements[index];

        // If c1 and c2 are both allocated.
        if (c1 < heap->alloc - 1 && c2 < heap->alloc - 1) {
            if (current.priority < heap->elements[c1].priority && current.priority >= heap->elements[c2].priority) {
                // Swap index w/ c1.
                heap_elem temp = heap->elements[c1];
                heap->elements[c1] = current;
                heap->elements[index] = temp;

                index = c1;

            } else if (current.priority >= heap->elements[c1].priority && current.priority < heap->elements[c2].priority) {
                // Swap index w/ c2.
                heap_elem temp = heap->elements[c2];
                heap->elements[c2] = current;
                heap->elements[index] = temp;

                index = c2;

            } else if (current.priority < heap->elements[c1].priority && current.priority < heap->elements[c2].priority) {
                // Do nothing. Stop checking.
                index = heap->alloc;
            }

        } else if (c2 >= heap->alloc && c1 < heap->alloc) {
            // Don't check c2. Doesn't exist yet.
            if (current.priority > heap->elements[c1].priority) {
                heap_elem temp = heap->elements[c1];
                heap->elements[c1] = heap->elements[index];
                heap->elements[index] = temp;

                index = c1;
            } else {
                index = heap->alloc;
            }
        } else if (c1 >= heap->alloc && c2 >= heap->alloc) {
            // No children. STAHP!
            index = heap->alloc;
        }
    }
}

/**
 * Increments the heap size by 1. Used if you are inserting more items than the heap
 * can currently hold.
 */
void increaseHeapSize(Heap * heap) {
    // Get current heap size.

    // Increment heap size.
    heap->size *= 2;
    heap->elements = realloc(heap->elements, sizeof(heap_elem) * heap->size);
}

/**
 * Insert a value into the heap. Calls increaseHeapSize if it would exceed
 * size of backing array.
 */
void insertValue(Heap * heap, int value, int priority) {
    // Check if we can insert to bottom.
    int index = heap->alloc++;
    if (index > heap->size) {
        // Can't, double heap size.
        increaseHeapSize(heap);
    }

    heap_elem he;
    he.data = value;
    he.priority = priority;
    heap->elements[index] = he;

    heapifyUp(heap);
}

/**
 * Return the minimum value from the heap without removing it.
 */
heap_elem getMinValue(Heap * heap) {
    return heap->elements[0];
}

/**
 * Return the minimum value from the heap AND remove it.
 */
heap_elem popMinValue(Heap * heap) {
    heap_elem min = heap->elements[0];
    heap->elements[0] = heap->elements[heap->alloc - 1];

    heap->alloc -= 1;

    heapifyDown(heap);

    return min;
}

void main(int args, char ** argv) {
    Heap * heap = newHeap();

    insertValue(heap, 26, 2);
    insertValue(heap, 54, 1);
    insertValue(heap, 12, 9);

    assert(getMinValue(heap).data == 54);
    assert(getMinValue(heap).data != 12);

    popMinValue(heap);

    assert(getMinValue(heap).data == 26);

    freeHeap(heap);
}
