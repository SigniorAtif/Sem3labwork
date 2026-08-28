/*
 * Q. Write a C program to implement an Array List that works on "chunks",
 *    where a chunk is a value v repeated v times (e.g. 3 -> 3 3 3):
 *      - insert(index, v): find the chunk containing the given index and
 *        insert a new chunk (v repeated v times) next to that chunk; the
 *        existing chunk stays intact
 *      - delete(index): find the chunk containing the given index and remove
 *        that whole chunk
 *      - display the list
 *    The array must grow automatically (realloc) when a chunk does not fit.
 *
 * Sample Input:
 *   (no input is read; the program works on the built-in demo array
 *    1 2 2 3 3 3 4 4 4 4, then inserts the chunk 7 at index 4 and deletes
 *    the chunk containing index 2)
 *
 * Sample Output:
 *   Initial: 1 2 2 3 3 3 4 4 4 4
 *   After insert 2 at index 4: 1 2 2 3 3 3 7 7 7 7 7 7 7 4 4 4 4
 *   After delete chunk at index 6: 1 3 3 3 7 7 7 7 7 7 7 4 4 4 4
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *arr;
    int size;
    int capacity;
} arraylist;

void init_capacity(arraylist *list, int capacity) {
    list->arr = (int *)malloc(capacity * sizeof(int));
    list->size = 0;
    list->capacity = capacity;
}

void ensure_capacity(arraylist *list, int needed) {
    if (needed <= list->capacity) return;
    int newcap = needed;
    list->arr = (int *)realloc(list->arr, newcap * sizeof(int));
    list->capacity = newcap;
}

// push a plain value at the end (used for building the initial demo array)
void push(arraylist *list, int value) {
    ensure_capacity(list, list->size + 1);
    list->arr[list->size++] = value;
}

// find [start,end] (inclusive) of the contiguous equal-value chunk containing index
void chunk_bounds(arraylist *list, int index, int *start, int *end) {
    int v = list->arr[index];
    int l = index, r = index;
    while (l > 0 && list->arr[l - 1] == v) l--;
    while (r + 1 < list->size && list->arr[r + 1] == v) r++;
    *start = l;
    *end = r;
}

void insertChunk(arraylist *list, int index, int value) {
    if (index < 0 || index >= list->size) {
        printf("Index out of bounds\n");
        return;
    }
    if (value <= 0) {
        printf("Value must be positive\n");
        return;
    }

    int start, end;
    chunk_bounds(list, index, &start, &end);
    int insertAt = (index - start < end - index) ? start : end + 1;

    ensure_capacity(list, list->size + value);

    // shift everything from insertAt onward to the right by `value` slots
    for (int i = list->size - 1; i >= insertAt; i--) {
        list->arr[i + value] = list->arr[i];
    }
    for (int i = 0; i < value; i++) {
        list->arr[insertAt + i] = value;
    }
    list->size += value;
}

int deleteChunk(arraylist *list, int index) {
    if (index < 0 || index >= list->size) {
        printf("Index out of bounds\n");
        return 1;
    }

    int start, end;
    chunk_bounds(list, index, &start, &end);
    int chunkLen = end - start + 1;

    for (int i = end + 1; i < list->size; i++) {
        list->arr[i - chunkLen] = list->arr[i];
    }
    list->size -= chunkLen;
    return 0;
}

void display(arraylist *list) {
    for (int i = 0; i < list->size; i++) {
        printf("%d ", list->arr[i]);
    }
    printf("\n");
}

int main() {
    arraylist list;
    init_capacity(&list, 4);

    int demo[] = {1, 2, 2, 3, 3, 3, 4, 4, 4, 4};
    for (int i = 0; i < 10; i++) push(&list, demo[i]);

    printf("Initial: ");
    display(&list);

    insertChunk(&list, 4, 7); // index 4 is inside the "3" chunk
    printf("After insert 2 at index 4: ");
    display(&list);

    deleteChunk(&list, 2); // index 6 is now inside the "2" chunk we just inserted
    printf("After delete chunk at index 6: ");
    display(&list);

    free(list.arr);
    return 0;
}
