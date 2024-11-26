#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    int rollNo;
    char name[50];
    int* subjectMarks;
    float average;
    char grade;
};

void calculateAverageAndGrade(struct Student* student, int numSubjects);
void displayAllStudentDetails(struct Student* students, int numStudents, int numSubjects, char subjectNames[][50]);
void displayParticularStudentDetails(struct Student* students, int numStudents, int numSubjects, char subjectNames[][50]);
void saveToCSV(struct Student* students, int numStudents, int numSubjects, char subjectNames[][50]);

int main() {
    int numStudents, numSubjects;

    printf("Welcome to the Student Information System!\n");
    printf("Please enter the number of students: ");
    scanf("%d", &numStudents);
    printf("Please enter the number of subjects: ");
    scanf("%d", &numSubjects);

    struct Student* students = (struct Student*)malloc(numStudents * sizeof(struct Student));
    char subjectNames[10][50];
    
    for (int i = 0; i < numSubjects; i++) {
        printf("Enter the name of subject %d: ", i + 1);
        scanf("%s", subjectNames[i]);
    }

    for (int i = 0; i < numStudents; i++) {
        printf("\n---------- Enter the details for Student %d -----------\n", i + 1);
        printf("Enter Roll No.: ");
        scanf("%d", &students[i].rollNo);
        printf("Enter Name: ");
        scanf("%s", students[i].name);

        students[i].subjectMarks = (int*)malloc(numSubjects * sizeof(int));
        for (int j = 0; j < numSubjects; j++) {
            int mark;
            do {
                printf("Enter %s mark (0-100): ", subjectNames[j]);
                scanf("%d", &mark);
                if (mark < 0 || mark > 100) {
                    printf("Invalid mark! Please enter a value between 0 and 100.\n");
                }
            } while (mark < 0 || mark > 100);
            students[i].subjectMarks[j] = mark;
        }

        calculateAverageAndGrade(&students[i], numSubjects);
    }

    int choice;
    do {
        printf("\n---- Display Menu ----\n");
        printf("1. Display All Student Details\n");
        printf("2. Display Particular Student Details\n");
        printf("3. Save Data to CSV\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayAllStudentDetails(students, numStudents, numSubjects, subjectNames);
                break;
            case 2:
                displayParticularStudentDetails(students, numStudents, numSubjects, subjectNames);
                break;
            case 3:
                saveToCSV(students, numStudents, numSubjects, subjectNames);
                break;
            case 4:
                printf("Exiting the program. Thank you!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4);

    for (int i = 0; i < numStudents; i++) {
        free(students[i].subjectMarks);
    }
    free(students);

    return 0;
}

void calculateAverageAndGrade(struct Student* student, int numSubjects) {
    int totalMarks = 0;
    for (int i = 0; i < numSubjects; i++) {
        totalMarks += student->subjectMarks[i];
    }

    student->average = (float)totalMarks / numSubjects;

    if (student->average >= 90) {
        student->grade = 'A';
    } else if (student->average >= 80) {
        student->grade = 'B';
    } else if (student->average >= 70) {
        student->grade = 'C';
    } else if (student->average >= 60) {
        student->grade = 'D';
    } else {
        student->grade = 'F';
    }
}

void displayAllStudentDetails(struct Student* students, int numStudents, int numSubjects, char subjectNames[][50]) {
    printf("\nRoll No.   Name           ");
    for (int i = 0; i < numSubjects; i++) {
        printf("%-15s", subjectNames[i]);
    }
    printf("Average       Grade\n");

    for (int i = 0; i < numStudents; i++) {
        printf("%-10d %-15s", students[i].rollNo, students[i].name);
        for (int j = 0; j < numSubjects; j++) {
            printf("%-15d", students[i].subjectMarks[j]);
        }
        printf("%-15.2f %-5c\n", students[i].average, students[i].grade);
    }
}

void displayParticularStudentDetails(struct Student* students, int numStudents, int numSubjects, char subjectNames[][50]) {
    int rollNo;
    printf("Enter Roll No. of the student to display details: ");
    scanf("%d", &rollNo);

    for (int i = 0; i < numStudents; i++) {
        if (students[i].rollNo == rollNo) {
            printf("\nDetails for Student Roll No. %d:\n", rollNo);
            printf("Name: %s\n", students[i].name);
            for (int j = 0; j < numSubjects; j++) {
                printf("%s: %d\n", subjectNames[j], students[i].subjectMarks[j]);
            }
            printf("Average: %.2f\n", students[i].average);
            printf("Grade: %c\n", students[i].grade);
            return;
        }
    }
    printf("Student with Roll No. %d not found.\n", rollNo);
}

void saveToCSV(struct Student* students, int numStudents, int numSubjects, char subjectNames[][50]) {
    FILE* file = fopen("students.csv", "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    fprintf(file, "Roll No,Name,");
    for (int i = 0; i < numSubjects; i++) {
        fprintf(file, "%s,", subjectNames[i]);
    }
    fprintf(file, "Average,Grade\n");

    for (int i = 0; i < numStudents; i++) {
        fprintf(file, "%d,%s,", students[i].rollNo, students[i].name);
        for (int j = 0; j < numSubjects; j++) {
            fprintf(file, "%d,", students[i].subjectMarks[j]);
        }
        fprintf(file, "%.2f,%c\n", students[i].average, students[i].grade);
    }

    fclose(file);
    printf("Data saved to students.csv successfully.\n");
}
