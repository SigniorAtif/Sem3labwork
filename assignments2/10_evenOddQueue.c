/*
 * Q10. Implement the queue with the following criteria.
 *      (a) Two fixed size arrays are used: one for inserting even elements and
 *          another for inserting odd elements.
 *      (b) Insertion: an even element goes to the rear of the even queue; if
 *          that array is full it goes to the rear of the odd queue. Similarly
 *          for odd elements.
 *      (c) Deletion: delete the front element of the array having the maximum
 *          number of elements currently present (even queue on a tie).
 *
 * Sample Input:
 *   10
 *   2 4 6 8 10 12 1 3 5 7
 *   3
 *
 * Sample Output:
 *   each array holds 4 elements
 *   Enter the number of values to insert: 10
 *   Enter 10 values: 2 4 6 8 10 12 1 3 5 7
 *   both queues full, 5 not inserted
 *   both queues full, 7 not inserted
 *   even (4) : 2 4 6 8
 *   odd  (4) : 10 12 1 3
 *   Enter the number of deletions: 3
 *   deleted 2 from even queue
 *   deleted 10 from odd queue
 *   deleted 4 from even queue
 *   even (2) : 6 8
 *   odd  (3) : 12 1 3
 */

#include <stdio.h>

#define SIZE 4

typedef struct queue {
  int data[SIZE];
  int front, rear, count;
  const char *name;
} queue;

void init(queue *q, const char *name) {
  q->front = 0;
  q->rear = -1;
  q->count = 0;
  q->name = name;
}

int is_full(queue *q) { return q->count == SIZE; }

void enqueue(queue *q, int val) {
  q->rear = (q->rear + 1) % SIZE;
  q->data[q->rear] = val;
  q->count++;
}

int dequeue(queue *q) {
  int val = q->data[q->front];
  q->front = (q->front + 1) % SIZE;
  q->count--;
  return val;
}

/* even goes to the even queue, odd to the odd queue; if the home queue is
 * full the value spills into the rear of the other one */
int insert(queue *even, queue *odd, int val) {
  queue *home = (val % 2 == 0) ? even : odd;
  queue *other = (home == even) ? odd : even;
  if (!is_full(home))
    enqueue(home, val);
  else if (!is_full(other))
    enqueue(other, val);
  else
    return 0;
  return 1;
}

/* removes the front of the queue holding more elements (even on a tie) */
int delete(queue *even, queue *odd, int *val, const char **from) {
  if (even->count == 0 && odd->count == 0)
    return 0;
  queue *q = (even->count >= odd->count) ? even : odd;
  *from = q->name;
  *val = dequeue(q);
  return 1;
}

void display(queue *q) {
  printf("%-5s(%d) :", q->name, q->count);
  for (int i = 0; i < q->count; i++)
    printf(" %d", q->data[(q->front + i) % SIZE]);
  printf("\n");
}

int main(void) {
  queue even, odd;
  int n, val;
  const char *from;
  init(&even, "even");
  init(&odd, "odd");

  printf("each array holds %d elements\n", SIZE);
  printf("Enter the number of values to insert: ");
  if (scanf("%d", &n) != 1)
    return 1;
  printf("Enter %d values: ", n);
  for (int i = 0; i < n; i++) {
    if (scanf("%d", &val) != 1)
      return 1;
    if (!insert(&even, &odd, val))
      printf("both queues full, %d not inserted\n", val);
  }
  display(&even);
  display(&odd);

  printf("Enter the number of deletions: ");
  if (scanf("%d", &n) != 1)
    return 1;
  for (int i = 0; i < n; i++) {
    if (!delete(&even, &odd, &val, &from)) {
      printf("both queues empty\n");
      break;
    }
    printf("deleted %d from %s queue\n", val, from);
  }
  display(&even);
  display(&odd);
  return 0;
}
