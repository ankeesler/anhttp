#include "list.h"

#include <stdlib.h>
#include <string.h>

void anhttpListInit(anhttpList_t *list, int size) {
    list->elements = (long *)malloc(sizeof(long) * size);
    list->length = 0;
    list->size = size;
}

void anhttpListFree(anhttpList_t *list) {
    free(list->elements);
    list->length = 0;
    list->size = 0;
}

void _anhttpListAdd(anhttpList_t *list, long element) {
    if (list->length == list->size) {
        int newSize = list->size * 2;
        long *newElements = (long *)malloc(sizeof(long) * newSize);

        memcpy(newElements, list->elements, sizeof(long) * list->size);
        free(list->elements);

        list->elements = newElements;
        list->size = newSize;
    }

    list->elements[list->length++] = element;
}
