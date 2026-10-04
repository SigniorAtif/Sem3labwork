/*
 * Q9. Implement non-recursive delete method of a binary search tree.
 *     Covers all three cases: leaf, one child, two children (replaced by the
 *     inorder successor), including deleting the root.
 *
 * Sample Input:
 *   9
 *   50 30 70 20 40 60 80 65 35
 *   4
 *   20
 *   30
 *   50
 *   99
 *
 * Sample Output:
 *   Enter the number of values: 9
 *   Enter 9 values: 50 30 70 20 40 60 80 65 35
 *   inorder  : 20 30 35 40 50 60 65 70 80
 *   Enter the number of deletions: 4
 *   Enter the value to delete: 20
 *   inorder  : 30 35 40 50 60 65 70 80
 *   Enter the value to delete: 30
 *   inorder  : 35 40 50 60 65 70 80
 *   Enter the value to delete: 50
 *   inorder  : 35 40 60 65 70 80
 *   Enter the value to delete: 99
 *   99 not found
 *   inorder  : 35 40 60 65 70 80
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  int data;
  struct node *left, *right;
} node;

node *insert(node *root, int val) {
  node *n = malloc(sizeof *n);
  n->data = val;
  n->left = n->right = NULL;
  if (!root)
    return n;

  node *cur = root, *parent = NULL;
  while (cur) {
    parent = cur;
    if (val == cur->data) { /* no duplicates */
      free(n);
      return root;
    }
    cur = val < cur->data ? cur->left : cur->right;
  }
  if (val < parent->data)
    parent->left = n;
  else
    parent->right = n;
  return root;
}

/* non-recursive delete, returns the (possibly new) root */
node *delete_node(node *root, int key, int *found) {
  node *cur = root, *parent = NULL;
  *found = 0;

  while (cur && cur->data != key) {
    parent = cur;
    cur = key < cur->data ? cur->left : cur->right;
  }
  if (!cur)
    return root;
  *found = 1;

  /* two children: copy the inorder successor in, then delete the successor */
  if (cur->left && cur->right) {
    node *sp = cur, *s = cur->right;
    while (s->left) {
      sp = s;
      s = s->left;
    }
    cur->data = s->data;
    parent = sp;
    cur = s;
  }

  /* now cur has at most one child */
  node *child = cur->left ? cur->left : cur->right;
  if (!parent)
    root = child;
  else if (parent->left == cur)
    parent->left = child;
  else
    parent->right = child;
  free(cur);
  return root;
}

void inorder(node *root) {
  if (!root)
    return;
  inorder(root->left);
  printf(" %d", root->data);
  inorder(root->right);
}

void free_tree(node *root) {
  if (!root)
    return;
  free_tree(root->left);
  free_tree(root->right);
  free(root);
}

int main(void) {
  node *root = NULL;
  int n, val, found;

  printf("Enter the number of values: ");
  if (scanf("%d", &n) != 1)
    return 1;
  printf("Enter %d values: ", n);
  for (int i = 0; i < n; i++) {
    if (scanf("%d", &val) != 1)
      return 1;
    root = insert(root, val);
  }
  printf("inorder  :");
  inorder(root);
  printf("\n");

  printf("Enter the number of deletions: ");
  if (scanf("%d", &n) != 1)
    return 1;
  for (int i = 0; i < n; i++) {
    printf("Enter the value to delete: ");
    if (scanf("%d", &val) != 1)
      return 1;
    root = delete_node(root, val, &found);
    if (!found)
      printf("%d not found\n", val);
    printf("inorder  :");
    inorder(root);
    printf("\n");
  }
  free_tree(root);
  return 0;
}
