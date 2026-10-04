/*
 * Q8. Write a program to identify whether a binary tree is a fully complete
 *     binary tree or not.
 *     complete : all levels full except maybe the last, filled from the left
 *     full     : every node has 0 or 2 children
 *     "fully complete" is reported when both hold.
 *
 * Sample Input:
 *   1 2 3 4 5 6 7 -1 -1 -1 -1 -1 -1 -1 -1
 *
 * Sample Output:
 *   Enter the tree in level order (-1 for null): 1 2 3 4 5 6 7 -1 -1 -1 -1 -1 -1 -1 -1
 *   complete binary tree : yes
 *   full binary tree     : yes
 *   fully complete       : yes
 *
 * Sample Input:
 *   1 2 3 -1 4 -1 -1 -1 -1
 *
 * Sample Output:
 *   Enter the tree in level order (-1 for null): 1 2 3 -1 4 -1 -1 -1 -1
 *   complete binary tree : no
 *   full binary tree     : no
 *   fully complete       : no
 */

#include <stdio.h>
#include <stdlib.h>

#define MAXQ 100

typedef struct node {
  int data;
  struct node *left, *right;
} node;

node *new_node(int val) {
  node *n = malloc(sizeof *n);
  n->data = val;
  n->left = n->right = NULL;
  return n;
}

/* builds a tree from level order input, -1 marks a missing child */
node *build_tree(void) {
  node *q[MAXQ];
  int f = 0, r = 0, val;

  printf("Enter the tree in level order (-1 for null): ");
  if (scanf("%d", &val) != 1 || val == -1)
    return NULL;
  node *root = new_node(val);
  q[r++] = root;
  while (f < r) {
    node *cur = q[f++];
    if (scanf("%d", &val) != 1)
      break;
    if (val != -1 && r < MAXQ)
      q[r++] = cur->left = new_node(val);
    if (scanf("%d", &val) != 1)
      break;
    if (val != -1 && r < MAXQ)
      q[r++] = cur->right = new_node(val);
  }
  return root;
}

void free_tree(node *root) {
  if (!root)
    return;
  free_tree(root->left);
  free_tree(root->right);
  free(root);
}

/* complete: every level full except possibly the last, which is filled
 * from the left. In a level order walk, once a missing child is seen no
 * later node may have a child. */
int is_complete(node *root) {
  node *q[MAXQ];
  int f = 0, r = 0, gap = 0;
  if (!root)
    return 1;
  q[r++] = root;
  while (f < r) {
    node *cur = q[f++];
    node *kids[2] = {cur->left, cur->right};
    for (int i = 0; i < 2; i++) {
      if (kids[i]) {
        if (gap)
          return 0;
        q[r++] = kids[i];
      } else
        gap = 1;
    }
  }
  return 1;
}

/* full: every node has 0 or 2 children */
int is_full(node *root) {
  if (!root)
    return 1;
  if (!root->left != !root->right)
    return 0;
  return is_full(root->left) && is_full(root->right);
}

int main(void) {
  node *root = build_tree();
  int c = is_complete(root), f = is_full(root);
  printf("complete binary tree : %s\n", c ? "yes" : "no");
  printf("full binary tree     : %s\n", f ? "yes" : "no");
  printf("fully complete       : %s\n", c && f ? "yes" : "no");
  free_tree(root);
  return 0;
}
