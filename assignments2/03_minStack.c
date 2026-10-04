/*
 * Q3. Write a program to implement a stack that will return the minimum
 *     element in constant time.
 *     An auxiliary array stores, for each position, the minimum of everything
 *     at or below it, so get_min() is just a lookup at top.
 *
 * Sample Input:
 *   6
 *   5 3 7 3 2 8
 *   4
 *
 * Sample Output:
 *   Enter the number of values to push: 6
 *   Enter 6 values: 5 3 7 3 2 8
 *   stack    : 8 2 3 7 3 5   (top first)
 *   min      : 2
 *   Enter the number of pops: 4
 *   popped 8, min is now 2
 *   popped 2, min is now 3
 *   popped 3, min is now 3
 *   popped 7, min is now 3
 */

#include <stdio.h>

#define SIZE 100

/* main stack plus an auxiliary stack whose top is always the current minimum */
typedef struct minstack {
  int data[SIZE];
  int mins[SIZE];
  int top;
} minstack;

void init(minstack *s) { s->top = -1; }
int is_empty(minstack *s) { return s->top == -1; }

int push(minstack *s, int val) {
  if (s->top == SIZE - 1)
    return 0;
  s->top++;
  s->data[s->top] = val;
  s->mins[s->top] = (s->top == 0 || val < s->mins[s->top - 1]) ? val : s->mins[s->top - 1];
  return 1;
}

int pop(minstack *s, int *val) {
  if (is_empty(s))
    return 0;
  *val = s->data[s->top--];
  return 1;
}

/* O(1) */
int get_min(minstack *s) { return s->mins[s->top]; }

void display(minstack *s) {
  printf("stack    :");
  for (int i = s->top; i >= 0; i--)
    printf(" %d", s->data[i]);
  printf("   (top first)\n");
}

int main(void) {
  minstack s;
  int n, val;
  init(&s);

  printf("Enter the number of values to push: ");
  if (scanf("%d", &n) != 1)
    return 1;
  printf("Enter %d values: ", n);
  for (int i = 0; i < n; i++) {
    if (scanf("%d", &val) != 1)
      return 1;
    if (!push(&s, val))
      printf("overflow, %d not pushed\n", val);
  }
  display(&s);
  if (!is_empty(&s))
    printf("min      : %d\n", get_min(&s));

  printf("Enter the number of pops: ");
  if (scanf("%d", &n) != 1)
    return 1;
  for (int i = 0; i < n; i++) {
    if (!pop(&s, &val)) {
      printf("underflow\n");
      break;
    }
    if (is_empty(&s))
      printf("popped %d, stack is empty\n", val);
    else
      printf("popped %d, min is now %d\n", val, get_min(&s));
  }
  return 0;
}
