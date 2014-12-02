#include <stdio.h>
#include <stdlib.h>
#include "heap.h"
#include <assert.h>

#ifndef INFINITY
#define INFINITY 65535
#endif

struct linked_list_elem {
    int value;
    int priority;
    struct linked_list_elem * next;
};

typedef struct linked_list_elem linked_list_elem;

linked_list_elem * newLinkedList() {
    linked_list_elem * node = malloc(sizeof(linked_list_elem *) * 2);
    node->next = NULL;

    return node;
}

void freeLinkedList(linked_list_elem * node) {
    while(node->next != NULL) {
        linked_list_elem * temp = node;
        node = node->next;
        free(temp);
    }
    free(node);
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
            matrix[i][j] = INFINITY;
        }
    }

    // Read node data.
    while (fscanf(infile, "%d$%d$%d", &node1, &node2, &weight) == 3) {
        matrix[node1 - 1][node2 - 1] = weight;
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
void printSummary(char * filename, int source, int destination, linked_list_elem * path) {
    FILE * outfile;
    int totalDist = 0;

    outfile = fopen(filename, "w");

    fprintf(outfile, "%s\n", "------------------------------");
    fprintf(outfile, "Summary:\n");
    fprintf(outfile, "Source: %d, Destination: %d\n", source, destination);
    fprintf(outfile, "Traversal: ");
    while (path->next != NULL) {
        fprintf(outfile, "%d -> ", path->value);
        path = path->next;
        totalDist += path->priority;
    }
    fprintf(outfile, "%d\n", path->value);

    fprintf(outfile, "Total distance: %d\n", totalDist);
    fprintf(outfile, "%s\n", "------------------------------");

    fclose(outfile);
}

/**
 * Prints a routing table for each node in the graph.
 * ex.
 *
 * To | Next Hop | Distance | Visited
 * ---|----------|----------|--------
 * @args filename: the name of the file to output to.
 */
void printRoutingTable(char * filename) {

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

/**
 * Implementation of Dijkstra's Algorithm.
 * @args matrix: the graph that you want to explore, implemented as an adjacency list.
 * @args start: the num value of the node in the graph that you want to start at.
 * @args goal: the num value of the node in the graph that you want to get to.
 * @return a list of ints showing the shortest path from start to goal.
 */
linked_list_elem * dijkstra(int ** matrix, int start, int goal, int length) {
    assert(start < length);

    // Start path. Stored as a linked list.
    linked_list_elem * path = newLinkedList();
    path->value = 0;

    Heap * pq = newHeap(length);
    Heap * old = newHeap(length);

    int dist[length]; // Array of distances from start;
    dist[start - 1] = 0;

    int i, alt, pri;
    // Get nodes connected to start, add to queue.
    for (i = 1; i <= length; i++) {
        if (i != start) {
            dist[i - 1] = INFINITY;
        }
    }

    insertValue(pq, start, 0);

    while (getCount(pq) != 0) {
        // Pop the first element off the queue.
        heap_elem u = popMinValue(pq);
        printf("Element u has data %d and priority %d\n", u.data, u.priority);
        printf("%d elements left in queue.\n", getCount(pq));
        addElement(old, u);

        // Get connected nodes, add to queue.
        for (i = 1; i <= length; i++) {
            pri = matrix[u.data - 1][i - 1];
            if (pri != INFINITY) {
                if (elementInHeap(old, i - 1) == 0) {
                    if (dist[u.data] == INFINITY)
                        alt = u.priority;
                    else
                        alt = dist[u.data] + u.priority;

                    if (alt < dist[u.data]) {
                        dist[u.data] = alt;
                        // Create new path element.
                        if (path->value == 0) {
                            path->value = u.data;
                            path->priority = u.priority;
                        } else {
                            linked_list_elem * node = path;

                            while(node->next != NULL) {
                                node = node->next;
                            }

                            node->next = newLinkedList();
                            node = node->next;
                            node->value = u.data;
                            node->priority = u.priority;
                        }
                    }

                    insertValue(pq, i, pri);
                    printf("Inserted node %d with priority %d\n", i, pri);
                } else if (elementInHeap(old, i - 1) == 1) {
                    updatePriority(pq, i, pri);
                    printf("Updated node %d with new priority %d\n", i, pri);
                }
            }
        }
    }


    // Clean up the memory.
    freeHeap(pq);
    freeHeap(old);
    return path;
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

    // Perform Dijkstra's, output results.
    linked_list_elem * path = dijkstra(weightMatrix, start, goal, length);

    printSummary("output.txt", start, goal, path);

    // Free memory.
    int i;
    for (i = 0; i < length; i++) {
        free(weightMatrix[i]);
    }

    free(weightMatrix);
    freeLinkedList(path);

    return 0;
}
