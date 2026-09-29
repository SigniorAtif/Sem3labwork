/*
 * Q. Write a C program to implement an Array List (a list backed by a
 *    dynamically allocated array) supporting the operations:
 *      - create / initialise the list with elements read from the user
 *      - insert an element at a given index
 *      - delete the element at a given index (return the deleted value)
 *      - search for a value and report its index
 *      - display all elements of the list
 *
 * Sample Input / Output:
 *
 *   How many elements (0 to 10)? 4
 *   Element 0: 10
 *   Element 1: 20
 *   Element 2: 30
 *   Element 3: 40
 *   10 20 30 40
 *   5 10 20 30 40
 *   Enter a value to search: 30
 *   Value 30 found at index 4
 *   Enter a number to delete: 1
 *   5 10 20 30 40
 *   Deleted value: 5
 *
 * (The program inserts the value 5 at index 0 twice, so before the search the
 *  list is 5 5 10 20 30 40 and 30 sits at index 4. Deleting index 1 removes
 *  the duplicate 5, leaving 5 10 20 30 40.)
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int *arr;
    int size;
    int capacity;
} arraylist;

void init(arraylist *list, int capacity){
    list->arr = (int*)malloc(capacity * sizeof(int));
    list->size = 0;
    list->capacity = capacity;

    int n;
    printf("How many elements (0 to %d)? ", capacity);
    scanf("%d", &n);
    if(n < 0 || n > capacity){
        printf("Invalid count, starting empty\n");
        return;
    }
    for(int i = 0; i < n; i++){
        printf("Element %d: ", i);
        scanf("%d", &list->arr[i]);
        list->size++;
    }
    printf("list size: %d\n", list->size);
}

void insert(arraylist *list, int index, int value){
    if(list->size >= list->capacity){
        printf("Array is full\n");
        return;
    }
    if(index < 0 || index > list->size){
        printf("Index out of bounds\n");
        return;
    }
    for(int i = list->size; i > index; i--){
        list->arr[i] = list->arr[i-1];
    }
    list->arr[index] = value;
    list->size++;
}

int delete(arraylist *list, int index, int *n){
    if(index < 0 || index >= list->size){
        printf("Index out of bounds\n");
        return 1;
    }
    *n = list->arr[index];
    for(int i = index; i < list->size - 1; i++){
        list->arr[i] = list->arr[i+1];
    }
    list->size--;
    return 0;
}

int search(arraylist *list, int value){
    for(int i = 0; i < list->size; i++){
        if(list->arr[i] == value){
            return i;
        }
    }
    return -1;
}

void display(arraylist *list){
    for(int i = 0; i < list->size; i++){
        printf("%d ", list->arr[i]);
    }
    printf("\n");
}

int main(){
    arraylist list;
    int number;
    init(&list, 10);
    display(&list);
    insert(&list, 0, 5);
    display(&list);
    insert(&list, 0, 5);
    printf("Enter a value to search: ");
    scanf("%d", &number);
    int pos = search(&list, number);
    if(pos == -1){
        printf("Value %d not found\n", number);
    } else {
        printf("Value %d found at index %d\n", number, pos);
    }
    printf("Enter a number to delete: ");
    scanf("%d", &number);
    int status = delete(&list, number, &number);
    display(&list);
    if(status == 0){
        printf("Deleted value: %d\n", number);
    }
    return 0;
}