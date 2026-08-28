/*
 * Q. Write a C program to create a structure "student" (name, roll number and
 *    marks of 3 subjects) and use an array of such structures to store the
 *    details of n students entered by the user. Print every student's
 *    information along with the total and the average marks.
 *
 * Sample Input:
 *   2
 *   Atif Ahmed
 *   23
 *   78 85 91
 *   Riya Sen
 *   24
 *   66 72 80
 *
 * Sample Output:
 *   Enter the number of students: 2
 *   Enter the name: Atif Ahmed
 *   Enter the roll number: 23
 *   Enter the marks for 3 subjects: 78 85 91
 *   Enter the name: Riya Sen
 *   Enter the roll number: 24
 *   Enter the marks for 3 subjects: 66 72 80
 *   Name: Atif Ahmed
 *   Roll Number: 23
 *   Total Marks: 254.00
 *   Average Marks: 84.67
 *   Name: Riya Sen
 *   Roll Number: 24
 *   Total Marks: 218.00
 *   Average Marks: 72.67
 */

#include<stdio.h>

typedef struct student
{
        char name[50];
        int rollnumber;
        float marks[3];
} Student;

int main(){
	int n;
	printf("Enter the number of students: ");
	scanf("%d", &n);
	Student s1[n];
        for(int i = 0; i < n; i++){
                printf("Enter the name: ");
                scanf(" %[^\n]", s1[i].name); //allow whitespace
                printf("Enter the roll number: ");
                scanf("%d", &s1[i].rollnumber);
                printf("Enter the marks for 3 subjects: ");
                scanf("%f %f %f", &s1[i].marks[0], &s1[i].marks[1], &s1[i].marks[2]);
        }
	for(int i = 0; i < n; i++){
                float avg = (s1[i].marks[0] + s1[i].marks[1] + s1[i].marks[2]) / 3.0;
                float total = (s1[i].marks[0] + s1[i].marks[1] + s1[i].marks[2]);
                printf("Name: %s\n", s1[i].name);
                printf("Roll Number: %d\n", s1[i].rollnumber);
                printf("Total Marks: %.2f\n", total);
                printf("Average Marks: %.2f\n", avg);
        }

}
