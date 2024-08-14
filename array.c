#ifndef ARRAY
#define ARRAY

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <math.h>

#define INIT_SIZE 5
#define EXPENSION_MULTIFPLE 2

typedef struct Array {
        int *array;
        int length;
        int capacity;
} Array;

Array* init_array()
{
        Array *array = (Array*)malloc(sizeof(Array));

        if (array == NULL) {
                fprintf(stderr, "Space allocation is falilure.");
                return NULL;
        }

        array->array = (int*)calloc(INIT_SIZE, sizeof(int));
        array->length = 0;
        array->capacity = INIT_SIZE;

        return array;
}

bool expend(Array *arr)
{
        if (arr == NULL) {
                fprintf(stderr, "Array is NULL, can't be expended.");
                return false;
        }

        if (!(arr->length == arr->capacity))
                return true;

        int* new_arr = (int*)calloc(arr->capacity * EXPENSION_MULTIFPLE, sizeof(int));

        if (new_arr == NULL) {
                fprintf(stderr, "Space allocation is falilure.");
                return false;
        }

        for (int i = 0; i < arr->length; i++)
                new_arr[i] = arr->array[i];

        arr->array = new_arr;
        arr->capacity = arr->capacity * EXPENSION_MULTIFPLE;

        return true;
}

bool reduce(Array *arr)
{
        if (arr == NULL) {
                fprintf(stderr, "Array is NULL, can't be reduce.");
                return false;
        }

        if (!(arr->length <= ceil(arr->capacity / EXPENSION_MULTIFPLE) && arr->capacity > INIT_SIZE))
                return true;

        int* new_arr = (int*)calloc(arr->capacity / EXPENSION_MULTIFPLE, sizeof(int));

        if (new_arr == NULL) {
                fprintf(stderr, "Space allocation is falilure.");
                return false;
        }

        for (int i = 0; i < arr->length; i++)
                new_arr[i] = arr->array[i];

        arr->array = new_arr;
        arr->capacity = arr->capacity / EXPENSION_MULTIFPLE;

        return true;
}

void insert(Array *arr, int index, int data)
{

        if (arr == NULL) {
                fprintf(stderr, "Array is NULL, can't insert data.");
                return;
        }

        if (!expend(arr)) {
                fprintf(stderr, "Array expendsion is failure");
                return;
        }

        for (int i = index; i < arr->length; i++)
                arr->array[i + 1] = arr->array[i];

        arr->length++;
}

void append(Array *arr, int data)
{
        if (arr == NULL) {
                fprintf(stderr, "Array is NULL, can't append data.");
                return;
        }

        if (!expend(arr)) {
                fprintf(stderr, "Array expendsion is failure");
                return;
        }

        arr->array[arr->length++] = data;
}

int serach(Array *arr, int target)
{
        if (arr == NULL) {
                fprintf(stderr, "Array is NULL, can't search data.");
                return false;
        }

        for (int i = 0; i < arr->length; i++)
                if (arr->array[i] == target)
                        return i;

        return -1;
}

int delete(Array *arr, int index)
{
        if (arr == NULL) {
                fprintf(stderr, "Array is NULL, can't delete data.");
                return INT_MAX;
        }

        int target = arr->array[index];

        for (int i = index + 1; i < arr->length; i++)
                arr->array[i - 1] = arr->array[i];

        arr->length--;

        if (!reduce(arr)) {
                fprintf(stderr, "Array reduacation is failure.");
                return INT_MAX;
        }

        return target;
}

#endif
