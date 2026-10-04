/*
 * Q4. Implement the queue using array and linked list.
 *     The same values are fed to a circular array queue (size 5) and a linked
 *     list queue, so the array overflow is visible next to the unbounded list.
 *
 * Sample Input:
 *   7
 *   1 2 3 4 5 6 7
 *   3
 *
 * Sample Output:
 *   Enter the number of values to enqueue: 7
 *   Enter 7 values: 1 2 3 4 5 6 7
 *   array queue overflow, 6 not inserted
 *   array queue overflow, 7 not inserted
 *   array queue : 1 2 3 4 5
 *   list queue  : 1 2 3 4 5 6 7
 *   Enter the number of dequeues: 3
 *   array dequeued 1
 *   list  dequeued 1
 *   array dequeued 2
 *   list  dequeued 2
 *   array dequeued 3
 *   list  dequeued 3
 *   array queue : 4 5
 *   list queue  : 4 5 6 7
 */

#include <stdio.h>
#include <stdlib.h>

#define SIZE 5

/* ---------- circular array queue ---------- */
typedef struct aqueue {
  int data[SIZE];
  int front, rear, count;
} aqueue;

void a_init(aqueue *q) { q->front = 0; q->rear = -1; q->count = 0; }

int a_enqueue(aqueue *q, int val) {
  if (q->count == SIZE)
    return 0;
  q->rear = (q->rear + 1) % SIZE;
  q->data[q->rear] = val;
  q->count++;
  return 1;
}

int a_dequeue(aqueue *q, int *val) {
  if (q->count == 0)
    return 0;
  *val = q->data[q->front];
  q->front = (q->front + 1) % SIZE;
  q->count--;
  return 1;
}

void a_display(aqueue *q) {
  printf("array queue :");
  for (int i = 0; i < q->count; i++)
    printf(" %d", q->data[(q->front + i) % SIZE]);
  printf("\n");
}

/* ---------- linked list queue ---------- */
typedef struct node {
  int data;
  struct node *next;
} node;

typedef struct lqueue {
  node *front, *rear;
} lqueue;

void l_init(lqueue *q) { q->front = q->rear = NULL; }

int l_enqueue(lqueue *q, int val) {
  node *n = malloc(sizeof *n);
  if (!n)
    return 0;
  n->data = val;
  n->next = NULL;
  if (q->rear)
    q->rear->next = n;
  else
    q->front = n;
  q->rear = n;
  return 1;
}

int l_dequeue(lqueue *q, int *val) {
  if (!q->front)
    return 0;
  node *t = q->front;
  *val = t->data;
  q->front = t->next;
  if (!q->front)
    q->rear = NULL;
  free(t);
  return 1;
}

void l_display(lqueue *q) {
  printf("list queue  :");
  for (node *t = q->front; t; t = t->next)
    printf(" %d", t->data);
  printf("\n");
}

int main(void) {
  aqueue aq;
  lqueue lq;
  int n, val;
  a_init(&aq);
  l_init(&lq);

  printf("Enter the number of values to enqueue: ");
  if (scanf("%d", &n) != 1)
    return 1;
  printf("Enter %d values: ", n);
  for (int i = 0; i < n; i++) {
    if (scanf("%d", &val) != 1)
      return 1;
    if (!a_enqueue(&aq, val))
      printf("array queue overflow, %d not inserted\n", val);
    l_enqueue(&lq, val);
  }
  a_display(&aq);
  l_display(&lq);

  printf("Enter the number of dequeues: ");
  if (scanf("%d", &n) != 1)
    return 1;
  for (int i = 0; i < n; i++) {
    if (a_dequeue(&aq, &val))
      printf("array dequeued %d\n", val);
    else
      printf("array queue underflow\n");
    if (l_dequeue(&lq, &val))
      printf("list  dequeued %d\n", val);
    else
      printf("list queue underflow\n");
  }
  a_display(&aq);
  l_display(&lq);

  while (l_dequeue(&lq, &val))
    ;
  return 0;
}
