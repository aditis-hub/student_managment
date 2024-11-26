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
    printf("----Display Menu----\n");
    printf("1. All student details\n");
    printf("2. Particular student details\n");
        printf("3. Save data to CSV\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

    printf("Enter no. of students: ");
    scanf("%d", &numStudents);
    printf("Enter no. of subjects: ");
    scanf("%d", &numSubjects);

    struct Student* students = (struct Student*)malloc(numStudents * sizeof(struct Student));

    char subjectNames[10][50];
    for (int i = 0; i < numSubjects; i++) {
        printf("Enter the name of subject %d: ", i + 1);
        scanf("%s", subjectNames[i]);
    }

    for (int i = 0; i < numStudents; i++) {
        printf("----------Enter the details for student %d-------------\n", i + 1);
        printf("Enter the student Roll no.: ");
        scanf("%d", &students[i].rollNo);
        printf("Enter the student name: ");
        scanf("%s", students[i].name);

        students[i].subjectMarks = (int*)malloc(numSubjects * sizeof(int));

        for (int j = 0; j < numSubjects; j++) {
            printf("Enter %s mark: ", subjectNames[j]);
            scanf("%d", &students[i].subjectMarks[j]);
        }

        calculateAverageAndGrade(&students[i], numSubjects);
    }

    int choice;
    do {
        printf("----Display Menu----\n");
        printf("1. All student details\n");
        printf("2. Particular student details\n");
        printf("3. Save data to CSV\n");
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
            default:
                printf("Invalid choice. Try again.\n");
        }

        char continueChoice;
        printf("Do you want to continue to display (Y/y): ");
        scanf(" %c", &continueChoice);

        if (continueChoice != 'Y' && continueChoice != 'y') {
            break;
        }
    } while (1);

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
    printf("Roll No.   Name           ");
    for (int i = 0; i < numSubjects; i++) {
        printf("%-15s", subjectNames[i]);
    }
    printf("Average       Grade\n");

    for (int i = 0; i < numStudents; i++) {
        printf("%-10d %-15s", students[i].rollNo, students[i].name);
        for (int j = 0; j < numSubjects; j++) {
            printf("%-15d", students[i].subjectMarks[j]);
        }
        printf("%-12.2f %c\n", students[i].average, students[i].grade);
    }
}

void displayParticularStudentDetails(struct Student* students, int numStudents, int numSubjects, char subjectNames[][50]) {
    int rollNo;
    printf("----Menu for Particular student----\n");
    printf("1. Name\n");
    printf("2. Roll no.\n");
    printf("Enter your choice: ");
    int choice;
    scanf("%d", &choice);

    switch (choice) {
        case 1: {
            printf("Enter the name of the student: ");
            char name[50];
            scanf("%s", name);

            for (int i = 0; i < numStudents; i++) {
                if (strcmp(students[i].name, name) == 0) {
                    printf("Roll No.   Name           ");
                    for (int j = 0; j < numSubjects; j++) {
                        printf("%-15s", subjectNames[j]);
                    }
                    printf("Average       Grade\n");
                    printf("%-10d %-15s", students[i].rollNo, students[i].name);
                    for (int j = 0; j < numSubjects; j++) {
                        printf("%-15d", students[i].subjectMarks[j]);
                    }
                    printf("%-12.2f %c\n", students[i].average, students[i].grade);
                    return;
                }
            }
            printf("Student not found.\n");
            break;
        }
        case 2:
            printf("Enter the roll no. of the student: ");
            scanf("%d", &rollNo);

            for (int i = 0; i < numStudents; i++) {
                if (students[i].rollNo == rollNo) {
                    printf("Roll No.   Name           ");
                    for (int j = 0; j < numSubjects; j++) {
                        printf("%-15s", subjectNames[j]);
                    }
                    printf("Average       Grade\n");
                    printf("%-10d %-15s", students[i].rollNo, students[i].name);
                    for (int j = 0; j < numSubjects; j++) {
                        printf("%-15d", students[i].subjectMarks[j]);
                    }
                    printf("%-12.2f %c\n", students[i].average, students[i].grade);
                    return;
                }
            }
            printf("Student not found.\n");
            break;
        default:
            printf("Invalid choice.\n");
    }
}

void saveToCSV(struct Student* students, int numStudents, int numSubjects, char subjectNames[][50]) {
    FILE* file = fopen("student_data.csv", "w"); // Specify the path here

    if (file == NULL) {
        printf("Error opening file for writing: Permission denied\n");
        return;
    }

    // Write the header
    fprintf(file, "Roll No., Name, ");
    for (int i = 0; i < numSubjects; i++) {
        fprintf(file, "%s, ", subjectNames[i]);
    }
    fprintf(file, "Average, Grade\n");

    // Write student data
    for (int i = 0; i < numStudents; i++) {
        fprintf(file, "%d, %s, ", students[i].rollNo, students[i].name);
        for (int j = 0; j < numSubjects; j++) {
            fprintf(file, "%d, ", students[i].subjectMarks[j]);
        }
        fprintf(file, "%.2f, %c\n", students[i].average, students[i].grade);
    }

    fclose(file);
    printf("Data successfully saved to student_data.csv\n");
}