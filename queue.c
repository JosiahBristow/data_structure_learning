#ifndef QUEUE

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct QueueNode {
        int data;
        struct QueueNode *next;
};

struct QueueNode *init_queue()
{
        struct QueueNode *queue = malloc(sizeof(struct QueueNode));
        queue->data = 0;
        queue->next = NULL;
        return queue;
}

int get_size(struct QueueNode *queue)
{
        return queue->data;
}

bool is_empty(struct QueueNode *queue)
{
        return queue->data ? true : false;
}

void enqueue(struct QueueNode *queue, int data)
{
        struct QueueNode *node = malloc(sizeof(struct QueueNode));
        node->data = data;
        node->next = NULL;

        queue->data++;

        while(queue->next != NULL)
                queue = queue->next;
        queue->next = node;
}

int dequeue(struct QueueNode *queue)
{
        if (is_empty(queue))
                return INT_MAX;

        struct QueueNode *target = queue->next;
        int ret = target->data;

        queue->next = target->next;
        queue->data--;

        free(target);
        return ret;
}

#endif /* ifndef QUEUE */
