//
// Created by Rosja Dostoyevsjky on 1/17/2024.
//

#ifndef ADMISSION_Q_H
#define ADMISSION_Q_H

#include<unistd.h>
#include<time.h>
#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>

#define MAX_Q 30
char *adArtFileLoc = "..\\databases\\admission_art.txt";

typedef struct {
    bool isManagement, hasScholarship;
    short visits;
    unsigned int admissionFees;
} Admitee;


typedef struct {
    int front, rear;
    Admitee admitees[MAX_Q];
    short qSize;
} AdmissionQ;

char *adFileLoc = "..\\databases\\admissionQueue.txt";

bool isEmptyQ(AdmissionQ *q) {
    return q->rear == q->front;
}


bool isFullAQ(AdmissionQ *q) {
    return ((q->front == q->rear + 1) || (q->front == 0 && q->rear == MAX_Q - 1));
}


AdmissionQ insertAQ(AdmissionQ *q, Admitee a) {
    if (isFullAQ(q)) {
        printf("Sorry, we are currently not accepting any new admissions.\n");
    } else {
        q->rear = (q->rear + 1) % MAX_Q;
        if (q->front == -1) {
            q->front = 0;
        }
        q->admitees[q->rear] = a;
        q->qSize++;
        return *q;
    }
//    printf("Admitted to Admission Queue\n");
}


Admitee removeAQ(AdmissionQ *q) {
    if (isEmptyQ(q)) {
        printf("nothing to remove from admission queue.\n");
    } else {
        Admitee temp = q->admitees[q->front];
        if (q->front == q->rear) {
            q->front = q->rear = -1;
        } else {
            q->front = (q->front + 1) % MAX_Q;
        }
        q->qSize--;
        printf("Removed from the front of the admission queue.\n");
        return temp;
    }
}


Admitee generateAdmitee() {
    Admitee a;
    srand(time(NULL));
    a.isManagement = (rand() * 5) % 2;
    a.hasScholarship = (rand() * 5) % 2;
    a.visits = 0;
    if (a.hasScholarship) {
        a.admissionFees = 120000;
    } else {
        a.admissionFees = 250000;
    }
    return a;
}


void displayQ(AdmissionQ *q) {
    if (isEmptyQ(q)) {
        printf("\nQueue is empty\n");
    } else {
        printf("Displaying Admission Queue\n");
        int i;
        printf("\n");
        for (i = q->front; i != q->rear; i = (i + 1) % MAX_Q) {
            printf("Admitee %d: %d %d %d %d\n", i + 1, q->admitees[i].isManagement,
                   q->admitees[i].hasScholarship, q->admitees[i].visits, q->admitees[i].admissionFees);
        }
        printf("Admitee %d: %d %d %d %d\n", i + 1, q->admitees[i].isManagement,
               q->admitees[i].hasScholarship, q->admitees[i].visits, q->admitees[i].admissionFees);
    }
}


bool moveAheadAdQ(AdmissionQ *q) {
    Admitee temp = q->admitees[q->front];
    removeAQ(q);
    insertAQ(q, temp);
    return true;
}


void giveAdmission(AdmissionQ *q) {//REMOVES FIRST STUDENT FROM AD-QUEUE
    Admitee temp = q->admitees[q->front];//ADDS STUDENT TO STUDENT LIST
    removeAQ(q);
}


AdmissionQ *genAdQueue() {
    AdmissionQ *aq = (AdmissionQ *) malloc(sizeof(AdmissionQ));
    aq->front = aq->rear = -1;
    aq->qSize = 0;
    return aq;
}


AdmissionQ loadAdmissionQueue() {
    AdmissionQ *admissionQ = genAdQueue();
    char *adQueue = (char *) malloc(sizeof(char) * 1000);
    FILE *AQFile = fopen(adFileLoc, "r");
    while (fgets(adQueue, 1000, AQFile) != NULL) {
        adQueue[strlen(adQueue) - 1] = '\0';
        //PROCESS EACH LINE WHICH HAS DATA ABOUT EACH STUDENT
        bool scholarship = false, management = false;
        short visits;
        unsigned int fees;
        if (adQueue[0] == 't') {
            management = true;
        }
        if (adQueue[2] == 't') {
            scholarship = true;
        }
        visits = (short) (adQueue[4] - '0');
        char fee[10];
        for (int i = 0; i < 10; i++) {
            fee[i] = adQueue[6 + i];
        }
        fees = (unsigned int) atol(fee);
        Admitee ad = {management, scholarship, visits, fees};
        insertAQ(admissionQ, ad);
//        printf("%d %d %d %d\n", ad.isManagement, ad.hasScholarship, ad.visits, ad.admissionFees);
    }
    free(adQueue);
    fclose(AQFile);
    return *admissionQ;
}

void writeToAQFile(AdmissionQ *admissionQ) {
    FILE *qFile = fopen(adFileLoc, "w");
    for (int i = 0; i < admissionQ->qSize; i++) {
        Admitee curr = admissionQ->admitees[i];
        char manag = (!curr.isManagement) ? 'f' : 't';
        char schol = (!curr.hasScholarship) ? 'f' : 't';
        char visits = (char) (curr.visits + 48);
        char fees[10];
        itoa(curr.admissionFees, fees, 10);
//        printf("%c\t%c\t%c\t%s\n", manag, schol, visits, fees);
        char data[20] = {schol, ',', manag, ',', visits, ',', '\0'};
        size_t j;
        int k = 0;
        for (j = strlen(data); fees[k] != '\0'; k++) {
            data[j++] = fees[k];
        }
        data[j++] = ';';
        data[j++] = '\n';
        data[j] = '\0';
//        printf("Data new line is %s", data);
        fputs(data, qFile);
    }
    fclose(qFile);
}

void renderAdmissionDept() {
    FILE *adArtFile = fopen(adArtFileLoc, "r");
    char artLine[400];
    while (fgets(artLine, 400, adArtFile) != NULL) {
        printf("%s", artLine);
    }
}

#endif //ADMISSION_Q_H
