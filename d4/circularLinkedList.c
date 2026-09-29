/*
 * Q. Write a C program to implement a Circular Singly Linked List (the last
 *    node points back to the head) with the operations:
 *      - create the list with n nodes read from the user
 *      - display the list
 *      - insert a node at a given position (beginning, middle or end)
 *      - delete a node at a given position
 *      - search for a value and report its position
 *
 * Sample Input:
 *   4
 *   10 20 30 40
 *   77 2     (value and position to insert -- value comes first)
 *   30       (value to search)
 *   0        (position to delete)
 *
 * Sample Output:
 *   Enter the number of nodes: 4
 *   Enter element 1: 10
 *   Enter element 2: 20
 *   Enter element 3: 30
 *   Enter element 4: 40
 *   created  : 10 -> 20 -> 30 -> 40 -> (head 10)
 *   Enter the value and position to insert: 77 2
 *   inserted : 10 -> 20 -> 77 -> 30 -> 40 -> (head 10)
 *   Enter the value to search: 30
 *   value 30 found at position 3
 *   Enter the position to delete: 0
 *   delete at position 0 -> ok
 *   deleted  : 20 -> 77 -> 30 -> 40 -> (head 20)
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
    printf("Enter element %d: ", i + 1);
    scanf("%d", &cur->data);

    if (*h == NULL) {
      *h = cur;
      cur->next = cur;
    } else {
      cur->next = *h;
      last->next = cur;
    }
    last = cur;
  }
}

void display(node *h) {
  if (h == NULL) {
    printf("list is empty\n");
    return;
  }

  node *cur = h;
  do {
    printf("%d -> ", cur->data);
    cur = cur->next;
  } while (cur != h);
  printf("(head %d)\n", h->data);
}

int length(node *h) {
  if (h == NULL)
    return 0;

  int n = 0;
  node *cur = h;
  do {
    n++;
    cur = cur->next;
  } while (cur != h);
  return n;
}

void insert(node **h, int pos, int data) {
  node *cur = malloc(sizeof(node));
  cur->data = data;

  if (*h == NULL) {
    cur->next = cur;
    *h = cur;
    return;
  }

  node *last = *h;
  while (last->next != *h)
    last = last->next;

  if (pos <= 0) {
    cur->next = *h;
    last->next = cur;
    *h = cur;
    return;
  }

  node *prev = *h;
  for (int i = 0; i < pos - 1 && prev->next != *h; i++)
    prev = prev->next;

  cur->next = prev->next;
  prev->next = cur;
}

int delete_pos(node **h, int pos) {
  if (*h == NULL || pos < 0)
    return 0;

  int n = length(*h);
  if (pos >= n)
    return 0;

  node *dead;

  if (pos == 0) {
    dead = *h;
    if (n == 1) {
      *h = NULL;
    } else {
      node *last = *h;
      while (last->next != *h)
        last = last->next;
      last->next = dead->next;
      *h = dead->next;
    }
    free(dead);
    return 1;
  }

  node *prev = *h;
  for (int i = 0; i < pos - 1; i++)
    prev = prev->next;

  dead = prev->next;
  prev->next = dead->next;
  free(dead);
  return 1;
}

int search(node *h, int data) {
  if (h == NULL)
    return -1;

  int i = 0;
  node *cur = h;
  do {
    if (cur->data == data)
      return i;
    cur = cur->next;
    i++;
  } while (cur != h);
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

  printf("Enter the value and position to insert: ");
  scanf("%d %d", &val, &pos);
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
