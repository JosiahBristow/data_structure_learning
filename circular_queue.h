#ifndef CIRCULAR_QUEUEH
#define CIRCULAR_QUEUEH

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#define MAXSIZE 5

typedef struct Queue {
        int front;
        int rear;
        int data[MAXSIZE];
} Queue;

Queue* init_queue()
{
        Queue *queue = (Queue*)malloc(sizeof(Queue));

        queue->front = 0;
        queue->rear = 0;

        return queue;
}

int is_empty(Queue *queue)
{
        return queue->rear == queue->front ? 1 : 0;
}

int is_full(Queue *queue)
{
       return (queue->rear + 1) % MAXSIZE == queue->front ? 1 : 0;
}

int get_size(Queue *queue)
{
        return (queue->rear - queue->front + MAXSIZE) % MAXSIZE;
}

int enqueue(Queue *queue, int data)
{
        if (is_full(queue))
                return 0;

        queue->data[queue->rear] = data;
        queue->rear = (queue->rear + 1) % MAXSIZE;

        return 1;
}

int dequeue(Queue *queue)
{
        if (is_empty(queue))
                return -1;

        int data = queue->data[queue->front];

        queue->front = (queue->front + 1) % MAXSIZE;

        return data;
}

void print_queue(Queue *queue)
{
        int index = queue->front;

        for (int i = 0; i < get_size(queue); i++) {
                printf("%d\t", queue->data[index]);
                index = (index + 1) % MAXSIZE;
        }

        puts("\n");
}

#endif /* ifndef circular_queueh */
