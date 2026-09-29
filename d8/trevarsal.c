#include<stdio.h>
#include<stdlib.h>

#define MAX 100

typedef struct node {
  int data;
  struct node *left, *right;
} node;

typedef struct stack{
  node *data[MAX];
  int top;
}stack;

void init(stack *s) { s->top = -1; }

int isEmpty(stack *s) { return s->top == -1; }

void push(stack *s, node *n) {
  if (s->top == MAX - 1) {
    printf("stack overflow\n");
    exit(1);
  }
  s->data[++s->top] = n;
}

node *pop(stack *s) { return s->data[s->top--]; }

node *newNode(int data) {
  node *n = malloc(sizeof(node));
  n->data = data;
  n->left = n->right = NULL;
  return n;
}

void preorder(node *root) {
  stack s;
  init(&s);

  if (root != NULL)
    push(&s, root);
  while (!isEmpty(&s)) {
    node *cur = pop(&s);
    printf("%d ", cur->data);
    if (cur->right != NULL)
      push(&s, cur->right);
    if (cur->left != NULL)
      push(&s, cur->left);
  }
  printf("\n");
}

void inorder(node *root) {
  stack s;
  init(&s);
  node *cur = root;

  while (cur != NULL || !isEmpty(&s)) {
    while (cur != NULL) {
      push(&s, cur);
      cur = cur->left;
    }
    cur = pop(&s);
    printf("%d ", cur->data);
    cur = cur->right;
  }
  printf("\n");
}

void postorder(node *root) {
  stack s1, s2;
  init(&s1);
  init(&s2);

  if (root != NULL)
    push(&s1, root);
  while (!isEmpty(&s1)) {
    node *cur = pop(&s1);
    push(&s2, cur);
    if (cur->left != NULL)
      push(&s1, cur->left);
    if (cur->right != NULL)
      push(&s1, cur->right);
  }
  while (!isEmpty(&s2))
    printf("%d ", pop(&s2)->data);
  printf("\n");
}

int main(){
  node *root = newNode(8);
  root->left = newNode(3);
  root->right = newNode(10);
  root->left->left = newNode(1);
  root->left->right = newNode(6);
  root->left->right->left = newNode(4);
  root->left->right->right = newNode(7);
  root->right->right = newNode(14);
  root->right->right->left = newNode(13);

  printf("preorder  : ");
  preorder(root);
  printf("inorder   : ");
  inorder(root);
  printf("postorder : ");
  postorder(root);

  return 0;
}
