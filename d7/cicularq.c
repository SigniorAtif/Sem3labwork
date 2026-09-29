// implementation of a circular queue using array

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

int is_full(queue *q) { return (q->rear + 1) % SIZE == q->front; }

int enqueue(queue *q, int val) {
  if (is_full(q))
    return 1;

  if (is_empty(q))
    q->front = 0;

  q->rear = (q->rear + 1) % SIZE;
  q->data[q->rear] = val;
  return 0;
}

int dequeue(queue *q, int *val) {
  if (is_empty(q))
    return 1;

  *val = q->data[q->front];

  if (q->front == q->rear)
    init(q);
  else
    q->front = (q->front + 1) % SIZE;

  return 0;
}

void display(queue *q) {
  if (is_empty(q)) {
    printf("queue is empty\n");
    return;
  }

  for (int i = q->front;; i = (i + 1) % SIZE) {
    printf("%d ", q->data[i]);
    if (i == q->rear)
      break;
  }
  printf("\n");
}

int main() {
  queue q;
  int n, val;

  init(&q);

  printf("Enter the number of values to insert: ");
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    printf("Enter the value: ");
    scanf("%d", &val);
    if (enqueue(&q, val))
      printf("queue is full\n");
  }
  printf("queue    : ");
  display(&q);

  if (dequeue(&q, &val))
    printf("queue is empty\n");
  else
    printf("deleted %d\n", val);
  printf("queue    : ");
  display(&q);

  printf("Enter the value to insert: ");
  scanf("%d", &val);
  if (enqueue(&q, val))
    printf("queue is full\n");
  printf("queue    : ");
  display(&q);

  return 0;
}
