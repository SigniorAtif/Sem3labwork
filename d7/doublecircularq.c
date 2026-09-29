//implementation of a double ended circular queue using array

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

int enqueue(queue *q, int val, int side) {
  if (is_full(q))
    return 1;

  if (is_empty(q)) {
    q->data[q->front = q->rear = 0] = val;
    return 0;
  }

  if (side == 0) {
    q->front = (q->front - 1 + SIZE) % SIZE;
    q->data[q->front] = val;
  } else {
    q->rear = (q->rear + 1) % SIZE;
    q->data[q->rear] = val;
  }

  return 0;
}

int dequeue(queue *q, int *val, int side) {
  if (is_empty(q))
    return 1;

  if (q->front == q->rear) {
    *val = q->data[q->front];
    init(q);
    return 0;
  }

  if (side == 0) {
    *val = q->data[q->front];
    q->front = (q->front + 1) % SIZE;
  } else {
    *val = q->data[q->rear];
    q->rear = (q->rear - 1 + SIZE) % SIZE;
  }

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
  int n, val, side;

  init(&q);

  printf("Enter the number of values to insert: ");
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    printf("Enter the value and side (0-front 1-rear): ");
    scanf("%d %d", &val, &side);
    if (enqueue(&q, val, side))
      printf("queue is full\n");
  }
  printf("queue    : ");
  display(&q);

  printf("Enter the side to delete from (0-front 1-rear): ");
  scanf("%d", &side);
  if (dequeue(&q, &val, side))
    printf("queue is empty\n");
  else
    printf("deleted %d\n", val);
  printf("queue    : ");
  display(&q);

  printf("Enter the value and side to insert (0-front 1-rear): ");
  scanf("%d %d", &val, &side);
  if (enqueue(&q, val, side))
    printf("queue is full\n");
  printf("queue    : ");
  display(&q);

  return 0;
}
