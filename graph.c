#ifndef GRAPH
#define GRAPH

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include "circular_queue.h"

typedef struct Graph {
        char *vertex;
        int **edge;
        int vertex_num;
        int edge_num;
} Graph;

Graph* init_graph(int vertex_num)
{
        Graph *graph = (Graph*)malloc(sizeof(Graph));

        graph->vertex = (char*)calloc(vertex_num, sizeof(char));
        graph->edge = (int**)calloc(vertex_num, sizeof(int*));
        for (int i = 0; i < vertex_num; i++)
                graph->edge[i] = calloc(vertex_num, sizeof(int));
        graph->vertex_num = vertex_num;
        graph->edge_num = 0;

        return graph;
}

void create_graph(Graph *graph, char *vertex, int *edge)
{
        for (int i = 0; i < graph->vertex_num; i++) {
                graph->vertex[i] = vertex[i];
                for (int j = 0; j < graph->vertex_num; j++) {
                        graph->edge[i][j] = *(edge + i * graph->vertex_num + j);

                        if (graph->edge_num != 0)
                                graph->edge_num++;
                }
        }
        graph->edge_num /= 2;
}

void _dfs(Graph *graph, int *visited, int index)
{
        printf("%c\t", graph->vertex[index]);
        visited[index] = 1;
        for (int i = 0; i < graph->vertex_num; i++)
                if (graph->edge[index][i] && !visited[i])
                        _dfs(graph, visited, i);
}

void dfs(Graph *graph, int index)
{
        int *visited = (int*)calloc(graph->vertex_num, sizeof(int));
        memset(visited, 0, graph->vertex_num);
        _dfs(graph, visited, index);
        putc('\n', stdout);
}

void _bfs(Graph *graph, int *visited, int index)
{
        Queue *queue = init_queue();

        printf("%c\t", graph->vertex[index]);
        visited[index] = 1;
        enqueue(queue, index);
        while(!is_empty(queue)) {
                int i = dequeue(queue);
                for (int j = 0; j < graph->vertex_num; j++) {
                        if (graph->edge[i][j] && !visited[j]) {
                                printf("%c\t", graph->vertex[j]);
                                visited[j] = 1;
                                enqueue(queue, j);
                        }
                }
        }
}

void bfs(Graph *graph, int index)
{
        int *visited = (int*)calloc(graph->vertex_num, sizeof(int));
        memset(visited, 0, graph->vertex_num);
        _bfs(graph, visited, index);
        putc('\n', stdout);
}

#endif /* ifndef GRAPH */
