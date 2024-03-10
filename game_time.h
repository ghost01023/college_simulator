//
// Created by Rosja Dostoyevsjky on 2/4/2024.
//
#include "game_save.h"

#ifndef GAME_TIME_H
#define GAME_TIME_H

const unsigned long long TIME = 1577817000000;
unsigned long long milliSecondsInDay = 86400000;
unsigned long long milliSecondsInHour = 3600000;
unsigned long long milliSecondsInMinute = 60000;

typedef struct {
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
} GameTime;

bool isLeapYear(int year), isDayOver(GameTime gTime);

void printDateTime(GameTime gTime);

void printDate(GameTime gTime);

void printTime(GameTime gTime);

GameTime AddMinute(GameTime *gTime);

GameTime AddHour(GameTime *gTime);

GameTime AddDay(GameTime *gTime);


void printDate(GameTime gTime) {
    char **months = (char **) malloc(sizeof(char *) * 12);
    *(months + 0) = "January";
    *(months + 1) = "February";
    *(months + 2) = "March";
    *(months + 3) = "April";
    *(months + 4) = "May";
    *(months + 5) = "June";
    *(months + 6) = "July";
    *(months + 7) = "August";
    *(months + 8) = "September";
    *(months + 9) = "October";
    *(months + 10) = "November";
    *(months + 11) = "December";
    printf("%d %s, %d", gTime.day, *(months + (gTime.month - 1)), gTime.year);
    free(months);
}

void printDateTime(GameTime gTime) {
    char **months = (char **) malloc(sizeof(char *) * 12);
    *(months + 0) = "January";
    *(months + 1) = "February";
    *(months + 2) = "March";
    *(months + 3) = "April";
    *(months + 4) = "May";
    *(months + 5) = "June";
    *(months + 6) = "July";
    *(months + 7) = "August";
    *(months + 8) = "September";
    *(months + 9) = "October";
    *(months + 10) = "November";
    *(months + 11) = "December";
    char *hour, *minute, *second;
    hour = (char *)malloc(5* sizeof(char));
    minute = (char *)malloc(5* sizeof(char));
    second = (char *)malloc(5* sizeof(char));
    char *dtChar = (char *) malloc(sizeof(char) * 5);
    printf("OK");
    if (gTime.hour < 10) {
        itoa(gTime.hour, dtChar, 10);
        hour = "\0";
        printf("%s", dtChar);
        strcat(hour, dtChar);
    } else {
        strcpy(hour, dtChar);
    }
    if (gTime.minute < 10) {
        itoa(gTime.minute, dtChar, 10);
        minute = "0\0";
        strcat(minute, dtChar);
    } else {
        strcpy(minute, dtChar);
    }
    if (gTime.second < 10) {
        itoa(gTime.second, dtChar, 10);
        second = "0\0";
        strcat(second, dtChar);
    } else {
        strcpy(second, dtChar);
    }
    printf("%d %s, %d | %d:%s:%s\t", gTime.day,
           *(months + (gTime.month - 1)), gTime.year, gTime.hour, minute,
           second);
    free(hour);
    free(minute);
    free(second);
}

GameTime AddMinute(GameTime *gTime) {
    if (gTime->minute == 59) {
        gTime->minute = 0;
        *gTime = AddHour(gTime);
    } else {
        gTime->minute++;
    }
    return *gTime;
}


GameTime AddHour(GameTime *gTime) {
    if (gTime->hour == 23) {
        gTime->hour = 0;
        *gTime = AddDay(gTime);
    } else {
        gTime->hour++;
    }
    return *gTime;
}

GameTime AddDay(GameTime *gTime) {
    if (gTime->month == 2) {
        if (isLeapYear(gTime->year) && gTime->day == 28) {
            gTime->day++;
        } else if (gTime->day == 28 || gTime->day == 29) {
            gTime->day = 1;
            gTime->month++;
        }
    }
    if (gTime->day == 30) {
        if ((gTime->month == 1) || (gTime->month == 3) ||
            (gTime->month == 5) || (gTime->month == 7) ||
            (gTime->month == 1) || (gTime->month == 8) ||
            (gTime->month == 10) || (gTime->month == 12)) {
            gTime->day++;
        } else {
            gTime->month++;
            gTime->day = 1;
        }
    } else if (gTime->day == 31) {
        if (gTime->month == 12) {
            gTime->year++;
            gTime->month = 1;
            gTime->day = 1;
        } else {
            gTime->month++;
            gTime->day = 1;
        }
    } else {
        gTime->day++;
    }
    return *gTime;
}

GameTime setNextDay(GameTime *gTime) {
    gTime->hour = 9;
    gTime->minute = 0;
    gTime->second = 0;
    GameTime temp = AddDay(gTime);
    return temp;
}


bool endOfDay(GameTime gTime) {
    return gTime.hour > 5;
}


bool isLeapYear(int year) {
    if (year % 400 == 0) {
        return true;
    } else if (year % 100 == 0) {
        return false;
    } else if (year % 4 == 0) {
        return true;
    } else {
        return false;
    }
}

bool isDayOver(GameTime gTime) {
    return gTime.hour >= 17;
}

#endif //GAME_TIME_H
