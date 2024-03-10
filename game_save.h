//
// Created by Rosja Dostoyevsjky on 2/3/2024.
//
#ifndef GAME_SAVE_H
#define GAME_SAVE_H

#include <stdio.h>
#include <stdlib.h>
#include "game_time.h"

char *saveFileLoc = "..\\databases\\game_save.txt";

typedef struct saveFileStruct {
    int collegeFunds;
    int health;
    int loans;
    int personalFunds;
    GameTime gameTime;
} SaveData;


SaveData loadSaveData() {
    SaveData temp;
    GameTime GT;
    //INIT MONTH NAMES

    FILE *saveFile = fopen(saveFileLoc, "r");
    //FIRST LINE REGARDING FINANCES
    char Finances[100];
    fgets(Finances, 100, saveFile);
    char cFunds[20], health[5], loans[20], pFunds[20],
    tYear[15], tMonth[5], tDay[5], tHour[5], tMinute[5], tSecond[5];
    int it = 0;
    for (int i = 0; Finances[i] != '\0'; i++) {
        while(Finances[i] != ',') {
            cFunds[it++] = Finances[i++];
        }
        cFunds[it] = '\0';
        i++;
        it = 0;
        while(Finances[i] != ',') {
            health[it++] = Finances[i++];
        }
        health[it] = '\0';
        it = 0;
        i++;
        while(Finances[i] != ',') {
            loans[it++] = Finances[i++];
        }
        loans[it] = '\0';
        it = 0;
        i++;
        while(Finances[i] != ',') {
            pFunds[it++] = Finances[i++];
        }
        pFunds[it] = '\0';
        it = 0;
        i++;
        while(Finances[i] != '-') {
            tYear[it++] = Finances[i++];
        }
        tYear[it] = '\0';
        it = 0;
        i++;
        while(Finances[i] != '-') {
            tMonth[it++] = Finances[i++];
        }
        tMonth[it] = '\0';
        it = 0;
        i++;
        while(Finances[i] != '-') {
            tDay[it++] = Finances[i++];
        }
        tDay[it] = '\0';
        it = 0;
        i++;
        while(Finances[i] != '-') {
            tHour[it++] = Finances[i++];
        }
        tHour[it] = '\0';
        it = 0;
        i++;
        while(Finances[i] != '-') {
            tMinute[it++] = Finances[i++];
        }
        tMinute[it] = '\0';
        it = 0;
        i++;
        while(Finances[i] != ';') {
            tSecond[it++] = Finances[i++];
        }
        tSecond[it] = '\0';
        int year = atoi(tYear);
        int month = atoi(tMonth);
        int day = atoi(tDay);
        int hour = atoi(tHour);
        int minute = atoi(tMinute);
        int second = atoi(tSecond);
        GT.year = year;
        GT.month = month;
        GT.day = day;
        GT.hour = hour;
        GT.minute = minute;
        GT.second = second;
        temp.gameTime = GT;
        int personalFunds = atoi(pFunds);
        int healthInt = atoi(health);
        int loansInt = atoi(loans);
        int collegeFundsInt = atoi(cFunds);
        temp.personalFunds = personalFunds;
        temp.health = healthInt;
        temp.loans = loansInt;
        temp.collegeFunds = collegeFundsInt;
//        printf("\nLoaded %d %d %d %d\n", personalFunds, healthInt, loansInt, collegeFundsInt);
    }
    fclose(saveFile);
    return temp;
}


void writeToSaveDataFile(SaveData data) {
    char collegeFunds[15], health[5] = {'\0'},
    loans[15] = {'\0'}, personalFunds[10] = {'\0'},
    year[5] = {'\0'}, month[5] = {'\0'}, day[5] = {'\0'},
    hour[5] = {'\0'}, minute[5] = {'\0'}, second[5] = {'\0'};
    itoa(data.collegeFunds, collegeFunds, 10);
    itoa(data.health, health, 10);
    itoa(data.loans, loans, 10);
    itoa(data.personalFunds, personalFunds, 10);
    itoa(data.gameTime.year, year, 10);
    itoa(data.gameTime.month, month, 10);
    itoa(data.gameTime.day, day, 10);
    itoa(data.gameTime.hour, hour, 10);
    itoa(data.gameTime.minute, minute, 10);
    itoa(data.gameTime.second, second, 10);
    char dataLine[150] = {'\0'};
    strcat(dataLine, collegeFunds);
    strcat(dataLine, ",\0");
    strcat(dataLine, health);
    strcat(dataLine, ",\0");
    strcat(dataLine, loans);
    strcat(dataLine, ",\0");
    strcat(dataLine, personalFunds);
    strcat(dataLine, ",\0");
    strcat(dataLine, year);
    strcat(dataLine, "-\0");
    strcat(dataLine, month);
    strcat(dataLine, "-\0");
    strcat(dataLine, day);
    strcat(dataLine, "-\0");
    strcat(dataLine, hour);
    strcat(dataLine, "-\0");
    strcat(dataLine, minute);
    strcat(dataLine, "-\0");
    strcat(dataLine, second);
    strcat(dataLine, ";\0");
    FILE *saveDataFile = fopen(saveFileLoc, "w");
    fputs(dataLine, saveDataFile);
    fclose(saveDataFile);
}

#endif //GAME_SAVE_H
