/*
 * Q. Write a C program to implement a Doubly Linked List with the operations:
 *      - create the list with n nodes read from the user
 *      - display the list in forward and in reverse order
 *      - find the length of the list
 *      - insert a node at a given position (beginning, middle or end)
 *      - delete a node at a given position
 *      - delete a node by its value
 *      - search for a value and report its position
 *
 * Sample Input:
 *   4
 *   10 20 30 40
 *   2        (position to insert at)
 *   77       (value to insert)
 *   30       (value to search)
 *   0        (position to delete)
 *   77       (value to delete)
 *
 * Sample Output:
 *   Enter the number of nodes: 4
 *   Enter element 1: 10
 *   Enter element 2: 20
 *   Enter element 3: 30
 *   Enter element 4: 40
 *   created  : NULL <-> 10 <-> 20 <-> 30 <-> 40 <-> NULL
 *   reversed : NULL <-> 40 <-> 30 <-> 20 <-> 10 <-> NULL
 *   length   : 4
 *   Enter the position to insert at: 2
 *   Enter the value to insert: 77
 *   inserted : NULL <-> 10 <-> 20 <-> 77 <-> 30 <-> 40 <-> NULL
 *   reversed : NULL <-> 40 <-> 30 <-> 77 <-> 20 <-> 10 <-> NULL
 *   Enter the value to search: 30
 *   value 30 found at position 3
 *   Enter the position to delete: 0
 *   delete at position 0 -> ok
 *   deleted  : NULL <-> 20 <-> 77 <-> 30 <-> 40 <-> NULL
 *   Enter the value to delete: 77
 *   delete value 77 -> ok
 *   deleted  : NULL <-> 20 <-> 30 <-> 40 <-> NULL
 *   reversed : NULL <-> 40 <-> 30 <-> 20 <-> NULL
 *   length   : 3
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  int data;
  struct node *prev;
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
    cur->prev = last;
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
  printf("NULL <-> ");
  for (node *cur = h; cur != NULL; cur = cur->next)
    printf("%d <-> ", cur->data);
  printf("NULL\n");
}

void display_rev(node *h) {
  if (h == NULL) {
    printf("list is empty\n");
    return;
  }

  node *last = h;
  while (last->next != NULL)
    last = last->next;

  printf("NULL <-> ");
  for (node *cur = last; cur != NULL; cur = cur->prev)
    printf("%d <-> ", cur->data);
  printf("NULL\n");
}

int length(node *h) {
  int n = 0;
  for (node *cur = h; cur != NULL; cur = cur->next)
    n++;
  return n;
}

void insert(node **h, int pos, int data) {
  node *cur = malloc(sizeof(node));
  if (cur == NULL) {
    fprintf(stderr, "out of memory\n");
    exit(1);
  }
  cur->data = data;
  cur->prev = NULL;
  cur->next = NULL;

  if (pos <= 0 || *h == NULL) {
    cur->next = *h;
    if (*h != NULL)
      (*h)->prev = cur;
    *h = cur;
    return;
  }

  node *prev = *h;
  for (int i = 0; i < pos - 1 && prev->next != NULL; i++)
    prev = prev->next;

  cur->next = prev->next;
  cur->prev = prev;
  if (prev->next != NULL)
    prev->next->prev = cur;
  prev->next = cur;
}

int delete_pos(node **h, int pos) {
  if (*h == NULL || pos < 0)
    return 0;

  node *dead = *h;
  for (int i = 0; i < pos; i++) {
    dead = dead->next;
    if (dead == NULL)
      return 0;
  }

  if (dead->prev != NULL)
    dead->prev->next = dead->next;
  else
    *h = dead->next;

  if (dead->next != NULL)
    dead->next->prev = dead->prev;

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
  printf("reversed : ");
  display_rev(h);

  printf("Enter the position and value to insert: ");
  scanf("%d %d", &pos, &val);
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
