/*
    write a program to implement a double ended queue using array based off of the chunk input and deletion as we did in array list but here. all chunks should be together and cannot be broken in a sense that it is circular so at the end it cannot be that 2 3's are at the end and there is 1 3 which is at the 0th position cuz its circular isntead, if there is space in total to accomodate the new chunk but if the side asked to insert at doesnt have enough space shift the existing data enough to make spcae to accomodate the new chunk
    now we need to implement the shift opimally where in a case there they might ask us to imput 7 to the rear end of the queue but if there is only 1 blank space at the rear of the queue and 6 blank space at the start instead of shifting everything to the right its more optimal to shift everything left by 1 and then place everything at the front and as it is circular it would loop back from the the front index to the end index which would be towards the left and vise versa for the front end
*/

#include <stdio.h>

#define SIZE 10



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

int count(queue *q) { return is_empty(q) ? 0 : q->rear - q->front + 1; }

int enqueue(queue *q, int *vals, int k, int side) {
  if (k <= 0 || count(q) + k > SIZE)
    return 1;

  if (is_empty(q)) {
    q->front = 0;
    q->rear = -1;
  }

  if (side == 0) {
    int space = q->front;
    if (space < k) {
      int shift = k - space;
      for (int i = q->rear; i >= q->front; i--)
        q->data[i + shift] = q->data[i];
      q->front += shift;
      q->rear += shift;
    }
    q->front -= k;
    for (int i = 0; i < k; i++)
      q->data[q->front + i] = vals[i];
  } else {
    int space = SIZE - 1 - q->rear;
    if (space < k) {
      int shift = k - space;
      for (int i = q->front; i <= q->rear; i++)
        q->data[i - shift] = q->data[i];
      q->front -= shift;
      q->rear -= shift;
    }
    for (int i = 0; i < k; i++)
      q->data[++q->rear] = vals[i];
  }

  return 0;
}

int dequeue(queue *q, int *vals, int k, int side) {
  if (k <= 0 || k > count(q))
    return 1;

  if (side == 0) {
    for (int i = 0; i < k; i++)
      vals[i] = q->data[q->front + i];
    q->front += k;
  } else {
    for (int i = 0; i < k; i++)
      vals[i] = q->data[q->rear - k + 1 + i];
    q->rear -= k;
  }

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

void read_chunk(int *vals, int *k, int *side) {
  printf("Enter the chunk size (1 to %d): ", SIZE);
  scanf("%d", k);
  if (*k < 1 || *k > SIZE) {
    *k = 0;
    return;
  }
  printf("Enter %d values: ", *k);
  for (int i = 0; i < *k; i++)
    scanf("%d", &vals[i]);
  printf("Enter the side (0-front 1-rear): ");
  scanf("%d", side);
}

int main() {
  queue q;
  int vals[SIZE], k, side;

  init(&q);

  read_chunk(vals, &k, &side);
  if (enqueue(&q, vals, k, side))
    printf("not enough space for the chunk\n");
  printf("queue    : ");
  display(&q);

  printf("Enter the number of values and side to delete (0-front 1-rear): ");
  scanf("%d %d", &k, &side);
  if (dequeue(&q, vals, k, side))
    printf("not enough values to delete\n");
  else {
    printf("deleted  : ");
    for (int i = 0; i < k; i++)
      printf("%d ", vals[i]);
    printf("\n");
  }
  printf("queue    : ");
  display(&q);

  read_chunk(vals, &k, &side);
  if (enqueue(&q, vals, k, side))
    printf("not enough space for the chunk\n");
  printf("queue    : ");
  display(&q);

  return 0;
}
