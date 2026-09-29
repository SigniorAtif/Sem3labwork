/*
 * Q. Write a C program to implement a Double Ended Queue (Deque) using an
 *    array that takes its data from the user, and perform the operations:
 *      - insert n values, each at a side chosen by the user (front/rear)
 *      - display the queue
 *      - delete a value from a side chosen by the user
 *      - insert one more value at a side chosen by the user
 *
 * Sample Input:
 *   3
 *   10 0    (value and side -- 0 front, 1 rear)
 *   20 1
 *   30 0
 *   0        (side to delete from)
 *   99 1     (value and side to insert)
 *
 * Sample Output:
 *   Enter the number of values to insert: 3
 *   Enter the value and side (0-front 1-rear): 10 0
 *   Enter the value and side (0-front 1-rear): 20 1
 *   Enter the value and side (0-front 1-rear): 30 0
 *   queue    : 30 10 20
 *   Enter the side to delete from (0-front 1-rear): 0
 *   deleted 30
 *   queue    : 10 20
 *   Enter the value and side to insert (0-front 1-rear): 99 1
 *   queue    : 10 20 99
 */

#include <stdio.h>

#define SIZE 5

typedef struct queue {
  int data[SIZE];
  int front;
  int rear;
} queue;

void init(queue *q) {
  q->front = -1;
  q->rear = -1;
}

int is_empty(queue *q) { return q->front == -1; }

int is_full(queue *q) { return q->rear == SIZE - 1 && q->front == 0; }

int enqueue(queue *q, int val, int side) {
  if (is_full(q))
    return 1;

  if (is_empty(q)) {
    q->data[q->front = q->rear = 0] = val;
    return 0;
  }

  if (side == 0) {
    if (q->front == 0) {
      for (int i = q->rear; i >= 0; i--)
        q->data[i + 1] = q->data[i];
      q->rear++;
      q->data[0] = val;
      return 0;
    }
    q->data[--q->front] = val;
  } else {
    if (q->rear == SIZE - 1) {
      for (int i = q->front; i <= q->rear; i++)
        q->data[i - 1] = q->data[i];
      q->front--;
      q->data[q->rear] = val;
      return 0;
    }
    q->data[++q->rear] = val;
  }

  return 0;
}

int dequeue(queue *q, int *val, int side) {
  if (is_empty(q))
    return 1;

  *val = q->data[side == 0 ? q->front++ : q->rear--];

  if (q->front > q->rear)
    init(q);

  return 0;
}

void display(queue *q) {
  if (is_empty(q)) {
    printf("queue is empty\n");
    return;
  }

  for (int i = q->front; i <= q->rear; i++)
    printf("%d ", q->data[i]);
  printf("\n");
}

int main() {
  queue q;
  int n, val, side;
  init(&q);

  printf("Enter the number of values to insert: ");
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    printf("Enter the value and side (0-front 1-rear): ");
    scanf("%d %d", &val, &side);
    if (enqueue(&q, val, side)) printf("queue is full\n");
  }
  printf("queue    : "); display(&q);

  printf("Enter the side to delete from (0-front 1-rear): ");
  scanf("%d", &side);
  if (dequeue(&q, &val, side)) printf("queue is empty\n");
  else printf("deleted %d\n", val);
  printf("queue    : "); display(&q);

  printf("Enter the value and side to insert (0-front 1-rear): ");
  scanf("%d %d", &val, &side);
  if (enqueue(&q, val, side)) printf("queue is full\n");
  printf("queue    : "); display(&q);

  return 0;
}
