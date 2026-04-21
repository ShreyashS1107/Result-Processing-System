#include <stdio.h>
#include <string.h>
#define SUBJECTS 5   // number of subjects
#define MAX 100      // maximum students
// Structure to store student details
struct Student {
    int roll;
    char name[50];
    float marks[SUBJECTS];
    float total;
    float avg;
    char grade;
};
// Global array of students
struct Student s[MAX];
int n = 0;              // number of students
int dataEntered = 0;    // flag to check if data is entered

// Function declarations
void inputData();
void calculate();
void displayReport();
void displayRank();
void searchStudent();

int main() {
    int choice;
    do {
        printf("\n------ RESULT PROCESSING SYSTEM -----\n");
        printf("1. Input Student Data\n");
        printf("2. Show Report Cards\n");
        printf("3. Display Rank List\n");
        printf("4. Search Student\n");
        printf("5. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                inputData();
                break;
            case 2:
                if(dataEntered) displayReport();
                else printf("Please enter data first!\n");
                break;
            case 3:
                if(dataEntered) displayRank();
                else printf("Please enter data first!\n");
                break;
            case 4:
                if(dataEntered) searchStudent();
                else printf("Please enter data first!\n");
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while(choice != 5);
    return 0;
}
// Input student details
void inputData() {
    printf("Enter number of students: ");
    scanf("%d", &n);

    if(n > MAX) {
        printf("Limit exceeded! Max is %d\n", MAX);
        return;}

    for(int i = 0; i < n; i++) {
        printf("\nStudent %d\n", i + 1);

        printf("Enter Roll: ");
        scanf("%d", &s[i].roll);

        printf("Enter Name: ");
        scanf(" %[^\n]", s[i].name);
        //%[^\n]to read everything other than\n
        printf("Enter marks of %d subjects:\n", SUBJECTS);
        for(int j = 0; j < SUBJECTS; j++)
            scanf("%f", &s[i].marks[j]);
    }
    dataEntered = 1; // data is now available
}
// Calculate total, average and grade
void calculate() {
    for(int i = 0; i < n; i++) {
        s[i].total = 0;

        for(int j = 0; j < SUBJECTS; j++)
            s[i].total += s[i].marks[j];

        s[i].avg = s[i].total / SUBJECTS;
        // Assign grade based on average
        if(s[i].avg >= 90) s[i].grade = 'A';
        else if(s[i].avg >= 75) s[i].grade = 'B';
        else if(s[i].avg >= 60) s[i].grade = 'C';
        else if(s[i].avg >= 50) s[i].grade = 'D';
        else s[i].grade = 'F';
    }
}
// Display report card of all students
void displayReport() {
    calculate();  // ensure values are updated

    for(int i = 0; i < n; i++) {
        printf("\n----- STUDENT REPORT -----\n");

        printf("Roll: %d\n", s[i].roll);
        printf("Name: %s\n", s[i].name);

        printf("Marks: ");
        for(int j = 0; j < SUBJECTS; j++)
            printf("%.2f ", s[i].marks[j]);

        printf("\nTotal: %.2f\n", s[i].total);
        printf("Average: %.2f\n", s[i].avg);
        printf("Grade: %c\n", s[i].grade);
    }
}
// Display rank list based on average
void displayRank() {
    struct Student temp[MAX];  // temporary array for sorting
    // Copy original data
    for(int i = 0; i < n; i++)
        temp[i] = s[i];
    // Calculate average for temp array
    for(int i = 0; i < n; i++) {
        temp[i].total = 0;
        for(int j = 0; j < SUBJECTS; j++)
            temp[i].total += temp[i].marks[j];

        temp[i].avg = temp[i].total / SUBJECTS;
    }
    // Sort in descending order of average
    for(int i = 0; i < n - 1; i++) {
        for(int j = i + 1; j < n; j++) {
            if(temp[j].avg > temp[i].avg) {
                struct Student t = temp[i];
                temp[i] = temp[j];
                temp[j] = t;
            }
        }
    }
    printf("\n----- RANK LIST -----\n");
    printf("Rank\t\tRoll\t\tName\t\t\t\tAverage\n");
    for(int i = 0; i < n; i++)
        printf("%d\t\t%d\t\t%s\t\t\t\t%.2f\n",
        i + 1, temp[i].roll, temp[i].name, temp[i].avg);}
// Search student by roll number
void searchStudent() {
    int roll, found = 0;
    printf("Enter roll number to search: ");
    scanf("%d", &roll);
    calculate();
    for(int i = 0; i < n; i++) {
        if(s[i].roll == roll) {
            printf("\nStudent Found!\n");

            printf("Roll: %d\n", s[i].roll);
            printf("Name: %s\n", s[i].name);

            printf("Marks: ");
            for(int j = 0; j < SUBJECTS; j++)
                printf("%.2f ", s[i].marks[j]);

            printf("\nTotal: %.2f\n", s[i].total);
            printf("Average: %.2f\n", s[i].avg);
            printf("Grade: %c\n", s[i].grade);

            found = 1;
            break;  // stop after finding
        }
    }
    if(!found)
        printf("Student not found!\n");
}
