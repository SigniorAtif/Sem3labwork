/*
 * Q11. Implement the queue as a collection of multiple arrays. Once the first
 *      array gets over, the number is entered into the second array and so on.
 *      If the front element gets deleted then every element present in all
 *      these three arrays moves one step forward; the first element of the
 *      second array moves to the last element of the first array and so on.
 *
 *      Counter  Front
 *               [ ][ ][ ][ ][ ] --+
 *               [ ][ ][ ][ ][ ] <-+--+
 *               [ ][ ][ ][ ][ ] <----+
 *                           Rear
 *
 * Sample Input:
 *   12
 *   1 2 3 4 5 6 7 8 9 10 11 12
 *   2
 *
 * Sample Output:
 *   Enter the number of values to insert: 12
 *   Enter 12 values: 1 2 3 4 5 6 7 8 9 10 11 12
 *   counter = 12
 *   array 1  :   1   2   3   4   5
 *   array 2  :   6   7   8   9  10
 *   array 3  :  11  12   -   -   -
 *   Enter the number of deletions: 2
 *   deleted 1
 *   deleted 2
 *   counter = 10
 *   array 1  :   3   4   5   6   7
 *   array 2  :   8   9  10  11  12
 *   array 3  :   -   -   -   -   -
 */

#include <stdio.h>

#define ROWS 3
#define COLS 5

/* three chained arrays; counter is the number of elements and also the
 * next free slot, so the front is always arr[0][0] and the rear is
 * slot counter-1 */
int arr[ROWS][COLS];
int counter = 0;

int enqueue(int val) {
  if (counter == ROWS * COLS)
    return 0;
  arr[counter / COLS][counter % COLS] = val;
  counter++;
  return 1;
}

/* removes arr[0][0] and moves every element one step forward; the first
 * element of each array moves to the last slot of the previous one */
int dequeue(int *val) {
  if (counter == 0)
    return 0;
  *val = arr[0][0];
  for (int i = 1; i < counter; i++)
    arr[(i - 1) / COLS][(i - 1) % COLS] = arr[i / COLS][i % COLS];
  counter--;
  return 1;
}

void display(void) {
  printf("counter = %d\n", counter);
  for (int r = 0; r < ROWS; r++) {
    printf("array %d  :", r + 1);
    for (int c = 0; c < COLS; c++) {
      int idx = r * COLS + c;
      if (idx < counter)
        printf(" %3d", arr[r][c]);
      else
        printf("   -");
    }
    printf("\n");
  }
}

int main(void) {
  int n, val;

  printf("Enter the number of values to insert: ");
  if (scanf("%d", &n) != 1)
    return 1;
  printf("Enter %d values: ", n);
  for (int i = 0; i < n; i++) {
    if (scanf("%d", &val) != 1)
      return 1;
    if (!enqueue(val))
      printf("queue full, %d not inserted\n", val);
  }
  display();

  printf("Enter the number of deletions: ");
  if (scanf("%d", &n) != 1)
    return 1;
  for (int i = 0; i < n; i++) {
    if (!dequeue(&val)) {
      printf("queue empty\n");
      break;
    }
    printf("deleted %d\n", val);
  }
  display();
  return 0;
}
