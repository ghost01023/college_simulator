#ifndef LIBRARY_H
#define LIBRARY_H

#include<stdio.h>
#include<stdlib.h>
#include <stdbool.h>
#include<string.h>

#define TOTAL_BOOKS 250
char *libBookTxt = "..\\databases\\library_books.txt";
char *borrowedBookTxt = "..\\databases\\borrowed_books.txt";

typedef struct bookStr {
    char name[50];
    char author[25];
    int pages;
} Book;


typedef struct {
    int count;
    Book bookStack[TOTAL_BOOKS];
} Library;

//Library MainLibNode;
char *libBooksTxt = "..\\databases\\library_books.txt";

void displayBook(Book b) {
    printf("%s | %s | %d\n", b.name, b.author, b.pages);
}

Library addBook(Library *Head, Book b) {
    if (Head->count != TOTAL_BOOKS) {
        Head->bookStack[Head->count++] = b;
    }
//    if (Head->count > 100) {
//
//    }
    return *Head;
}

Book generateBook() {
    Book temp;
    printf("Enter the title:\n");
    scanf("%s", temp.name);
    printf("Enter the Author:\n");
    scanf("%s", temp.author);
    printf("Enter the total pages:\n");
    scanf_s("%d", &temp.pages);
    displayBook(temp);
    return temp;
}

Book popBook(Library *HeadNode) {
    if (HeadNode->count != 0) {
        Book temp = HeadNode->bookStack[--HeadNode->count];
        return temp;
    } else {
        char name[50] = {'\0'};
        char author[25] = {'\0'};
        Book temp;
        strcpy(temp.author, author);
        strcpy(temp.name, name);
        temp.pages = 0;
        return temp;
    }
}


Library borrowBook(Library *mainNode, Library *borrowNode) {
    addBook(borrowNode, popBook(mainNode));
    return *borrowNode;
}

Library initBookNode(char *fileLoc) {
    Library MainLibNode;
    MainLibNode.count = 0;
    FILE *libBooksFile = fopen(fileLoc, "r");
    char bookInfo[100];
    while (fgets(bookInfo, 100, libBooksFile) != NULL) {
        char name[50];
        int infoIt = 0, i = 0;
        for (; bookInfo[infoIt] != ','; infoIt++) {
            name[i++] = bookInfo[infoIt];
        }
        name[i] = '\0';
        infoIt++;
        i = 0;
        char author[25];
        for (; bookInfo[infoIt] != ','; infoIt++) {
            author[i++] = bookInfo[infoIt];
        }
        author[i] = '\0';
        infoIt++;
        i = 0;
        char pages[5];
        for (; bookInfo[infoIt] != ';'; infoIt++) {
            pages[i++] = bookInfo[infoIt];
        }
        pages[i] = '\0';
        int page = atoi(pages);
        Book temp;
        strcpy(temp.author, author);
        strcpy(temp.name, name);
        temp.pages = page;
        addBook(&MainLibNode, temp);
    }
    return MainLibNode;
}


void writeToLibFile(Library libNode, char *loc) {
    FILE *libFile = fopen(loc, "w");
    char bookLine[250] = {'\0'};
    for (int i = 0; i < libNode.count; i++) {
        strcat(bookLine, libNode.bookStack[i].name);
        strcat(bookLine, ",");
        strcat(bookLine, libNode.bookStack[i].author);
        strcat(bookLine, ",");
        char pages[5];
        itoa(libNode.bookStack[i].pages, pages, 10);
        strcat(bookLine, pages);
        strcat(bookLine, ";\n");
        fputs(bookLine, libFile);
        bookLine[0] = '\0';
    }
    fclose(libFile);
}



void displayAllBooks(Library *Head) {
    for (int i = 0; i < Head->count; i++) {
        displayBook(Head->bookStack[i]);
    }
}

//void renderLibrary() {
//    FILE *libArtFile = fopen(lib_art, "r");
//    char line[1000] = {'\0'};
//    fgets(line, 1000, libArtFile);
//    printf("Line is: \n%s", line);
////    while(fgets(artLine, 1000, libArtFile) != NULL) {
////    }
//    fclose(libArtFile);
//}

#endif //LIBRARY_H