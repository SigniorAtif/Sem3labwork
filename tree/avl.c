/*
 * AVL tree: insertion and deletion with rebalancing (LL, RR, LR, RL).
 *   After every operation the tree is printed in preorder with the balance
 *   factor of each node, so the rotations can be checked by hand.
 *
 * Sample Input:
 *   1 10  1 20  1 30  1 40  1 50  1 25
 *   2 40  2 30  2 99  3 25  3 30  4
 *
 * Sample Output (prompts trimmed, last line of each step):
 *   preorder : 30(0) 20(0) 10(0) 25(0) 40(-1) 50(0)    (after the inserts)
 *   preorder : 30(1) 20(0) 10(0) 25(0) 50(0)           (delete 40)
 *   preorder : 20(-1) 10(0) 50(1) 25(0)                (delete 30, root; LL)
 *   99 not found
 *   25 found
 *   30 not found
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  int data, height;
  struct node *left, *right;
} node;

int height(node *n) { return n ? n->height : 0; }

int max(int a, int b) { return a > b ? a : b; }

void update(node *n) { n->height = 1 + max(height(n->left), height(n->right)); }

int balance(node *n) { return n ? height(n->left) - height(n->right) : 0; }

node *new_node(int val) {
  node *n = malloc(sizeof *n);
  n->data = val;
  n->height = 1;
  n->left = n->right = NULL;
  return n;
}

/*
 *      y            x
 *     / \          / \
 *    x   C  -->   A   y
 *   / \              / \
 *  A   B            B   C
 */
node *rotate_right(node *y) {
  node *x = y->left;
  y->left = x->right;
  x->right = y;
  update(y);
  update(x);
  return x;
}

node *rotate_left(node *x) {
  node *y = x->right;
  x->right = y->left;
  y->left = x;
  update(x);
  update(y);
  return y;
}

/* fix the height of n and rotate if it is out of balance */
node *rebalance(node *n) {
  update(n);
  int bf = balance(n);

  if (bf > 1) {
    if (balance(n->left) < 0) /* LR */
      n->left = rotate_left(n->left);
    return rotate_right(n); /* LL */
  }
  if (bf < -1) {
    if (balance(n->right) > 0) /* RL */
      n->right = rotate_right(n->right);
    return rotate_left(n); /* RR */
  }
  return n;
}

node *insert(node *root, int val) {
  if (!root)
    return new_node(val);
  if (val < root->data)
    root->left = insert(root->left, val);
  else if (val > root->data)
    root->right = insert(root->right, val);
  else
    return root; /* duplicates ignored */
  return rebalance(root);
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

node *delete_node(node *root, int key, int *found) {
  if (!root)
    return NULL;

  if (key < root->data) {
    root->left = delete_node(root->left, key, found);
  } else if (key > root->data) {
    root->right = delete_node(root->right, key, found);
  } else {
    *found = 1;
    if (!root->left || !root->right) {
      node *child = root->left ? root->left : root->right;
      free(root);
      return child; /* child subtree is already balanced */
    }
    node *s = min_node(root->right);
    root->data = s->data;
    root->right = delete_node(root->right, s->data, found);
  }
  return rebalance(root);
}

void preorder(node *root) {
  if (!root)
    return;
  printf(" %d(%d)", root->data, balance(root));
  preorder(root->left);
  preorder(root->right);
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
    printf("\npreorder :");
    preorder(root);
    printf("\n");
  }
out:
  free_tree(root);
  return 0;
}
