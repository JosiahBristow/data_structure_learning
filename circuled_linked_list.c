#ifndef CIRCULED_INKED_LIST
#define CIRCULED_INKED_LIST

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
        int data;
        struct Node *next;
} Node;

Node* init_list()
{
        Node *list = (Node*)malloc(sizeof(Node));

        list->data = 0;
        list->next = list;

        return list;
}

void head_insert(Node *list, int data)
{
        Node *node = (Node*)malloc(sizeof(Node));

        node->data = data;
        node->next = list->next;
        list->next = node;

        list->data++;
}

void tail_insert(Node *list, int data)
{
        Node *node = (Node*)malloc(sizeof(Node));

        node->data = data;

        Node *head = list;

        while (list->next != head)
                list = list->next;
        list->next = node;
        node->next = head;

        head->data++;
}

int delete(Node *list, int data)
{
        Node *head = list;
        Node *target = NULL;
        int ret = 0;

        while (list->next->data != data && list->next != head)
                list = list->next;
        target = list->next;
        list->next = target->next;

        head->data--;

        ret = target->data;
        free(target);

        return ret;
}

#endif
