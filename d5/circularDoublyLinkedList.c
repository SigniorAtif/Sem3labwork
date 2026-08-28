/*
 * Q. Write a C program to implement a Circular Doubly Linked List that takes
 *    its data from the user, and perform the operations:
 *      - create the list with n nodes read from the keyboard
 *      - display the list in forward and in reverse order
 *      - find the length of the list
 *      - insert a node at a position entered by the user (and at the front
 *        and the end)
 *      - delete the node at the front, at a position entered by the user,
 *        and at the end
 *      - search for a value and report its position
 *
 *    In a circular doubly linked list the last node's next points back to the
 *    head and the head's prv points to the last node, so the list has no NULL
 *    link at either end; [H] below marks the head to show the wrap-around.
 *
 * Sample Input:
 *   4
 *   10 20 30 40
 *   2        (position to insert at)
 *   77       (value to insert)
 *   1        (position to delete)
 *
 * Sample Output:
 *   Enter the number of elements: 4
 *   Enter number 1: 10
 *   Enter number 2: 20
 *   Enter number 3: 30
 *   Enter number 4: 40
 *   created  : [H] <-> 10 <-> 20 <-> 30 <-> 40 <-> [H]
 *   reversed : [H] <-> 40 <-> 30 <-> 20 <-> 10 <-> [H]
 *   length   : 4
 *   Enter the pos: 2
 *   Enter the val: 77
 *   inserted : [H] <-> 555 <-> 10 <-> 20 <-> 77 <-> 30 <-> 40 <-> 999 <-> [H]
 *   reversed : [H] <-> 999 <-> 40 <-> 30 <-> 77 <-> 20 <-> 10 <-> 555 <-> [H]
 *   search 555 -> pos 0
 *   search 42  -> pos -1
 *   Enter the pos to delete: 1
 *   deleted position 0, 1 and last:
 *   [H] <-> 10 <-> 77 <-> 30 <-> 40 <-> [H]
 *   reversed : [H] <-> 40 <-> 30 <-> 77 <-> 10 <-> [H]
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  struct node *prv;
  int val;
  struct node *next;
} node;

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

void create(node **h, int no) {
  for (int i = 0; i < no; i++) {
    node *cur = malloc(sizeof(node));
    printf("Enter number %d: ", i + 1);
    scanf("%d", &(cur->val));

    if (*h == NULL) {
      cur->prv = cur;
      cur->next = cur;
      *h = cur;
    } else {
      node *last = (*h)->prv;
      cur->prv = last;
      cur->next = *h;
      last->next = cur;
      (*h)->prv = cur;
    }
  }
}

void display(node *h) {
  if (h == NULL) {
    printf("list is empty\n");
    return;
  }

  printf("[H] <-> ");
  node *cur = h;
  do {
    printf("%d <-> ", cur->val);
    cur = cur->next;
  } while (cur != h);
  printf("[H]\n");
}

void display_rev(node *h) {
  if (h == NULL) {
    printf("list is empty\n");
    return;
  }

  node *last = h->prv;
  printf("[H] <-> ");
  node *cur = last;
  do {
    printf("%d <-> ", cur->val);
    cur = cur->prv;
  } while (cur != last);
  printf("[H]\n");
}

void insert(node **h, int pos, int val) {
  node *cur = malloc(sizeof(node));
  cur->val = val;

  if (*h == NULL) {
    cur->prv = cur;
    cur->next = cur;
    *h = cur;
    return;
  }

  int len = length(*h);
  if (pos < 0)
    pos = 0;
  if (pos > len)
    pos = len;

  /* walk from the last node, so pos == 0 and pos == len both land on it */
  node *prv = (*h)->prv;
  for (int i = 0; i < pos; i++)
    prv = prv->next;

  cur->prv = prv;
  cur->next = prv->next;
  prv->next->prv = cur;
  prv->next = cur;

  if (pos == 0)
    *h = cur;
}

int delete_pos(node **h, int pos) {
  if (*h == NULL || pos < 0 || pos >= length(*h))
    return 0;

  node *dead = *h;
  for (int i = 0; i < pos; i++)
    dead = dead->next;

  if (dead->next == dead) {         /* the only node in the list */
    *h = NULL;
  } else {
    dead->prv->next = dead->next;
    dead->next->prv = dead->prv;
    if (dead == *h)
      *h = dead->next;
  }

  free(dead);
  return 1;
}

int search(node *h, int val) {
  if (h == NULL)
    return -1;

  int i = 0;
  node *cur = h;
  do {
    if (cur->val == val)
      return i;
    cur = cur->next;
    i++;
  } while (cur != h);
  return -1;
}

int main() {
  node *h = NULL;

  int n;
  printf("Enter the number of elements: ");
  scanf("%d",&n);
  create(&h, n);
  printf("created  : ");
  display(h);
  printf("reversed : ");
  display_rev(h);
  printf("length   : %d\n", length(h));

  int pos, val;
  printf("Enter the val and pos: ");
  scanf("%d %d",&val, &pos);

  insert(&h, pos, val);

  printf("inserted : ");
  display(h);

  printf("search 555 -> pos %d\n", search(h, 555));
  printf("search 42  -> pos %d\n", search(h, 42));

  printf("Enter the pos to delete: ");
  scanf("%d",&pos);

  delete_pos(&h, pos); 
  printf("deleted position %d\n",pos);
  display(h);

  return 0;
}
