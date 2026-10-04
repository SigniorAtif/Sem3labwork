/*
 * Q7. Interchange left node to right and right node to left in a binary tree.
 *
 *           1                 1
 *         /   \             /   \
 *        2     3    ->     3     2
 *       / \     \         /     / \
 *      4   5     6       6     5   4
 *
 * Sample Input:
 *   1 2 3 4 5 -1 6 -1 -1 -1 -1 -1 -1
 *
 * Sample Output:
 *   Enter the tree in level order (-1 for null): 1 2 3 4 5 -1 6 -1 -1 -1 -1 -1 -1
 *   before   : level order 1 2 3 4 5 6
 *              inorder     4 2 5 1 3 6
 *   after    : level order 1 3 2 6 5 4
 *              inorder     6 3 1 5 2 4
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

void level_order(node *root) {
  node *q[MAXQ];
  int f = 0, r = 0;
  if (root)
    q[r++] = root;
  while (f < r) {
    node *cur = q[f++];
    printf(" %d", cur->data);
    if (cur->left)
      q[r++] = cur->left;
    if (cur->right)
      q[r++] = cur->right;
  }
  printf("\n");
}

void inorder(node *root) {
  if (!root)
    return;
  inorder(root->left);
  printf(" %d", root->data);
  inorder(root->right);
}

/* swaps left and right children of every node */
void mirror(node *root) {
  if (!root)
    return;
  node *t = root->left;
  root->left = root->right;
  root->right = t;
  mirror(root->left);
  mirror(root->right);
}

int main(void) {
  node *root = build_tree();
  printf("before   : level order");
  level_order(root);
  printf("           inorder    ");
  inorder(root);
  printf("\n");

  mirror(root);

  printf("after    : level order");
  level_order(root);
  printf("           inorder    ");
  inorder(root);
  printf("\n");
  free_tree(root);
  return 0;
}
