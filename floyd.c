#ifndef FLOYD
#define FLOYD

#include <stdio.h>
#include <stdlib.h>

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

void floyd(struct Graph *graph)
{
        int d[graph->vertex_num][graph->vertex_num];
        int p[graph->vertex_num][graph->vertex_num];

        for (int i = 0; i < graph->vertex_num; i++)
                for (int j = 0; j < graph->vertex_num; j++) {
                        d[i][j] = graph->edge[i][j];

                        if (graph->edge[i][j] > 0 && graph->edge[i][j] != MAX)
                                p[i][j] = i;
                        else
                                p[i][j] = -1;
                }

        for (int i = 0; i < graph->vertex_num; i++)
                for (int j = 0; j < graph->vertex_num; j++)
                        for (int k = 0; k < graph->vertex_num; k++)
                                if (d[j][i] + d[i][k] < d[j][k])  {
                                        d[j][k] = d[j][i] + d[i][k];
                                        p[j][k] = p[i][k];
                                }

        for (int i = 0; i < graph->vertex_num; i++) {
                for (int j = 0; j < graph->vertex_num; j++)
                        printf("%2d\t", d[i][j]);
                printf("\n");
        }
        puts("\n");
        for (int i = 0; i < graph->vertex_num; i++) {
                for (int j = 0; j < graph->vertex_num; j++)
                        printf("%2d\t", p[i][j]);
                printf("\n");
        }
}

#endif
