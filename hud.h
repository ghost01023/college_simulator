//
// Created by Rosja Dostoyevsjky on 2/4/2024.
//

#ifndef HUD_H
#define HUD_H

#include "library.h"
#include "game_save.h"
#include "admission_q.h"
#include "all_students.h"
#include "teachers.h"
#include "game_time.h"
#include<ctype.h>
char *lib_art = "..\\databases\\lib_art.txt";

void toLower(char *upper) {
    for (int i = 0; *(upper + i) != '\0'; i++) {
        *(upper+i) = tolower(*(upper + i));
    }
}

void consume(SaveData *sData, int addable) {
    if(sData->health + addable > 100) {
        sData->health = 100;
    } else {
        sData->health += addable;
    }
}

void consumeDrink(SaveData *sData) {
    consume(sData, 2);
}

void consumeFood(SaveData *sData) {
    consume(sData, 4);
}

void consumeFullMeal(SaveData *sData) {
    consume(sData, 5);
}

void renderHUD(TeachersDLL tDLL, Student studNode, Library libData,
               SaveData sData, GameTime gTime, AdmissionQ adQueue) {
    printf("\n\nEAST POINT COLLEGE OF ENGINEERING AND TECHNOLOGY\n");
    printf("=========================================================="
           "=====================\n");
    printf("DATE: ");
    printDateTime(gTime);
    printf("\t\t\t");
    printf("HEALTH: %d", sData.health);
    printf("\n");
    bool teacherPayPending = false;
    for (int i = 0; i < 5; i++) {
        TeacherNode *curr = &tDLL.allNodes[i];
        bool found = false;
        while(curr != NULL) {
            if(curr->pendingPay > 0) {
                found = true;
                break;
            }
        }
        if(found) {
            teacherPayPending = true;
            break;
        }
    }
    printf("Total Loans Taken: %d\t\t", sData.loans);
    printf("College Budget: %d\n", sData.collegeFunds);
    printf("Personal Funds: %d\n", sData.personalFunds);
    if (teacherPayPending) {
        printf("Teachers Dept. [*]\t\t\t");
    } else {
        printf("Teachers Dept. [-]\t\t\t");
    }
    if (libData.count < 100) {
        printf("Library [*]\n");
    } else {
        printf("Library [-]\n");
    }
    if (adQueue.qSize > 0) {
        printf("Admission Department: [*]\n");
    }
    else {
        printf("Admission Department: [-]\n");
    }
    printf("=========================================================="
           "=====================\n");
}

void renderFile(char *fileLoc) {
    printf("\n");
    printf("=========================================================="
           "=====================\n");
    FILE *artFile = fopen(fileLoc, "r");
    char line[250];
    while(fgets(line, 250, artFile) != NULL) {
        printf("%s", line);
    }
}

void renderLibrary(Library mainLibNode, Library borrowedNode) {
    renderFile(lib_art);
    printf("Available Books: %d", mainLibNode.count);
    printf("\tBooks to Collect: %d\n", borrowedNode.count);
    printf("=========================================================="
           "=====================\n");
}

#endif //HUD_H
