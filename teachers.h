//
// Created by Rosja Dostoyevsjky on 2/1/2024.
//
#ifndef TEACHERS_H
#define TEACHERS_H

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <stdio.h>
const char *teachLoc = "..\\databases\\teachers.txt";

//STRUCT OF TEACHER
//SINGLY LINKED LIST
//WILL EACH BE OF TEACHERS IN A PARTICULAR DEPARTMENT
typedef struct teacherStruct {
    char name[30];
    bool tenure;
    int pay;
    char dept[10];
    int pendingPay;
    struct teacherStruct *next;
} TeacherNode;
//CIRCULAR QUEUE OF SINGLY LINKED LIST OF TEACHERS
typedef struct {
    TeacherNode *allNodes;
    int rear;
} TeachersDLL;

void displayTeacherNode(TeacherNode *Head);

TeacherNode initTeacherNode();

TeachersDLL initTeacherDLL();



TeachersDLL insertTeacherNode(TeachersDLL *tdll, TeacherNode tNode) {
//    printf("Inserting...");
    *(tdll->allNodes + (tdll->rear++)) = tNode;
//    printf("Inserted\n\n");
//    printf("%s\n", (*(tdll->allNodes + (tdll->rear - 1))).name);
    return *tdll;
}

TeacherNode insertTeacher(TeacherNode *Head, TeacherNode nextTeacher) {
    TeacherNode *temp = (TeacherNode *)malloc(sizeof(TeacherNode));
    strcpy(temp->dept, nextTeacher.dept);
    strcpy(temp->name, nextTeacher.name);
    temp->tenure = nextTeacher.tenure;
    temp->pay = nextTeacher.pay;
    temp->pendingPay = nextTeacher.pendingPay;
    temp->next = NULL;
    TeacherNode *curr = Head;
    if (*(curr->name) == '\0') {
        return *temp;
    }
    while (curr->next != NULL) {
        curr = curr->next;
    }
    curr->next = temp;
    return *Head;
}

void displayTeacherNode(TeacherNode *Head) {
    char dept[5];
    strcpy(dept, Head->dept);
    printf("\nDisplaying Teachers in the %s Department\n\n", dept);
    TeacherNode *curr = Head;
    while (curr != NULL) {
        printf("%s \t %s \t %d \t %d \t %d\n", curr->name,
               curr->dept, curr->pay, curr->pendingPay, curr->tenure);
        curr = curr->next;
    }
}

void displayTeachersDLL(TeachersDLL teacherDLL) {
    for (int i = 0; i < teacherDLL.rear; i++) {
        displayTeacherNode(&teacherDLL.allNodes[i]);
    }
}


TeachersDLL loadAllTeachers() {
    TeachersDLL AllTeachers = initTeacherDLL();
    FILE *teachFile = fopen(teachLoc, "r");
    char teacherData[50];
    TeacherNode tNode = initTeacherNode();
    while (fgets(teacherData, 50, teachFile) != NULL) {
        //ASSIGN TEACHER-NODE DATA IF END OF DEPARTMENT CHUNK IS REACHED
        if (teacherData[0] == '/') {
            AllTeachers = insertTeacherNode(&AllTeachers, tNode);
            tNode = initTeacherNode();
            continue;
        }
        TeacherNode temp;
        int tempIt = 0;
        char name[30], dept[10];
        bool tenure = false;
        char pay[10], pendingPay[10];
        //PARSE EACH FACULTY DETAIL LINE SEPARATED BY {;}
        for (int i = 0; i < strlen(teacherData);) {
            while (teacherData[i] != ',') {
                name[tempIt++] = teacherData[i++];
            }
            i += 1;
            name[tempIt] = '\0';
            tempIt = 0;
            strcpy(temp.name, name);
            while (teacherData[i] != ',') {
                dept[tempIt++] = teacherData[i++];
            }
            dept[tempIt] = '\0';
            i += 1;
            tempIt = 0;
            strcpy(temp.dept, dept);
            if (teacherData[i++] == '1') {
                tenure = true;
            }
            temp.tenure = tenure;
            i += 1;
            while (teacherData[i] != ',') {
                pay[tempIt++] = teacherData[i++];
            }
            pay[tempIt] = '\0';
            temp.pay = atoi(pay);
            tempIt = 0;
            i += 1;
            while(teacherData[i] != ';') {
                pendingPay[tempIt++] = teacherData[i++];
            }
            pendingPay[i] = '\0';
            i += 2;
            temp.pendingPay = atoi(pendingPay);
            tNode = insertTeacher(&tNode, temp);
//            printf("\nCompleted scan of one faculty.\n");
        }
    }
    return AllTeachers;
}

TeachersDLL initTeacherDLL() {
    TeachersDLL tdll;
    tdll.allNodes = (TeacherNode *)malloc(sizeof(TeacherNode) * 5);
    tdll.rear = 0;
    return tdll;
}

TeacherNode initTeacherNode() {
    TeacherNode temp;
    strcpy(temp.name, "\0");
    temp.next = NULL;
    return temp;
}

void writeToTeachFile(TeachersDLL tdll) {
    FILE *teachFile = fopen(teachLoc, "w");
    for (int i = 0; i < 5; i++) {
        TeacherNode *currNode = &tdll.allNodes[i];
//        displayTeacherNode(&tdll.allNodes[i]);
        while(currNode != NULL) {
            //ITERATE OVER EACH TEACHER_NODE STRUCT
            char name[40], dept[10], tenure[2] = {'1', '\0'}, pay[10], pendingPay[10];
            itoa(currNode->pay, pay, 10);
            itoa(currNode->pendingPay, pendingPay, 10);
            strcpy(name, currNode->name);
            strcpy(dept, currNode->dept);
            if(!currNode->tenure) {
                tenure[0] = '0';
            }
            char teacherLine[100] = {'\0'};
            strcat(teacherLine, name);
            strcat(teacherLine, ",");
            strcat(teacherLine, dept);
            strcat(teacherLine, ",");
            strcat(teacherLine, tenure);
            strcat(teacherLine, ",");
            strcat(teacherLine, pay);
            strcat(teacherLine, ",");
            strcat(teacherLine, pendingPay);
            strcat(teacherLine, ";\n");
//            printf("The line is %s\n", teacherLine);
            fputs(teacherLine, teachFile);
            currNode = currNode->next;
        }
        fputs("/\\\n\0", teachFile);
    }
    fclose(teachFile);
}

#endif //TEACHERS_H
