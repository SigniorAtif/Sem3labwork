/*take a number as input and then display the numbers from left to right in single lines without using a array or reversing the digit

example input -> 1234
output ->
1
2
3
4
*/

#include <stdio.h>

int main(void)
{
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);

    int divisor = 1;
    while (n / divisor >= 10)
        divisor *= 10;

    while (divisor > 0)
    {
        printf("%d\n", n / divisor);
        n %= divisor;
        divisor /= 10;
    }

    return 0;
}
