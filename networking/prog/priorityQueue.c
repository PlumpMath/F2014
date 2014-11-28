#include <stdlib.h>
#include "priorityQueue.h"

priority_queue priq_new(int size) {
    if (size < 4) size = 4;

    priority_queue q = malloc(sizeof(priority_queue_t));
    q->buffer = malloc(sizeof(queue_element_t) * size);
    q->allocated_space = size;
    q->n = 1;

    return q;
}

void priq_push(priority_queue q, void * data, int priority) {
    queue_element_t * b;
    int n, m;

    if (q->n >= q->allocated_space) {
        q->allocated_space *= 2;
        b = q->buffer = realloc(q->buffer, sizeof(queue_element_t) * q->allocated_space);
    } else {
        b = q->buffer;
    }

    n = q->n++;
    while ((m = n /2) && priority < b[m].priority) {
        b[n] = b[m];
        n = m;
    }
    b[n].data = data;
    b[n].priority = priority;
}

void * priq_pop(priority_queue q, int * priority) {
    void * out;
    if (q->n == 1) return 0;

    queue_element_t * b = q->buffer;

    out = b[1].data;
    if (priority) *priority = b[1].priority;

    --q->n;

    int n = 1, m;
    while ((m = n / 2) < q->n) {
        if (m + 1 < q->n && b[m].priority > b[m + 1].priority) m++;

        if (b[q->n].priority <= b[m].priority) break;
        b[n] = b[m];
        n = m;
    }

    b[n] = b[q->n];
    if (q->n < q->allocated_space / 2 && q->n >= 16)
        q->buffer = realloc(q->buffer, (q->allocated_space /= 2) * sizeof(b[0]));

    return out;
}

void * priq_top(priority_queue q, int * priority) {
    if (q->n == 1) return 0;
    if (priority) *priority = q->buffer[1].priority;
    return q->buffer[1].data;
}

void priq_combine(priority_queue q, priority_queue q2) {
    int i;
    queue_element_t * e = q2->buffer + 1;

    for (i = q2->n - 1; i >= 1; i--, e++)
        priq_push(q, e->data, e->priority);
    priq_purge(q2);
}
