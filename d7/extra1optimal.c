/*
    write a program to implement a double ended queue using array based off of the chunk input and deletion as we did in array list but here. all chunks should be together and cannot be broken in a sense that it is circular so at the end it cannot be that 2 3's are at the end and there is 1 3 which is at the 0th position cuz its circular isntead, if there is space in total to accomodate the new chunk but if the side asked to insert at doesnt have enough space shift the existing data enough to make spcae to accomodate the new chunk
    now we need to implement the shift opimally where in a case there they might ask us to imput 7 to the rear end of the queue but if there is only 1 blank space at the rear of the queue and 6 blank space at the start instead of shifting everything to the right its more optimal to shift everything left by 1 and then place everything at the front and as it is circular it would loop back from the the front index to the end index which would be towards the left and vise versa for the front end
    also in the output along with printing the queue in order also print the queue array from 0 to last so we know whats going on 
*/

#include <stdio.h>

#define SIZE 10

typedef struct queue {
  int data[SIZE];
  int head[SIZE]; 
  int front;
  int n;
} queue;

void init(queue *q) {
  q->front = -1;
  q->n = 0;
}

int is_empty(queue *q) { return q->n == 0; }

int count(queue *q) { return q->n; }

int rear(queue *q) { return (q->front + q->n - 1) % SIZE; }

int wrap(int i) { return ((i % SIZE) + SIZE) % SIZE; }

int fits(queue *q, int k, int side, int p) {
  int total = q->n + k;
  for (int j = 1; j < total; j++) {
    if (wrap(p + j) != 0)
      continue;
    if (side == 0)
      return j < k ? 0 : q->head[wrap(q->front + j - k)];
    return j < q->n ? q->head[wrap(q->front + j)] : j == q->n;
  }
  return 1;
}

// returns the shift applied to the existing data (+ right, - left)
int enqueue(queue *q, int *vals, int k, int side, int *shift) {
  if (k <= 0 || q->n + k > SIZE)
    return 1;

  if (is_empty(q)) {
    q->front = 0;
    for (int i = 0; i < k; i++) {
      q->data[i] = vals[i];
      q->head[i] = i == 0;
    }
    q->n = k;
    *shift = 0;
    return 0;
  }

  // try the smallest shift first, in both directions
  int d = 0, found = 0;
  for (int s = 0; s < SIZE && !found; s++) {
    int tries[2] = {side == 0 ? s : -s, side == 0 ? -s : s};
    for (int t = 0; t < 2 && !found; t++) {
      d = tries[t];
      int p = wrap(q->front + d - (side == 0 ? k : 0));
      found = fits(q, k, side, p);
    }
  }
  if (!found)
    return 1;

  if (d != 0) {
    int tmp[SIZE], tmph[SIZE];
    for (int i = 0; i < q->n; i++) {
      tmp[i] = q->data[wrap(q->front + i)];
      tmph[i] = q->head[wrap(q->front + i)];
    }
    q->front = wrap(q->front + d);
    for (int i = 0; i < q->n; i++) {
      q->data[wrap(q->front + i)] = tmp[i];
      q->head[wrap(q->front + i)] = tmph[i];
    }
  }

  int start = side == 0 ? wrap(q->front - k) : wrap(q->front + q->n);
  for (int i = 0; i < k; i++) {
    q->data[start + i] = vals[i];
    q->head[start + i] = i == 0;
  }
  if (side == 0)
    q->front = start;
  q->n += k;
  *shift = d;

  return 0;
}

int dequeue(queue *q, int *vals, int k, int side) {
  if (k <= 0 || k > count(q))
    return 1;

  if (side == 0) {
    for (int i = 0; i < k; i++)
      vals[i] = q->data[wrap(q->front + i)];
    q->front = wrap(q->front + k);
  } else {
    for (int i = 0; i < k; i++)
      vals[i] = q->data[wrap(q->front + q->n - k + i)];
  }
  q->n -= k;

  if (is_empty(q))
    init(q);
  else
    q->head[q->front] = 1; // leftover of a split chunk is still a chunk

  return 0;
}

void display(queue *q) {
  printf("queue    : ");
  if (is_empty(q))
    printf("empty");
  for (int i = 0; i < q->n; i++)
    printf("%d ", q->data[wrap(q->front + i)]);
  printf("\n");

  printf("array    : ");
  for (int i = 0; i < SIZE; i++) {
    int used = !is_empty(q) && wrap(i - q->front) < q->n;
    if (!used)
      printf("_ ");
    else
      printf("%s%d ", q->head[i] ? "|" : "", q->data[i]);
  }
  if (!is_empty(q))
    printf("  (front=%d rear=%d)", q->front, rear(q));
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
  int vals[SIZE], k, side, shift, choice;

  init(&q);

  while (1) {
    printf("\n1-insert chunk 2-delete 3-exit: ");
    if (scanf("%d", &choice) != 1 || choice == 3)
      break;

    if (choice == 1) {
      read_chunk(vals, &k, &side);
      if (enqueue(&q, vals, k, side, &shift))
        printf("not enough space for the chunk\n");
      else if (shift)
        printf("shifted  : %d %s\n", shift < 0 ? -shift : shift,
               shift < 0 ? "left" : "right");
    } else if (choice == 2) {
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
    }
    display(&q);
  }

  return 0;
}
