//
// Created by Rosja Dostoyevsjky on 1/17/2024.
//

#ifndef ALL_STUDENTS_H
#define ALL_STUDENTS_H

#include<stdio.h>
#include <stdbool.h>
#include<string.h>
#include<time.h>
#include "admission_q.h"

char *studLoc = "..\\databases\\students.txt";
typedef struct stud {
    char USN[20];
    char name[50];
    char branch[10];
    int feeInstallment;//8 chars 7 for val and 1 for null char
    char state[40];
    int booksTaken; //2 char 1 for books and 1 for null char
    int admissionDate;
    struct stud *next;
} Student;


void displayStudent(Student stud);

Student addStudent(Student *Head, Student newStud);


Student loadStudents() {
    Student *tempStud = (Student *)malloc(sizeof(Student));
    tempStud->next = NULL;
    FILE *studFile = fopen(studLoc, "r");
    char student[250];
    while (fgets(student, 250, studFile) != NULL) {
        student[strlen(student) - 1] = '\0';
//        printf("%s", student);
        Student temp;
//        printf("At it");
        int feeInstallment, booksTaken, admissionDate, it, studIt = -1;
        for (it = 0, studIt++; student[studIt] != ','; studIt++) {
            temp.USN[it++] = student[studIt];
        }
        temp.USN[it] = '\0';
//        printf("%s", usn);
        for (it = 0, studIt++; student[studIt] != ','; studIt++) {
            temp.name[it++] = student[studIt];
        }
        temp.name[it] = '\0';
//        printf("\t%s", name);
        for (it = 0, studIt++; student[studIt] != ','; studIt++) {
            temp.branch[it++] = student[studIt];
        }
        temp.branch[it] = '\0';
//        printf("\t%s", branch);
        char feeInsInt[8];
        for (it = 0, studIt++; student[studIt] != ','; studIt++) {
            feeInsInt[it++] = student[studIt];
        }
        feeInsInt[it] = '\0';
//        printf("\t%s", feeInsInt);
        feeInstallment = atoi(feeInsInt);
        for (it = 0, studIt++; student[studIt] != ','; studIt++) {
            temp.state[it++] = student[studIt];
        }
        temp.state[it] = '\0';
//        printf("\t%s", state);
        char booksTakenInt[2];
        for (it = 0, studIt++; student[studIt] != ','; studIt++) {
            booksTakenInt[it++] = student[studIt];
        }
        booksTakenInt[it] = '\0';
//        printf("\t%s", booksTakenInt);
        booksTaken = atoi(booksTakenInt);
        char dateAdmit[9];
        for (it = 0, studIt++; student[studIt] != ';'; studIt++) {
            dateAdmit[it++] = student[studIt];
        }
        dateAdmit[it] = '\0';
//        printf("\t%s", dateAdmit);
        admissionDate = atoi(dateAdmit);
        temp.feeInstallment = feeInstallment;
        temp.booksTaken = booksTaken;
        temp.admissionDate = admissionDate;
        temp.next = NULL;
//        displayStudent(temp);
        addStudent(tempStud, temp);
//        printf("OK");
    }
    fclose(studFile);
    return *tempStud;
}

Student createStudent() {
    Student temp;
    printf("%llu", sizeof(temp));
    printf("Enter USN of student:\n");
//    scanf("[\n]*%s", temp.USN);
    scanf("%s", temp.USN);
    //CONVERT USN TO UPPER CASE
    //IMPLEMENT PASCAL CASE ON OTHERS LATER
    for (int i = 0; temp.USN[i] != '\0'; i++) {
        if (temp.USN[i] >= 'a' && temp.USN[i] <= 'z') {
            temp.USN[i] = (char)(temp.USN[i] - 32);
        }
    }
//    fgets(temp.USN, 20, stdin);
    printf("Enter Name of student:\n");
    scanf("%s", temp.name);
    printf("Enter Branch of student:\n");
    scanf("%s", temp.branch);
//    fgets(temp.branch, 10, stdin);
    printf("Enter State of student:\n");
//    fgets(temp.state, 25, stdin);
    scanf("%s", temp.state);
    printf("Enter Fee Installment of student:\n");
    scanf_s("%d", &temp.feeInstallment);
    temp.booksTaken = 0;
    temp.admissionDate = 1292024;
    temp.next = NULL;
    return temp;
}

Student addStudent(Student *Head, Student newStud) {
    Student *curr = Head;
//    printf("OK");
    while (curr->next != NULL) {
//        printf("%s\n", curr->name);
        curr = curr->next;
    }
    Student *temp = (Student *) malloc(sizeof(Student));
    strcpy(temp->USN, newStud.USN);
    strcpy(temp->name, newStud.name);
    strcpy(temp->branch, newStud.branch);
    temp->feeInstallment = newStud.feeInstallment;
    strcpy(temp->state, newStud.state);
    temp->booksTaken = newStud.booksTaken;
    temp->admissionDate = newStud.admissionDate;
    temp->next = NULL;
    curr->next = temp;
    return *Head;
//    displayStudent(*temp);
}

void writeToStudFile(Student *studHeadNode) {
    FILE *studFile = fopen(studLoc, "w");
    Student *curr = studHeadNode->next;
    while (curr != NULL) {
        size_t dataIt = 0;
        char data[200] = {'\0'};
        //ASSIGN THE USN
//        for (int i = 0; i < 10; i++) {
//            data[dataIt++] = curr->USN[i];
//        }
        //ASSIGN THE USN
        strcat(data, curr->USN);
        dataIt += strlen(curr->USN);
        data[dataIt++] = ',';
        data[dataIt++] = '\0';
        //ASSIGN NAME
        strcat(data, curr->name);
        dataIt += strlen(curr->name) - 1;
        data[dataIt++] = ',';
        data[dataIt++] = '\0';
        //ASSIGN BRANCH/DEPT
        strcat(data, curr->branch);
        dataIt += strlen(curr->branch) - 1;
        data[dataIt++] = ',';
        data[dataIt++] = '\0';
        //ASSIGN FEE, BOOKS TAKEN, AND ADMISSION DATE
        char feeStr[10], booksStr[2], adDateStr[10];
        itoa(curr->feeInstallment, feeStr, 10);
        strcat(data, feeStr);
        dataIt += strlen(feeStr) - 1;
        data[dataIt++] = ',';
        data[dataIt++] = '\0';
        //ASSIGN THE STATE
        strcat(data, curr->state);
        dataIt += strlen(curr->state) - 1;
        data[dataIt++] = ',';
        data[dataIt++] = '\0';
        itoa(curr->booksTaken, booksStr, 10);
        strcat(data, booksStr);
        dataIt += strlen(booksStr) - 1;
        data[dataIt++] = ',';
        data[dataIt++] = '\0';
        itoa(curr->admissionDate, adDateStr, 10);
        strcat(data, adDateStr);
        dataIt += strlen(adDateStr) - 1;
        data[dataIt++] = ';';
        data[dataIt++] = '\n';
        data[dataIt++] = '\0';
//        printf("The data is now \n%s\n\n", data);
        fputs(data, studFile);
        curr = curr->next;
//        for (int i = 0; i < strlen(curr->name); i++) {
//            data
//        }
    }
    fclose(studFile);
}

Student *genStudentHeadNode() {
    Student *temp = (Student *) malloc(sizeof(Student));
    temp->next = NULL;
    return temp;
}

Student admitteeToStudent(Admitee ad) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    printf("now: %d-%02d-%02d %02d:%02d:%02d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
    Student temp;
    temp.booksTaken = 0;
    temp.next = NULL;
    temp.feeInstallment = (int)ad.admissionFees;
    printf("Enter the Name of the Student:\n");
    scanf("%s", temp.name);
    printf("Enter the USN:\n");
    scanf("%s", temp.USN);
    printf("Enter the State:\n");
    scanf("%s", temp.state);
    printf("Enter the Branch:\n");
    scanf("%s", temp.branch);
    char day[5], month[5], year[5];
    itoa(tm.tm_year + 1900, year, 10);
    itoa(tm.tm_mon, month, 10);
    itoa(tm.tm_mday, day, 10);
    char date[15] = {'\0'};
    strcat(date, day);
    strcat(date, month);
    strcat(date, year);
    int dateInt = atoi(date);
    temp.admissionDate = dateInt;
    displayStudent(temp);
    return temp;
}

void displayStudent(const Student stud) {
    printf("%s %s %s %d %s %d %d\n", stud.USN, stud.name,
           stud.branch, stud.feeInstallment, stud.state,
           stud.booksTaken, stud.admissionDate);
}

void displayAllStudents(Student *Head) {
    Student *curr = Head->next;
    while(curr != NULL) {
        displayStudent(*curr);
        curr = curr->next;
    }
}

//void displayAllStudents(Student *studNode) {
//
//}

#endif //ALL_STUDENTS_H
