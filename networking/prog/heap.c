#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "heap.h"

heap_t * newHeap() {
    heap_t * heap = malloc(sizeof(heap_t));
    heap->size = 4;
    heap->alloc = 0;
    heap->elements = malloc(sizeof(heap_elem_t) * heap->size);

    return heap;
}

void freeHeap(heap_t * heap) {
    // Free values memory.
    free(heap->elements);
    free(heap);
}

int getSize(heap_t * heap) {
    return heap->size;
}

int getCount(heap_t * heap) {
    return heap->alloc;
}

/**
 * Enforces the min heap conditions after an insert or removal.
 */
void heapifyUp(heap_t * heap) {
    // Check value in final slot.
    int index = heap->alloc - 1, parent;

    while (index > 0) {
        parent = (index - 1) / 2;
        if (heap->elements[index].priority < heap->elements[parent].priority) {
            heap_elem_t temp = heap->elements[index];
            heap->elements[index] = heap->elements[parent];
            heap->elements[parent] = temp;

            index = parent;
        } else {
            index = 0;
        }
    }
}

void heapifyDown(heap_t * heap) {
    int index = 0, c1, c2;
    heap_elem_t current, c1_val, c2_val;

    // Loop through allocated indices only.
    while(index < heap->alloc) {

        c1 = ((index + 1) * 2) - 1;
        c2 = ((index + 1) * 2);

        // Compare to children.
        current = heap->elements[index];
        c1_val = heap->elements[c1];
        c2_val = heap->elements[c2];

        // If c1 and c2 are both allocated.
        if (c1 < heap->alloc - 1 && c2 < heap->alloc - 1) {
            if (current.priority < c1_val.priority && current.priority >= c2_val.priority) {
                // Swap index w/ c1.
                heap_elem_t temp = heap->elements[c1];
                heap->elements[c1] = current;
                heap->elements[index] = temp;

                index = c1;

            } else if (current.priority >= c1_val.priority && current.priority < c2_val.priority) {
                // Swap index w/ c2.
                heap_elem_t temp = heap->elements[c2];
                heap->elements[c2] = current;
                heap->elements[index] = temp;

                index = c2;

            } else if (current.priority < c1_val.priority && current.priority < c2_val.priority) {
                // Do nothing. Stop checking.
                index = heap->alloc;
            } else if (current.priority >= c1_val.priority && current.priority >= c2_val.priority) {
                // Pick whichever is smaller.
                if (c1_val.priority < c2_val.priority) {
                    heap_elem_t temp = heap->elements[c1];
                    heap->elements[c1] = current;
                    heap->elements[index] = temp;
                } else {
                    heap_elem_t temp = heap->elements[c2];
                    heap->elements[c2] = current;
                    heap->elements[index] = temp;
                }
            }

        } else if (c2 >= heap->alloc && c1 < heap->alloc) {
            // Don't check c2. Doesn't exist yet.
            if (current.priority > heap->elements[c1].priority) {
                heap_elem_t temp = heap->elements[c1];
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
void increaseHeapSize(heap_t * heap) {
    // Increment heap size.
    heap->size *= 2;
    heap->elements = realloc(heap->elements, sizeof(heap_elem_t) * heap->size);
}

/**
 * Insert a value into the heap. Calls increaseHeapSize if it would exceed
 * size of backing array.
 */
void insertValue(heap_t * heap, int value, int priority) {
    // Check if we can insert to bottom.
    int index = heap->alloc++;
    if (index >= heap->size) {
        // Can't, double heap size.
        increaseHeapSize(heap);
    }

    heap_elem_t he;
    he.data = value;
    he.priority = priority;
    heap->elements[index] = he;

    heapifyUp(heap);
}

void addElement(heap_t * heap, heap_elem_t element) {
    insertValue(heap, element.data, element.priority);
}

int elementInHeap(heap_t * heap, int data) {
    int i;
    for (i = 0; i < heap->alloc; i++) {
        if (heap->elements[i].data == data) {
            return 1;
        }
    }
    return 0;
}

/**
 * Return the minimum value from the heap without removing it.
 */
heap_elem_t getMinValue(heap_t * heap) {
    return heap->elements[0];
}

void updatePriority(heap_t * heap, int value, int priority) {
    // Find node with data = value.
    int i;
    heap_elem_t elem;

    for (i = 0; i < heap->alloc; i++) {
        elem = heap->elements[i];
        if (elem.data == value) {
            elem.priority = priority;
        }
    }
}

/**
 * Return the minimum value from the heap AND remove it.
 */
heap_elem_t popMinValue(heap_t * heap) {
    heap_elem_t min = heap->elements[0];
    heap->elements[0] = heap->elements[heap->alloc - 1];

    heap->alloc -= 1;

    heapifyDown(heap);

    return min;
}
