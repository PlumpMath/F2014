#include <stdio.h>
#include <stdlib.h>
#include "priorityQueue.h"

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
            matrix[i][j] = -1;
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
void printSummary(char * filename) {

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
int * dijkstra(int ** matrix, int start, int goal, int length) {
    priority_queue pq = priq_new(length);

    // Find start node, get children, push into queue.
    int i, weight;
    for (i = 1; i <= length; i++) {
        if (matrix[start - 1][i - 1] != -1) {
            weight = matrix[start-1][i-1];
            printf("There is an edge from %d to %d with a weight of %d\n", start, i, weight);
            void * data_ptr = &i;
            priq_push(pq, data_ptr, weight);
        }
    }

    int priority;

    printf("Elements in queue: %d\n", priq_size(pq));
    int data = *(int*)priq_top(pq, &priority);
    printf("Minimum value is %d with a weight of %d\n", data, priority);
    printf("Elements in queue: %d\n", priq_size(pq));

    free(pq->buffer);
    free(pq);
}

void main(int args, char** argv) {
    // Get filename from args.
    char * filename;
    if (argv[1] != NULL) {
        filename = argv[1];
    } else {
        fprintf(stderr, "No filename given. Aborting!\n");
        exit(1);
    }

    int ** weightMatrix;
    int length = 0, start = 0, goal = 0;
    int * length_ptr, *start_ptr, *goal_ptr;

    length_ptr = &length;
    start_ptr = &start;
    goal_ptr = &goal;

    weightMatrix = readInputFile(filename, length_ptr, start_ptr, goal_ptr);

    // Perform Dijkstra's, output results.
    int * path = dijkstra(weightMatrix, start, goal, length);

    // Free memory.
    int i;
    for (i = 0; i < length; i++) {
        free(weightMatrix[i]);
    }

    free(weightMatrix);

    exit(0);
}
