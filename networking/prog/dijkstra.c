#include <stdio.h>
#include <stdlib.h>

#ifndef INFINITY
#define INFINITY 65535
#endif

#define BLOCK_SIZE 31

typedef struct node_t node_t, *heap_t;
typedef struct edge_t edge_t;

struct edge_t {
    node_t * node;
    edge_t * neighbor;
    int cost;
};

struct node_t {
    edge_t * edge;
    node_t * previous;
    int dist; // Distance from root.
    int name; // Names are ints in graph.txt
    int heap_index; // Position in heap.
};

edge_t * edge_root = 0, *e_next = 0;
heap_t * heap;
int heap_len;

void add_edge(node_t * a, node_t * b, int dist)
{
    if (e_next == edge_root) {
        edge_root = malloc(sizeof(edge_t) * (BLOCK_SIZE + 1));
        edge_root[BLOCK_SIZE].neighbor = e_next;
        e_next = edge_root + BLOCK_SIZE;
    }
    --e_next;

    e_next->node = b;
    e_next->cost = dist;
    e_next->neighbor = a->edge;
    a->edge = e_next;
}

void free_edges() {
    for (; edge_root; edge_root = e_next) {
        e_next = edge_root[BLOCK_SIZE].neighbor;
        free(edge_root);
    }
}

void set_dist(node_t * node, node_t * previous, int dist) {
    int i, j;

    if (node->previous && dist >= node->dist) return;

    node->dist = dist;
    node->previous = previous;

    i = node->heap_index;
    if (!i) i = ++heap_len;

    for (; i > 1 && node->dist < heap[j = i/2]->dist; i = j) {
        (heap[i] = heap[j])->heap_index = i;
    }

    heap[i] = node;
    node->heap_index = i;
}

node_t * pop_queue()
{
    node_t * node, * temp;
    int i, j;

    if (!heap_len) return 0;

    node = heap[1];
    temp = heap[heap_len--];

    for (i = 1; i < heap_len && (j = i * 2) <= heap_len; i = j) {
        if (j < heap_len && heap[j]->dist > heap[j+1]->dist) j++;

        if (heap[i]->dist >= temp->dist) break;
        (heap[i] = heap[j])->heap_index = i;
    }

    heap[i] = temp;
    temp->heap_index = 1;

    return node;
}

void dijkstras(node_t * start)
{
    node_t * head;
    edge_t * edge;

    set_dist(start, start, 0);
    while ((head = pop_queue())) {
        for (edge = head->edge; edge; edge = edge->neighbor) {
            set_dist(edge->node, head, head->dist + edge->cost);
        }
    }
}

void show_path(node_t * node)
{
    if (node->previous == node) {
        printf("%d", node->name);
    } else if (!node->previous) {
        printf("%d(unreached)", node->name);
    } else {
        show_path(node->previous);
        printf("-> %d(%d) ", node->name, node->dist);
    }
}

void show_path_file(FILE * file, node_t * node)
{
    if (node->previous == node) {
        fprintf(file, "%d", node->name);
    } else if (!node->previous) {
        fprintf(file, "%d(unreached)", node->name);
    } else {
        show_path_file(file, node->previous);
        fprintf(file, " -> %d", node->name);
    }
}

int getNextNode(node_t * node, int start) {
    if (node->previous == node) {
        return node->name;
    } else if (!node->previous) {
        return 0;
    } else if (node->previous->name == start) {
        return node->name;
    } else {
        return getNextNode(node->previous, start);
    }
}

/**
 * Reads an input file and produces an adjacency matrix showing the connections
 * between nodes.
 * @args filename: string that is the input file name.
 * @args length_ptr: A pointer to the length variable. Passes the length value
 *       out of the function.
 * @return A 2D array of ints (an adjacency matrix) representing the graph.
 */
int ** readInputFile(char * filename, int * length_ptr, int * start, int * goal) {
    FILE * infile;
    infile = fopen(filename, "r");

    int node1, node2, weight;
    int source, destination;
    int highest = 0;

    // Go through file once, Count vertices.
    while (fscanf(infile, "%d$%d$%d", &node1, &node2, &weight) == 3) {
        if (node1 > highest)
            highest = node1;

        if (node2 > highest)
            highest = node2;
    }

    *length_ptr = highest;

    rewind(infile);

    // Construct adjacency matrix
    int ** matrix;
    int i, j;
    matrix = malloc(sizeof(int *) * (highest + 1));
    for (i = 0; i < highest; i++) {
        matrix[i] = malloc(sizeof(int) * (highest + 1));
    }

    for (i = 0; i < highest; i++) {
        for (j = 0; j < highest; j++) {
            if (i == j)
                matrix[i][j] = 0;
            else
                matrix[i][j] = INFINITY;
        }
    }

    // Read node data.
    while (fscanf(infile, "%d$%d$%d", &node1, &node2, &weight) == 3) {
        matrix[node1 - 1][node2 - 1] = weight;
        matrix[node2 - 1][node1 - 1] = weight;
    }

    // Read source.
    while (fscanf(infile, "Source$%d\n", &source) == 1) {
        *start = source;
    }

    while (fscanf(infile, "Destination$%d\n", &destination) == 1) {
        *goal = destination;
    }

    fclose(infile);

    return matrix;
}

/**
 * Prints a summary of the traversal, including source, destination, the number
 * of nodes traversed, which were traversed and the total distance travelled.
 * @args filename: the name of the file to output to.
 */
void printSummary(char * filename, int source, int destination, node_t * nodes) {
    FILE * outfile;
    outfile = fopen(filename, "w");

    fprintf(outfile, "-----------------------------------------\n");
    fprintf(outfile, "Summary:\n");
    fprintf(outfile, "Source: %d, Destination: %d\n", source, destination);
    fprintf(outfile, "Traversal: ");
    show_path_file(outfile, nodes + (destination - 1));
    fprintf(outfile, "\n-----------------------------------------\n");

    fclose(outfile);
}

/**
 * Prints a routing table for each node in the graph.
 * ex.
 *
 *  To | Next Hop | Distance
 * ----|----------|----------
 * @args filename: the name of the file to output to.
 */
void printRoutingTable(char * filename, node_t * nodes, int offset, int length, int ** matrix) {
    FILE * outfile;
    outfile = fopen(filename, "a");

    int i;
    fprintf(outfile, "Routing table for node %d\n", offset + 1);
    fprintf(outfile, "%-3s %10s %-4s\n", "To", "Next Node", "Cost");


    for (i = 1; i <= length; i++) {
        // Find next node and cost
        int next_node = getNextNode(nodes + i - 1, offset + 1);
        int cost = matrix[next_node - 1][offset];
        if (i != offset + 1)
            fprintf(outfile, "%-3d %*s%d%*s %-4d\n", i, 5, "", next_node, 5, "", cost);
    }
    fprintf(outfile, "\n");

    fclose(outfile);
}

/* Prints out the matrix. For debugging. */
void printMatrix(int ** matrix, int length) {
    int i, j;
    for (i = 0; i < length; i++) {
        for (j = 0; j < length; j++) {
            printf("| %d ", matrix[i][j]);
        }
        printf("|\n");
    }
}

int main(int args, char** argv) {
    // Get filename from args.
    char * filename;
    if (argv[1] != NULL) {
        filename = argv[1];
    } else {
        fprintf(stderr, "No filename given. Aborting!\n");
        return 1;
    }

    int ** weightMatrix;
    int length = 0, start = 0, goal = 0;
    int * length_ptr, *start_ptr, *goal_ptr;

    length_ptr = &length;
    start_ptr = &start;
    goal_ptr = &goal;

    weightMatrix = readInputFile(filename, length_ptr, start_ptr, goal_ptr);

    int i, j, k, cost;

    for (i = 0; i < length; i++) {

        node_t * nodes = calloc(sizeof(node_t), length);

        for (j = 0; j < length; j++) {
            nodes[j].name = j+1;
        }

        for (j = 0; j < length; j++) {
            for (k = 0; k < length; k++) {
                if (j == k) continue;
                cost = weightMatrix[j][k];
                if (cost == INFINITY) continue;
                add_edge(nodes + j, nodes + k, cost);
            }
        }

        heap = calloc(sizeof(heap_t), length + 1);
        heap_len = 0;

        // Run first dijkstra's for start.
        dijkstras(nodes + i);

        if (i == 0)
            printSummary("output.txt", start, goal, nodes);

        printRoutingTable("output.txt", nodes, i, length, weightMatrix);

        free(heap);
        free(nodes);
        free_edges();
    }

    // Free memory.
    for (i = 0; i < length; i++) {
        free(weightMatrix[i]);
    }

    free(weightMatrix);

    return 0;
}
