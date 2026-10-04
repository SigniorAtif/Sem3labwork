/*
 * Q1. Write a program to check whether a string is bracket ( [], {} and () )
 *     balanced or not using stack. For example "((())())()" is balanced,
 *     ")()(" is not and "())" is not.
 *
 * Sample Input:
 *   ((())())()
 *
 * Sample Output:
 *   Enter the string: ((())())()
 *   ((())())() is balanced
 *
 * Sample Input:
 *   {[(])}
 *
 * Sample Output:
 *   Enter the string: {[(])}
 *   {[(])} is not balanced
 */

#include <stdio.h>
#include <string.h>

#define MAX 256

typedef struct stack {
  char data[MAX];
  int top;
} stack;

void init(stack *s) { s->top = -1; }
int is_empty(stack *s) { return s->top == -1; }
void push(stack *s, char c) { s->data[++s->top] = c; }
char pop(stack *s) { return s->data[s->top--]; }

int matches(char open, char close) {
  return (open == '(' && close == ')') || (open == '[' && close == ']') ||
         (open == '{' && close == '}');
}

int is_balanced(const char *str) {
  stack s;
  init(&s);
  for (int i = 0; str[i]; i++) {
    char c = str[i];
    if (c == '(' || c == '[' || c == '{')
      push(&s, c);
    else if (c == ')' || c == ']' || c == '}') {
      if (is_empty(&s) || !matches(pop(&s), c))
        return 0;
    }
  }
  return is_empty(&s);
}

int main(void) {
  char str[MAX];
  printf("Enter the string: ");
  if (scanf("%255s", str) != 1)
    return 1;
  printf("%s is %s\n", str, is_balanced(str) ? "balanced" : "not balanced");
  return 0;
}
