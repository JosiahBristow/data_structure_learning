#ifndef PRIM
#define PRIM

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 32767

typedef struct Graph {
        char *vertex;
        int **edge;
        int vertex_num;
        int edge_num;
} Graph;

typedef struct Edge {
        char vertex;
        int weight;
} Edge;

Edge* init_edge(Graph *graph, int index)
{
        Edge *edge = (Edge*)malloc(graph->vertex_num * sizeof(Edge));

        for (int i = 0; i < graph->vertex_num; i++) {
                edge[i].vertex = graph->vertex[index];
                edge[i].weight = graph->edge[index][i];
        }

        return edge;
}

int get_min_edge(Edge *edge, Graph *graph)
{
        int index = 0;

        int min_edge = MAX;
        for (int i = 0; i < graph->vertex_num; i++)
                if (edge[i].weight < min_edge && edge[i].weight != 0) {
                        min_edge = edge[i].weight;
                        index = i;
                }

        return index;
}

void prim(Graph *graph, int index)
{
        int min;
        Edge *edge = init_edge(graph, index);
        for (int i = 0; i < graph->vertex_num - 1; i++) {
                min = get_min_edge(edge, graph);
                printf("v%c --> v%c, weight = %d\n",
                       edge[min].vertex, graph->vertex[min], edge[min].weight);
                edge[min].weight = 0;
                for (int j = 0; j < graph->vertex_num; j++)
                        if (graph->edge[min][j] < edge[j].weight) {
                                edge[j].weight = graph->edge[min][j];
                                edge[j].vertex = graph->vertex[min];
                        }
        }
}

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

                        if (graph->edge[i][j] != 0 && graph->edge[i][j] != MAX)
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
                if (graph->edge[index][i] != MAX && graph->edge[index][i]
                        && !visited[i])
                        _dfs(graph, visited, i);
}

void dfs(Graph *graph, int index)
{
        int *visited = (int*)malloc(graph->vertex_num * sizeof(int));
        memset(visited, 0, graph->vertex_num);
        _dfs(graph, visited, index);
        putc('\n', stdout);
}

#endif
