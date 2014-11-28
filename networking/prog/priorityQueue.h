typedef struct {
    void * data;
    int priority;
} queue_elemment_t;

typedef struct {
    queue_element_t * buffer;
    int n, allocated_space;
} priority_queue_t, *priority_queue;

#define priq_purge(q) (q)->n = 1
#define priq_size(q) ((q)->n - 1)

priority_queue priq_new(int size);
void priq_push(priority_queue q, void * data, int priority);
void * priq_pop(priority_queue q, int * priority);
void * priq_top(priority_queue q, int * priority);
void priq_combine(priority_queue q, priority_queue q2);
