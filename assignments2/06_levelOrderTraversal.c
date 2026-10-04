/*
 * Q6. Implement the level order traversal of a binary tree.
 *     The tree is read in level order with -1 for a missing child.
 *
 *           1
 *         /   \
 *        2     3
 *       / \   / \
 *      4   5 6   7
 *         /
 *        8
 *
 * Sample Input:
 *   1 2 3 4 5 6 7 -1 -1 8 -1 -1 -1 -1 -1 -1 -1
 *
 * Sample Output:
 *   Enter the tree in level order (-1 for null): 1 2 3 4 5 6 7 -1 -1 8 -1 -1 -1 -1 -1 -1 -1
 *   level 0  : 1
 *   level 1  : 2 3
 *   level 2  : 4 5 6 7
 *   level 3  : 8
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

/* prints every level on its own line using a queue */
void level_order(node *root) {
  node *q[MAXQ];
  int f = 0, r = 0, level = 0;
  if (root)
    q[r++] = root;
  while (f < r) {
    int width = r - f; /* nodes on the current level */
    printf("level %d  :", level++);
    while (width--) {
      node *cur = q[f++];
      printf(" %d", cur->data);
      if (cur->left)
        q[r++] = cur->left;
      if (cur->right)
        q[r++] = cur->right;
    }
    printf("\n");
  }
}

int main(void) {
  node *root = build_tree();
  if (!root) {
    printf("tree is empty\n");
    return 0;
  }
  level_order(root);
  free_tree(root);
  return 0;
}
