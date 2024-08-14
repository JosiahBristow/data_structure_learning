#include <string.h>
#ifndef STACK

#include <stdbool.h>
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

struct StackNode {
        int data;
        struct StackNode *next;
};

struct StackNode *init_stack()
{
        struct StackNode *stack = malloc(sizeof(struct StackNode));
        stack->data = 0;
        stack->next = NULL;

        return stack;
}

int get_size(struct StackNode *stack)
{
        return stack->data;
}

bool is_empty(struct StackNode *stack)
{
        return stack->data ? true : false;
}

void push(struct StackNode *stack, int data)
{
        struct StackNode *node = malloc(sizeof(struct StackNode));
        node->data = data;
        node->next = stack->next;

        stack->next = node;
        stack->data++;
}

int pop(struct StackNode *stack)
{
        if (is_empty(stack))
                return INT_MAX;

        struct StackNode *target = stack->next;
        int ret = target->data;

        stack->next = target->next;

        free(target);
        return ret;
}

#endif /* ifndef STACK */
