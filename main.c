#include<time.h>
#include <stdio.h>
#include <stdlib.h>
#include "./polynomial.h"
#include "./library.h"
#include "./game_save.h"
#include "./admission_q.h"
#include "./all_students.h"
#include "./teachers.h"
#include "./game_time.h"
#include "./hud.h"

//CONSTANT POINTERS TO VARIOUS TYPES OF DATABASES MODELLING DIFFERENT ASPECTS
//OF THE COLLEGE
//AdmissionQ *admissionQ;

/////////////////////////
////////////////////////
////////////////////////////
//int choice = -1;
//scanf("%d", &choice)
//switch(choice) {
// case 1:
//      admissions case
// case 2:
//      library case
// case 3:
//      due clear case
// case 4:
//      exit game (save all ad, lib, due etc progress awa money, time etc in text file
//
// }
// general save game status text file
//contains: college funds, time, date etc
///////////////////////////
// renderHud function (viable options are like {Lib [*]}
//////////////////////////
/////////////////////////
//===========================================//
//LOAD ADMISSION QUEUE DATA FROM FILE
//
//    admissionQ = loadAdmissionQueue(admissionQ);
//    printf("Initialized admission queue\n");
//    displayQ(admissionQ);
//    printf("%d", admissionQ->qSize);
//
//============================================//
//WRITE DATA TO ADMISSION QUEUE FILE BASED ON DATA IN THE CURRENT RAM-AD-QUEUE
//    Admitee john = {false, false, 7, 500000};
//    insertAQ(admissionQ, john);
//    writeToAQFile(admissionQ);
//============================================//
//INITIALIZE STUDENT HEAD NODE WITH LOADED DATA FROM STUDENTS IN STUDENTS.TXT FILE
//CREATE A NEW STUDENT BY ACCEPTING INPUT FROM USER
//THEN INSERT INTO STUDENTS LINKED LIST AND THEN WRITE NEW LINKED LIST DATA BACK TO
//TEXT FILE
//    allStudents = genStudentHeadNode();
//    loadStudents(allStudents); //LOADS ALL STUDENTS IN TEXT FILE TO CURRENT
//    Student newStud = createStudent();
//    addStudent(allStudents, newStud);
//    Student *curr = allStudents->next;        //PROVIDED STUDENTS POINTER
//    printf("Enter display...");
//    displayStudent(newStud);
//    displayStudent(*allStudents->next);
//    writeToStudFile(allStudents);
//================================================
//================================================
//SET UP LIBRARY AND ITS TEXT FILE. SIMPLE ENOUGH. FIVE LINES FOR 5 STACKS
//DEVELOP HISTOGRAM FOR LIBRARY STACKS FOR STATUS VIEWING
//SET UP APPROPRIATE WRITE FUNCTION TOWARD LIB TEXT FILE


int main() {
    TeachersDLL allTeachers = loadAllTeachers();
    printf("Loaded all teacher data...\n\n");
    //sleep(1);
    Student allStudents = loadStudents();
    printf("Loaded all student data...\n\n");
    //sleep(1);
    Library allBooks = initBookNode(libBookTxt);
    Library borrowedBooks = initBookNode(borrowedBookTxt);
    //sleep(1);
    printf("Loaded all book data...\n\n");
    //sleep(1);
    AdmissionQ allAdmitees = loadAdmissionQueue();
    //sleep(1);
    printf("Loaded all Students currently in Admission Queue...\n\n");
    SaveData sd = loadSaveData();
    //sleep(1);
    printf("Loaded Game Save Data...\n\n");
    //sleep(1);
    bool gameOn = true;
    printf("=======================================================\n");
    printf("                 Entered Diagnostic Mode\n");
    printf("=======================================================");
    //sleep(1);
    int diagFlag = 1;
    while (diagFlag) {
        printf("\n\n1. Student Data\t\t2. Teacher Data\n"
               "3. Library Data\t4. Borrowed Books\t5. Admission Queue\n6. Stats\n\n");
        printf("=======================================================\n");
        printf("\n====================ENTER YOUR CHOICE==================\n");
        int ch;
        scanf_s("%d", &ch);
        switch (ch) {
            case 1:
                displayAllStudents(&allStudents);
                break;
            case 2:
                displayTeachersDLL(allTeachers);
                break;
            case 3:
                displayAllBooks(&allBooks);
                break;
            case 4:
                displayAllBooks(&borrowedBooks);
                break;
            case 5:
                displayQ(&allAdmitees);
                break;
            case 6:
                printf("======================================"
                       "==========================================\n");
                printf("College Funds: %d\t Health:\3%d\t Loans: "
                       "%d\t Personal Funds: %d\n",
                       sd.collegeFunds, sd.health, sd.loans, sd.personalFunds);
                printf("========================================"
                       "========================================\n");
                printf("Date-Time:  ");
                printDateTime(sd.gameTime);
                break;
            default:
                printf("Exiting Diagnostic Mode...\n");
                //sleep(1);
                diagFlag = 0;
                break;
        }
    }
    char ch[15];
    while (gameOn) {
        renderHUD(allTeachers, allStudents, allBooks,
                  sd, sd.gameTime, allAdmitees);
        scanf("%s", ch);
        toLower(ch);
        if (!strcmp(ch, "exit")) {
            gameOn = false;
            writeToSaveDataFile(sd);
            writeToStudFile(&allStudents);
            writeToAQFile(&allAdmitees);
            writeToLibFile(allBooks, libBookTxt);
            writeToLibFile(borrowedBooks, borrowedBookTxt);
            writeToTeachFile(allTeachers);
        } else if (!strcmp(ch, "polynomial") || !strcmp(ch, "poly")
                   || !strcmp(ch, "exam") || !strcmp(ch, "test")) {
            if (askPolyQuestion()) {
                int reward = (rand() % 5) * 7000;
                sd.collegeFunds += reward;
                printf("Reward of %d was given.\n", reward);
            }
            for (int i = 0; i < 5; i++) {
                sd.gameTime = AddHour(&sd.gameTime);
            }
        } else if (!strcmp(ch, "admit") || !strcmp(ch, "add")) {
            allStudents = addStudent(&allStudents, admitteeToStudent(removeAQ(&allAdmitees)));
            for (int i = 0; i < 2; i++) {
                sd.gameTime = AddHour(&sd.gameTime);
            }
        } else if (!strcmp(ch, "addbook") || !strcmp(ch, "addb")) {
            Book temp = generateBook();
            displayBook(temp);
            allBooks = addBook(&allBooks, temp);
            for (int i = 0; i < 1; i++) {
                sd.gameTime = AddHour(&sd.gameTime);
            }
        } else if (!strcmp(ch, "borrow") || !strcmp(ch, "bbook") || !strcmp(ch, "bb")) {
            borrowBook(&allBooks, &borrowedBooks);
            for (int i = 0; i < 3; i++) {
                sd.gameTime = AddHour(&sd.gameTime);
            }
        } else if (!strcmp(ch, "takebook") || !strcmp(ch, "tbb")) {
            for (int i = 0; i < 1; i++) {
                sd.gameTime = AddHour(&sd.gameTime);
            }
            borrowBook(&borrowedBooks, &allBooks);
        } else if (!strcmp(ch, "borrowed") || !strcmp(ch, "bbooks")) {
            printf("DISPLAYING ALL BOOKS CURRENTLY BORROWED BY STUDENTS\n");
            displayAllBooks(&borrowedBooks);
        }
        if (isDayOver(sd.gameTime)) {
            printf("End of day reached.\nStarting Next Day...\n");
            //sleep(1);
            sd.gameTime = setNextDay(&sd.gameTime);
            //CHECK IF TIME FOR PAYMENT HAS COME

        }
        srand(time(NULL));
        int newAdmitee = rand() % 4;
        if (newAdmitee > 2 && (strcmp(ch, "exit"))) {
            allAdmitees = insertAQ(&allAdmitees, generateAdmitee());
            printf("A new admitee has arrived at college.\n");
        }

    }
    printf("Removing Artifacts...\t");
    //sleep(1);
    printf("Exiting Game...\n");
    //sleep(1);
    return 0;
}