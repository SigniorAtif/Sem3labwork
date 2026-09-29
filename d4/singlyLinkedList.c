/*
 * Q. Write a C program to implement a Singly Linked List with the operations:
 *      - create the list with n nodes read from the user
 *      - display the list
 *      - insert a node at a given position (beginning, middle or end)
 *      - delete a node at a given position
 *      - search for a value and report its position
 *
 * Sample Input:
 *   4
 *   10 20 30 40
 *   2        (position to insert at)
 *   77       (value to insert)
 *   30       (value to search)
 *   0        (position to delete)
 *
 * Sample Output:
 *   Enter the number of nodes: 4
 *   Enter element 1: 10
 *   Enter element 2: 20
 *   Enter element 3: 30
 *   Enter element 4: 40
 *   created  : 10 -> 20 -> 30 -> 40 -> NULL
 *   Enter the position to insert at: 2
 *   Enter the value to insert: 77
 *   inserted : 10 -> 20 -> 77 -> 30 -> 40 -> NULL
 *   Enter the value to search: 30
 *   value 30 found at position 3
 *   Enter the position to delete: 0
 *   delete at position 0 -> ok
 *   deleted  : 20 -> 77 -> 30 -> 40 -> NULL
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  int data;
  struct node *next;
} node;

void create(node **h, int no) {
  node *last = *h;

  for (int i = 0; i < no; i++) {
    node *cur = malloc(sizeof(node));
    if (cur == NULL) {
      fprintf(stderr, "out of memory\n");
      exit(1);
    }
    printf("Enter element %d: ", i + 1);
    scanf("%d", &cur->data);
    cur->next = NULL;

    if (*h == NULL)
      *h = cur;
    else
      last->next = cur;
    last = cur;
  }
}

void display(node *h) {
  if (h == NULL) {
    printf("list is empty\n");
    return;
  }
  for (node *cur = h; cur != NULL; cur = cur->next)
    printf("%d -> ", cur->data);
  printf("NULL\n");
}

void insert(node **h, int pos, int data) {
  node *cur = malloc(sizeof(node));
  if (cur == NULL) {
    fprintf(stderr, "out of memory\n");
    exit(1);
  }
  cur->data = data;
  cur->next = NULL;

  if (pos <= 0 || *h == NULL) {
    cur->next = *h;
    *h = cur;
    return;
  }

  node *prev = *h;
  for (int i = 0; i < pos - 1 && prev->next != NULL; i++)
    prev = prev->next;

  cur->next = prev->next;
  prev->next = cur;
}

int delete_pos(node **h, int pos) {
  if (*h == NULL || pos < 0)
    return 0;

  node *dead;

  if (pos == 0) {
    dead = *h;
    *h = dead->next;
    free(dead);
    return 1;
  }

  node *prev = *h;
  for (int i = 0; i < pos - 1; i++) {
    prev = prev->next;
    if (prev == NULL)
      return 0;
  }

  dead = prev->next;
  if (dead == NULL)
    return 0;

  prev->next = dead->next;
  free(dead);
  return 1;
}


int search(node *h, int data) {
  int i = 0;
  for (node *cur = h; cur != NULL; cur = cur->next, i++)
    if (cur->data == data)
      return i;
  return -1;
}

int main() {
  node *h = NULL;
  int n, pos, val;

  printf("Enter the number of nodes: ");
  scanf("%d", &n);
  create(&h, n);
  printf("created  : ");
  display(h);

  printf("Enter the position to insert at: ");
  scanf("%d", &pos);
  printf("Enter the value to insert: ");
  scanf("%d", &val);
  insert(&h, pos, val);
  printf("inserted : ");
  display(h);

  printf("Enter the value to search: ");
  scanf("%d", &val);
  pos = search(h, val);
  if (pos == -1)
    printf("value %d not found\n", val);
  else
    printf("value %d found at position %d\n", val, pos);

  printf("Enter the position to delete: ");
  scanf("%d", &pos);
  printf("delete at position %d -> %s\n", pos,
         delete_pos(&h, pos) ? "ok" : "not found");
  printf("deleted  : ");
  display(h);

  return 0;
}
