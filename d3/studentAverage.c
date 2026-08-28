/*
 * Q. Write a C program to create a structure "student" that stores the name,
 *    roll number and marks of 3 subjects of a student. Read the details from
 *    the user and print the student information along with the average marks.
 *
 * Sample Input:
 *   Atif Ahmed
 *   23
 *   78 85 91
 *
 * Sample Output:
 *   Enter the name: Atif Ahmed
 *   Enter the roll number: 23
 *   Enter the marks for 3 subjects: 78 85 91
 *   Name: Atif Ahmed
 *   Roll Number: 23
 *   Average Marks: 84.67
 */

#include<stdio.h>

typedef struct student
{
	char name[50];
	int rollnumber;
	int marks[3];
} Student;

int main()
{
 	Student s1;
   	printf("Enter the name: ");
   	scanf(" %[^\n]", s1.name); //allow whitespace
   	printf("Enter the roll number: ");
   	scanf("%d", &s1.rollnumber);
   	printf("Enter the marks for 3 subjects: ");
    	scanf("%d %d %d", &s1.marks[0], &s1.marks[1], &s1.marks[2]);
    	float avg = (s1.marks[0] + s1.marks[1] + s1.marks[2]) / 3.0;
    	printf("Name: %s\n", s1.name);
    	printf("Roll Number: %d\n", s1.rollnumber);
    	printf("Average Marks: %.2f\n", avg);
    	return 0;
}
