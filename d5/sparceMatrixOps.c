/*
 * Q. Write a C program to represent a sparse matrix using a linked list (a
 *    header node holding the number of rows, columns and non-zero elements,
 *    followed by one node per non-zero element storing row, column and value)
 *    and perform the addition and the multiplication of two such matrices.
 *
 * Sample Input:
 *   2 2          (rows and cols of A)
 *   2 2          (rows and cols of B)
 *   2            (number of non-zero elements in A)
 *   0 0 1
 *   1 1 2
 *   2            (number of non-zero elements in B)
 *   0 0 3
 *   0 1 4
 *
 * Sample Output:
 *   Rows and cols of A: 2 2
 *   Rows and cols of B: 2 2
 *   Number of non-zero elements in A: 2
 *   Enter 2 entries as: row col value
 *   0 0 1
 *   1 1 2
 *   Number of non-zero elements in B: 2
 *   Enter 2 entries as: row col value
 *   0 0 3
 *   0 1 4
 *
 *   Matrix A (2 x 2):
 *       1    0
 *       0    2
 *   Matrix A as linked list: [rows=2|cols=2|nz=2] -> [0|0|1] -> [1|1|2] -> NULL
 *
 *   Matrix B (2 x 2):
 *       3    4
 *       0    0
 *   Matrix B as linked list: [rows=2|cols=2|nz=2] -> [0|0|3] -> [0|1|4] -> NULL
 *
 *   A + B (2 x 2):
 *       4    4
 *       0    2
 *   A + B as linked list: [rows=2|cols=2|nz=3] -> [0|0|4] -> [1|1|2] -> [0|1|4] -> NULL
 *
 *   A - B (2 x 2):
 *      -2   -4
 *       0    2
 *   A - B as linked list: [rows=2|cols=2|nz=3] -> [0|0|-2] -> [1|1|2] -> [0|1|-4] -> NULL
 *
 *   A * B (2 x 2):
 *       3    4
 *       0    0
 *   A * B as linked list: [rows=2|cols=2|nz=2] -> [0|0|3] -> [0|1|4] -> NULL
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int row;
    int col;
    int val;
    struct node *next;
} node;

void display(node *head, int rows, int cols, const char *name) {
    printf("\n%s (%d x %d):\n", name, rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int v = 0;
            for (node *cur = head->next; cur != NULL; cur = cur->next) {
                if (cur->row == i && cur->col == j) {
                    v = cur->val;
                    break;
                }
            }
            printf("%5d", v);
        }
        printf("\n");
    }
}

/* print the matrix the way it is really stored: header node, then one node
   per non-zero element */
void displayList(node *head, const char *name) {
    printf("%s as linked list: ", name);
    printf("[rows=%d|cols=%d|nz=%d]", head->row, head->col, head->val);
    for (node *cur = head->next; cur != NULL; cur = cur->next)
        printf(" -> [%d|%d|%d]", cur->row, cur->col, cur->val);
    printf(" -> NULL\n");
}

node *simplify(node *head) {
    for (node *i = head->next; i != NULL; i = i->next) {
        for (node *j = i; j->next != NULL; ) {
            if (j->next->row == i->row && j->next->col == i->col) {
                node *dup = j->next;
                i->val += dup->val;
                j->next = dup->next;
                free(dup);
            } else {
                j = j->next;
            }
        }
    }

    for (node *cur = head; cur->next != NULL; ) {
        if (cur->next->val == 0) {
            node *zero = cur->next;
            cur->next = zero->next;
            free(zero);
        } else {
            cur = cur->next;
        }
    }

    head->val = 0;
    for (node *cur = head->next; cur != NULL; cur = cur->next)
        head->val++;

    return head;
}

/* sign = 1 for addition, sign = -1 for subtraction */
node *add(node *a, node *b, int sign) {
    node *head = (node *)malloc(sizeof(node));
    head->row = a->row;
    head->col = a->col;
    head->val = 0;
    head->next = NULL;
    node *tail = head;

    for (int pass = 0; pass < 2; pass++) {
        for (node *cur = (pass == 0 ? a : b)->next; cur != NULL; cur = cur->next) {
            node *n = (node *)malloc(sizeof(node));
            n->row = cur->row;
            n->col = cur->col;
            n->val = (pass == 0 ? cur->val : sign * cur->val);
            n->next = NULL;
            tail->next = n;
            tail = n;
        }
    }

    return simplify(head);
}

node *multiply(node *a, node *b) {
    node *head = (node *)malloc(sizeof(node));
    head->row = a->row;
    head->col = b->col;
    head->val = 0;
    head->next = NULL;
    node *tail = head;

    for (node *pa = a->next; pa != NULL; pa = pa->next) {
        for (node *pb = b->next; pb != NULL; pb = pb->next) {
            if (pa->col != pb->row)
                continue;
            node *n = (node *)malloc(sizeof(node));
            n->row = pa->row;
            n->col = pb->col;
            n->val = pa->val * pb->val;
            n->next = NULL;
            tail->next = n;
            tail = n;
        }
    }

    return simplify(head);
}

/* init: build one matrix list -- header node holding rows, cols and the
   number of non-zero elements, then one node per non-zero element */
node *init(int rows, int cols, const char *name) {
    int nz;

    printf("Number of non-zero elements in %s: ", name);
    scanf("%d", &nz);

    node *head = (node *)malloc(sizeof(node));
    head->row = rows;
    head->col = cols;
    head->val = nz;
    head->next = NULL;
    node *tail = head;

    printf("Enter %d entries as: row col value\n", nz);
    for (int i = 0; i < nz; i++) {
        node *n = (node *)malloc(sizeof(node));
        scanf("%d %d %d", &n->row, &n->col, &n->val);
        n->next = NULL;
        tail->next = n;
        tail = n;
    }

    return head;
}

int main() {
    int r1, c1, r2, c2;

    printf("Rows and cols of A: ");
    scanf("%d %d", &r1, &c1);
    printf("Rows and cols of B: ");
    scanf("%d %d", &r2, &c2);

    node *a = init(r1, c1, "A");
    node *b = init(r2, c2, "B");

    display(a, r1, c1, "Matrix A");
    displayList(a, "Matrix A");
    display(b, r2, c2, "Matrix B");
    displayList(b, "Matrix B");

    if (r1 == r2 && c1 == c2) {
        node *sum = add(a, b, 1);
        display(sum, r1, c1, "A + B");
        displayList(sum, "A + B");

        node *diff = add(a, b, -1);
        display(diff, r1, c1, "A - B");
        displayList(diff, "A - B");
    }

    if (c1 == r2) {
        node *prod = multiply(a, b);
        display(prod, r1, c2, "A * B");
        displayList(prod, "A * B");
    }

    return 0;
}
