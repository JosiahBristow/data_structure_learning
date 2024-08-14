#ifndef DIJKSTRA
#define DIJKSTRA

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#define MAX 32767

struct Graph {
        char *vertex;
        int **edge;
        int vertex_num;
        int edge_num;
} Graph;

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

int get_min_path(int *s, int *d, struct Graph *graph)
{
        int min = MAX;
        int index;

        for (int i = 0; i < graph->vertex_num; i++)
                if (d[i] < min && !s[i]) {
                        min = d[i];
                        index = i;
                }

        return index;
}

void dijkstra(struct Graph *graph, int index)
{
        int *s = (int*)calloc(graph->vertex_num, sizeof(struct Graph));
        int *p = (int*)calloc(graph->vertex_num, sizeof(struct Graph));
        int *d = (int*)calloc(graph->vertex_num, sizeof(struct Graph));

        for (int i = 0; i < graph->vertex_num; i++) {
                s[i] = i == index ? index : 0;

                if (graph->edge[index][i] > 0 && graph->edge[index][i] != MAX)
                        p[i] = index;
                else
                        p[i] = -1;

                d[i] = graph->edge[index][i];
        }

        for (int i = 0; i < graph->vertex_num; i++) {
                int index = get_min_path(s, d, graph);

                s[index] = 1;

                for (int j = 0; j < graph->vertex_num; j++)
                        if (!s[j] && d[index] + graph->edge[index][j] < d[j]) {
                                p[j] = index;
                                d[j] = d[index] + graph->edge[index][j];
                        }
        }

        for (int i = 0; i < graph->vertex_num; i++)
                printf("%d\t%d\t%d\n", s[i], p[i], d[i]);
}


#endif

int main(int argc, char *argv[])
{
        struct Graph *G = init_graph(7);
        int edge[7][7] = {
                0, 12, MAX, MAX, MAX, 16, 14,
                12, 0, 10, MAX, MAX, 7, MAX,
                MAX, 10, 0, 3, 5, 6, MAX,
                MAX, MAX, 3, 0, 4, MAX, MAX,
                MAX, MAX, 5, 4, 0, 2, 8,
                16, 7, 6, MAX, 2, 0, 9,
                14, MAX, MAX, MAX, 8, 9, 0,
        };
        create_graph(G, "1234567", (int*)edge);
        dijkstra(G, 0);
        return EXIT_SUCCESS;
}
