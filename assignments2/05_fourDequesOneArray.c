/*
 * Q5. Let a single array be divided into four equal parts. Implement a double
 *     ended circular queue in each sub part of this array.
 *
 * Sample Input:
 *   1 1 10    (choice, deque, value)
 *   2 1 20
 *   1 2 5
 *   2 4 9
 *   3 1       (choice, deque)
 *   4 3
 *   5
 *   0
 *
 * Sample Output:
 *   array of 20 split into 4 deques of 5
 *   1-insert front 2-insert rear 3-delete front 4-delete rear 5-display all 0-exit
 *   Enter choice: 1
 *   Enter deque number (1-4): 1
 *   Enter value: 10
 *   deque 1  : 10
 *   Enter choice: 2
 *   Enter deque number (1-4): 1
 *   Enter value: 20
 *   deque 1  : 10 20
 *   Enter choice: 1
 *   Enter deque number (1-4): 2
 *   Enter value: 5
 *   deque 2  : 5
 *   Enter choice: 2
 *   Enter deque number (1-4): 4
 *   Enter value: 9
 *   deque 4  : 9
 *   Enter choice: 3
 *   Enter deque number (1-4): 1
 *   deleted 10
 *   deque 1  : 20
 *   Enter choice: 4
 *   Enter deque number (1-4): 3
 *   deque 3 is empty
 *   deque 3  :
 *   Enter choice: 5
 *   deque 1  : 20
 *   deque 2  : 5
 *   deque 3  :
 *   deque 4  : 9
 *   Enter choice: 0
 */

#include <stdio.h>

#define PARTS 4
#define PART_SIZE 5
#define SIZE (PARTS * PART_SIZE)

/* one shared array, deque k lives in arr[k*PART_SIZE .. (k+1)*PART_SIZE-1];
 * front/rear are offsets inside that slice */
int arr[SIZE];
int front[PARTS], rear[PARTS], count[PARTS];

int base(int k) { return k * PART_SIZE; }

void init(void) {
  for (int k = 0; k < PARTS; k++) {
    front[k] = 0;
    rear[k] = PART_SIZE - 1;
    count[k] = 0;
  }
}

int insert_front(int k, int val) {
  if (count[k] == PART_SIZE)
    return 0;
  front[k] = (front[k] - 1 + PART_SIZE) % PART_SIZE;
  arr[base(k) + front[k]] = val;
  count[k]++;
  return 1;
}

int insert_rear(int k, int val) {
  if (count[k] == PART_SIZE)
    return 0;
  rear[k] = (rear[k] + 1) % PART_SIZE;
  arr[base(k) + rear[k]] = val;
  count[k]++;
  return 1;
}

int delete_front(int k, int *val) {
  if (count[k] == 0)
    return 0;
  *val = arr[base(k) + front[k]];
  front[k] = (front[k] + 1) % PART_SIZE;
  count[k]--;
  return 1;
}

int delete_rear(int k, int *val) {
  if (count[k] == 0)
    return 0;
  *val = arr[base(k) + rear[k]];
  rear[k] = (rear[k] - 1 + PART_SIZE) % PART_SIZE;
  count[k]--;
  return 1;
}

void display(int k) {
  printf("deque %d  :", k + 1);
  for (int i = 0; i < count[k]; i++)
    printf(" %d", arr[base(k) + (front[k] + i) % PART_SIZE]);
  printf("\n");
}

int main(void) {
  int ch, k, val;
  init();
  printf("array of %d split into %d deques of %d\n", SIZE, PARTS, PART_SIZE);
  printf("1-insert front 2-insert rear 3-delete front 4-delete rear "
         "5-display all 0-exit\n");

  while (1) {
    printf("Enter choice: ");
    if (scanf("%d", &ch) != 1 || ch == 0)
      break;
    if (ch == 5) {
      for (k = 0; k < PARTS; k++)
        display(k);
      continue;
    }
    if (ch < 1 || ch > 4) {
      printf("invalid choice\n");
      continue;
    }
    printf("Enter deque number (1-%d): ", PARTS);
    if (scanf("%d", &k) != 1)
      break;
    if (k < 1 || k > PARTS) {
      printf("invalid deque\n");
      continue;
    }
    k--;
    if (ch == 1 || ch == 2) {
      printf("Enter value: ");
      if (scanf("%d", &val) != 1)
        break;
      if (!(ch == 1 ? insert_front(k, val) : insert_rear(k, val)))
        printf("deque %d is full\n", k + 1);
    } else {
      if (ch == 3 ? delete_front(k, &val) : delete_rear(k, &val))
        printf("deleted %d\n", val);
      else
        printf("deque %d is empty\n", k + 1);
    }
    display(k);
  }
  return 0;
}
