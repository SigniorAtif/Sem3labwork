/*
 * Q. Write a C program to represent a polynomial using a linked list (one
 *    node per term storing the coefficient and the power) and perform the
 *    addition, the subtraction and the multiplication of two polynomials.
 *
 * Sample Input:
 *   (no input is read; the two polynomials are hard-coded in main --
 *    A = 5x^2 + 4x^1 + 2x^0 and B = 3x^2 + 1x^0)
 *
 * Sample Output:
 *   A     = 5x^2 + 4x^1 + 2x^0
 *   B     = 3x^2 + 1x^0
 *   A + B = 8x^2 + 4x^1 + 3x^0
 *   A - B = 2x^2 + 4x^1 + 1x^0
 *   A * B = 15x^4 + 11x^2 + 12x^3 + 4x^1 + 2x^0
 *
 * (the product terms are not sorted by power -- multiply() appends each
 *  partial product and simplify() only merges the like terms in place.)
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int coeff;
    int pow;
    struct node *next;
} node;

/* add one term at the end of the list */
node *append(node *head, int coeff, int pow)
{
    node *ptr, *cur;

    ptr = (node *)malloc(sizeof(node));
    ptr->coeff = coeff;
    ptr->pow = pow;
    ptr->next = NULL;

    if (head == NULL)
        return ptr;

    cur = head;
    while (cur->next != NULL)
        cur = cur->next;
    cur->next = ptr;
    return head;
}

/* init: build a list from n terms */
node *init(int coeff[], int pow[], int n)
{
    node *head = NULL;
    int i;

    for (i = 0; i < n; i++)
        head = append(head, coeff[i], pow[i]);
    return head;
}

/* simplify: two loops, find duplicate powers, add them and remove the copy */
node *simplify(node *head)
{
    node *outer, *inner, *prev, *dead;

    outer = head;
    while (outer != NULL) {
        prev = outer;
        inner = outer->next;
        while (inner != NULL) {
            if (inner->pow == outer->pow) {
                outer->coeff = outer->coeff + inner->coeff;
                prev->next = inner->next;
                dead = inner;
                inner = inner->next;
                free(dead);
            } else {
                prev = inner;
                inner = inner->next;
            }
        }
        outer = outer->next;
    }
    return head;
}

/* add: put both lists into one list, then simplify.
   sign = 1 for addition, sign = -1 for subtraction */
node *add(node *a, node *b, int sign)
{
    node *res = NULL;
    node *cur;

    cur = a;
    while (cur != NULL) {
        res = append(res, cur->coeff, cur->pow);
        cur = cur->next;
    }
    cur = b;
    while (cur != NULL) {
        res = append(res, sign * cur->coeff, cur->pow);
        cur = cur->next;
    }
    return simplify(res);
}

/* multiply: every term of a with every term of b, then simplify */
node *multiply(node *a, node *b)
{
    node *res = NULL;
    node *i, *j;

    i = a;
    while (i != NULL) {
        j = b;
        while (j != NULL) {
            res = append(res, i->coeff * j->coeff, i->pow + j->pow);
            j = j->next;
        }
        i = i->next;
    }
    return simplify(res);
}

void print(node *head)
{
    node *cur;
    int c;

    if (head == NULL) {
        printf("0\n");
        return;
    }
    cur = head;
    while (cur != NULL) {
        c = cur->coeff;
        if (cur == head) {
            if (c < 0) {
                printf("-");
                c = -c;
            }
        } else {
            if (c < 0) {
                printf(" - ");
                c = -c;
            } else {
                printf(" + ");
            }
        }
        printf("%dx^%d", c, cur->pow);
        cur = cur->next;
    }
    printf("\n");
}

int main()
{
    int c1[] = {5, 4, 2};
    int p1[] = {2, 1, 0};
    int c2[] = {3, 1};
    int p2[] = {2, 0};

    node *a, *b;

    a = init(c1, p1, 3);
    b = init(c2, p2, 2);

    printf("A     = ");
    print(a);
    printf("B     = ");
    print(b);
    printf("A + B = ");
    print(add(a, b, 1));
    printf("A - B = ");
    print(add(a, b, -1));
    printf("A * B = ");
    print(multiply(a, b));

    return 0;
}
