#ifndef KRUSKAL
#define KRUSKAL

#include <stdio.h>
#include <stdlib.h>

#define MAX 32767

struct Graph {
        char *vertex;
        int **edge;
        int vertex_num;
        int edge_num;
} Graph;

struct Edge {
        int start;
        int end;
        int weight;
} Edge;

int edge_sort_cmp(const void *e1, const void *e2)
{
        struct Edge *_e1 = (struct Edge*)e1;
        struct Edge *_e2 = (struct Edge*)e2;
        return _e1->weight - _e2->weight;
}

struct Edge *init_edge(struct Graph *graph)
{
        struct Edge *edge = (struct Edge*)calloc(
                graph->edge_num,sizeof(struct Edge)
        );

        int index = 0;
        for (int i = 0; i < graph->vertex_num; i++)
                for (int j = i + 1; j < graph->vertex_num; j++)
                        if (graph->edge[i][j] != MAX) {
                                edge[index].start = i;
                                edge[index].end = j;
                                edge[index].weight = graph->edge[i][j];
                                index++;
                        }

        qsort(
                edge, graph->edge_num,
                sizeof(struct Edge), edge_sort_cmp
        );

        return edge;
}

struct Graph *init_graph(int vertex_num)
{
        struct Graph *graph = (struct Graph*)malloc(sizeof(struct Graph));

        graph->vertex = (char*)calloc(vertex_num, sizeof(char));
        graph->edge = (int**)calloc(vertex_num, sizeof(int*));
        for (int i = 0; i < vertex_num; i++)
                graph->edge[i] = calloc(vertex_num, sizeof(int));
        graph->vertex_num = vertex_num;
        graph->edge_num = 0;

        return graph;
}

void create_graph(struct Graph *graph, char *vertex, int *edge)
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

void kruskal(struct Graph *graph, int index)
{
        int *connected = (int*)malloc(graph->vertex_num * sizeof(int));
        for (int i = 0; i < graph->vertex_num; i++)
                connected[i] = i;

        struct Edge *edge = init_edge(graph);

        for (int i = 0; i < graph->edge_num; i++) {
                int start = connected[edge[i].start];
                int end = connected[edge[i].end];

                if (start != end) {
                        printf(
                                "v%c --> v%c, weight = %d\n",
                                graph->vertex[edge[i].start],
                                graph->vertex[edge[i].end],
                                edge[i].weight
                        );

                        for (int j = 0; j < graph->vertex_num; j++)
                                if (connected[j] == end)
                                        connected[j] = start;
                }
        }
}

#endif
