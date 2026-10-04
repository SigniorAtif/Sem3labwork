/*
 * Q2. Write a function to convert an Infix expression to a Postfix expression.
 *     Operands are single letters/digits, operators + - * / % ^ and ( ).
 *     ^ is right associative, the rest are left associative.
 *
 * Sample Input:
 *   a+b*(c^d-e)^(f+g*h)-i
 *
 * Sample Output:
 *   Enter the infix expression: a+b*(c^d-e)^(f+g*h)-i
 *   postfix  : abcd^e-fgh*+^*+i-
 */

#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define MAX 256

int prec(char op) {
  switch (op) {
  case '^': return 3;
  case '*': case '/': case '%': return 2;
  case '+': case '-': return 1;
  }
  return 0;
}

/* converts infix to postfix, returns 0 on mismatched parentheses */
int infix_to_postfix(const char *infix, char *postfix) {
  char st[MAX];
  int top = -1, k = 0;

  for (int i = 0; infix[i]; i++) {
    char c = infix[i];
    if (isspace((unsigned char)c))
      continue;
    if (isalnum((unsigned char)c))
      postfix[k++] = c;
    else if (c == '(')
      st[++top] = c;
    else if (c == ')') {
      while (top >= 0 && st[top] != '(')
        postfix[k++] = st[top--];
      if (top < 0)
        return 0;
      top--; /* drop '(' */
    } else {
      /* '^' is right associative, the rest are left associative */
      while (top >= 0 && st[top] != '(' &&
             (prec(st[top]) > prec(c) || (prec(st[top]) == prec(c) && c != '^')))
        postfix[k++] = st[top--];
      st[++top] = c;
    }
  }
  while (top >= 0) {
    if (st[top] == '(')
      return 0;
    postfix[k++] = st[top--];
  }
  postfix[k] = '\0';
  return 1;
}

int main(void) {
  char infix[MAX], postfix[MAX];
  printf("Enter the infix expression: ");
  if (!fgets(infix, MAX, stdin))
    return 1;
  infix[strcspn(infix, "\n")] = '\0';
  if (!infix_to_postfix(infix, postfix)) {
    printf("invalid expression (mismatched parentheses)\n");
    return 1;
  }
  printf("postfix  : %s\n", postfix);
  return 0;
}
