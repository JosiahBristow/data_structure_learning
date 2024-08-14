#ifndef TOPSORT
#define TOPSORT

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 32767

struct Graph {
        char *vertex;
        int **edge;
        int vertex_num;
        int edge_num;
};

struct Node {
        int data;
        struct Node *next;
};

struct Node *init_stack()
{
        struct Node *stack = (struct Node*)malloc(sizeof(struct Node));

        stack->data = 0;
        stack->next = NULL;

        return stack;
}

int is_empty(struct Node *stack)
{
        return stack->next ? 0 : 1;
}

void push(struct Node *stack, int data)
{
        struct Node *node = (struct Node*)malloc(sizeof(struct Node));

        node->data = data;
        node->next = stack->next;
        stack->next = node;

        stack->data++;
}

int pop(struct Node *stack)
{
        if (is_empty(stack))
                return -1;
        struct Node *tmp = stack->next;
        int ret = tmp->data;
        stack->next = tmp->next;
        free(tmp);

        stack->data--;

        return ret;
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

int *find_in_degree(struct Graph *graph)
{
        int *in_degree = (int*)calloc(graph->vertex_num, sizeof(int));
        memset(in_degree, 0, graph->vertex_num);

        for (int i = 0; i < graph->vertex_num; i++)
                for (int j = 0; j < graph->vertex_num; j++)
                        if (graph->edge[i][j])
                                in_degree[j]++;

        return in_degree;
}

void topsort(struct Graph *graph)
{
        int *in_degree = find_in_degree(graph);

        struct Node *stack = init_stack();
        for (int i = 0; i < graph->vertex_num; i++)
                if (!in_degree[i])
                        push(stack, i);

        while (!is_empty(stack)) {
                int index = pop(stack);
                printf("%c\t", graph->vertex[index]);
                for (int i = 0; i < graph->vertex_num; i++)
                        if (graph->edge[index][i]) {
                                in_degree[i]--;
                                if (!in_degree[i])
                                        push(stack, i);
                        }
        }
        printf("\n");
}

#endif

int main(int argc, char *argv[])
{
        struct Graph *graph = init_graph(6);
        int edge[6][6] = {
                0, 1, 1, 1, 0, 0,
                0, 0, 0, 0, 0, 0,
                0, 1, 0, 0, 1, 0,
                0, 0, 0, 0, 1, 0,
                0, 0, 0, 0, 0, 0,
                0, 0, 0, 1, 1, 0,
        };
        create_graph(graph, "123456", (int*)edge);
        topsort(graph);
        return EXIT_SUCCESS;
}
