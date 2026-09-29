/* write a program to take a odd digit number as input and extract the middle
digit from it and print it in word format 1 -> "one" using switch case and
while loop

Sample Input:
  12345
Sample Output:
  Enter an odd digit number: 12345
  three

(an even digit count prints "not a odd unmber" and stops) */
#include<stdio.h>
int main() {
    int num, middle_digit, temp, count = 0;
    printf("Enter an odd digit number: ");
    scanf("%d", &num);

    temp = num;
    while(temp != 0) {
        temp /= 10;
        count++;
    }
    if( count % 2 != 1){
        printf("not a odd unmber");
        return 0;
    }
    temp = num;
    for(int i = 0; i < count / 2; i++) {
        temp /= 10;
    }
    middle_digit = temp % 10;

    switch(middle_digit) {
        case 0:
            printf("zero\n");
            break;
        case 1:
            printf("one\n");
            break;
        case 2:
            printf("two\n");
            break;
        case 3:
            printf("three\n");
            break;
        case 4:
            printf("four\n");
            break;
        case 5:
            printf("five\n");
            break;
        case 6:
            printf("six\n");
            break;
        case 7:
            printf("seven\n");
            break;
        case 8:
            printf("eight\n");
            break;
        case 9:
            printf("nine\n");
            break;
        default:
            printf("Invalid input");
    }

    return 0;
}
