/*
 * Binary search tree: insertion and deletion.
 *   Delete covers all three cases: leaf, one child, two children (replaced by
 *   the inorder successor), including deleting the root.
 *
 * Sample Input:
 *   1 50  1 30  1 70  1 20  1 40  1 60  1 80
 *   2 20  2 30  2 50  2 99  3 60  3 50  4
 *
 * Sample Output (prompts trimmed):
 *   inorder  : 20 30 40 50 60 70 80      (after the inserts)
 *   inorder  : 30 40 50 60 70 80         (delete 20, leaf)
 *   inorder  : 40 50 60 70 80            (delete 30, one child)
 *   inorder  : 40 60 70 80               (delete 50, two children / root)
 *   99 not found
 *   60 found
 *   50 not found
 */

#include <stdio.h>
#include <stdlib.h>

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

node *insert(node *root, int val) {
  if (!root)
    return new_node(val);
  if (val < root->data)
    root->left = insert(root->left, val);
  else if (val > root->data)
    root->right = insert(root->right, val);
  /* duplicates ignored */
  return root;
}

/* iterative search, returns the node or NULL */
node *search(node *root, int key) {
  while (root && root->data != key)
    root = key < root->data ? root->left : root->right;
  return root;
}

node *min_node(node *root) {
  while (root->left)
    root = root->left;
  return root;
}

/* returns the (possibly new) root of this subtree */
node *delete_node(node *root, int key, int *found) {
  if (!root)
    return NULL;

  if (key < root->data) {
    root->left = delete_node(root->left, key, found);
  } else if (key > root->data) {
    root->right = delete_node(root->right, key, found);
  } else {
    *found = 1;
    /* zero or one child: splice it out */
    if (!root->left || !root->right) {
      node *child = root->left ? root->left : root->right;
      free(root);
      return child;
    }
    /* two children: copy the inorder successor in, then delete it */
    node *s = min_node(root->right);
    root->data = s->data;
    root->right = delete_node(root->right, s->data, found);
  }
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
  int choice, val, found;

  for (;;) {
    printf("\n1. Insert  2. Delete  3. Search  4. Exit\nEnter choice: ");
    if (scanf("%d", &choice) != 1 || choice == 4)
      break;

    switch (choice) {
    case 1:
      printf("Enter the value to insert: ");
      if (scanf("%d", &val) != 1)
        goto out;
      root = insert(root, val);
      break;
    case 2:
      printf("Enter the value to delete: ");
      if (scanf("%d", &val) != 1)
        goto out;
      found = 0;
      root = delete_node(root, val, &found);
      if (!found)
        printf("%d not found\n", val);
      break;
    case 3:
      printf("Enter the value to search: ");
      if (scanf("%d", &val) != 1)
        goto out;
      if (search(root, val))
        printf("%d found\n", val);
      else
        printf("%d not found\n", val);
      continue;
    default:
      printf("Invalid choice\n");
      continue;
    }
    printf("inorder  :");
    inorder(root);
    printf("\n");
  }
out:
  free_tree(root);
  return 0;
}
