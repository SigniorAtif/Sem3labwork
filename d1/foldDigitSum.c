/*take a long number as input where we fold that number and then add it
example -> 1964728
  1
 96
472
  8
sum -> 577

Sample Input:
  1964728
Sample Output:
  Enter number: 1964728
  sum -> 577 */

#include <stdio.h>

/* 10^p */
long p10(int p) {
    long r = 1;
    while (p-- > 0)
        r *= 10;
    return r;
}

int main(void) {
    long n;
    printf("Enter number: ");
    if (scanf("%ld", &n) != 1)
        return 1;

    /* count digits */
    int len = 0;
    for (long t = n; t > 0; t /= 10)
        len++;
    if (len == 0)
        len = 1;                /* n == 0 */

    long sum = 0;
    int remaining = len;
    int chunk = 1;

    while (remaining > 0) {
        int take = chunk < remaining ? chunk : remaining;
        remaining -= take;
        /* the `take` digits sitting above position `remaining` */
        sum += (n / p10(remaining)) % p10(take);
        chunk++;
    }

    printf("sum -> %ld\n", sum);
    return 0;
}
