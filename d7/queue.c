#include<stdio.h>

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

int is_full(queue *q) { return q->rear == SIZE - 1; }

int enqueue(queue *q, int val) {
  if (is_full(q))
    return 0;

  if (is_empty(q))
    q->front = 0;

  q->data[++q->rear] = val;
  return 1;
}

int dequeue(queue *q, int *val) {
  if (is_empty(q))
    return 1;

  *val = q->data[q->front];

  if (q->front == q->rear)
    init(q);
  else
    q->front++;

  return 0;
}

void display(queue *q) {
  if (is_empty(q)) {
    printf("queue is empty\n");
    return;
  }

  for (int i = q->front; i <= q->rear; i++)
    printf("%d%s", q->data[i], i == q->rear ? "\n" : " <- ");
}

int main(){
    queue q;
    init(&q);
    
    enqueue(&q, 10);
    enqueue(&q, 20);
    enqueue(&q, 30);
    display(&q);
    
    int val;
    dequeue(&q, &val);
    printf("Dequeued: %d\n", val);
    display(&q);
    
    return 0;
}