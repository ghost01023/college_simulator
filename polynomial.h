//
// Created by Rosja Dostoyevsjky on 1/30/2024.
//
#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include<stdio.h>
#include<stdlib.h>
#include <stdbool.h>
#include<string.h>

typedef struct polyTerm {
    int coeff, exp;
    struct polyTerm *next;
} Term;

bool isEmpty(Term *Head) {
    return Head->next == NULL;
}

Term *detachTerm(Term *Head) {
    Term *first = Head->next;
    if (isEmpty(Head)) {
        return Head;
    } else {
        Head->next = first->next;
        return Head;
    }
}

Term *attachTerm(Term *Head, Term temp) {
    Term *tempTerm = (Term *) malloc(sizeof(Term));
    tempTerm->exp = temp.exp;
    tempTerm->coeff = temp.coeff;
    tempTerm->next = NULL;
    if (Head == NULL) {
        return tempTerm;
    }
    Term *curr = Head;
    while (curr->next != NULL) {
        curr = curr->next;
    }
    curr->next = tempTerm;
//    free(tempTerm);
    return Head;
}

void displayTerm(Term *Head) {
    Term *curr = Head->next;
    while (curr != NULL) {
        printf("%d", curr->coeff);
        if (curr->exp == 0) {
            break;
        }
        printf("x^%d ", curr->exp);
        if (curr->next != NULL) {
            printf("+ ");
        }
        curr = curr->next;
    }
}

Term createPol(char polynomial[100]) {
    Term *polyTerm = (Term *) malloc(sizeof(Term));
    polyTerm->next = NULL;
    for (int i = 0; i < strlen(polynomial); i++) {
        char coeff[10], exp[5];
        int coeIt = 0, expIt = 0;
        while (polynomial[i] != 'x') {
            if (polynomial[i] == '\0') {
                break;
            }
            coeff[coeIt++] = polynomial[i++];
        }
        coeff[coeIt] = '\0';
        i += 2;
        while ((polynomial[i] != '+') && (polynomial[i] != '\0')) {
            exp[expIt++] = polynomial[i++];
        }
        exp[expIt] = '\0';
        Term temp;
        temp.coeff = atoi(coeff);
        temp.exp = atoi(exp);
        temp.next = NULL;
        polyTerm = attachTerm(polyTerm, temp);
    }
    return *polyTerm;
}

Term addPolynomial(Term *aRoot, Term *bRoot) {
    Term *polyAnswer = (Term *) malloc(sizeof(Term));
    polyAnswer->next = NULL;
    while (!isEmpty(aRoot) && !isEmpty(bRoot)) {
        Term temp;
        temp.next = NULL;
        int aC = aRoot->next->coeff, aE = aRoot->next->exp;
        int bC = bRoot->next->coeff, bE = bRoot->next->exp;
        if (aE == bE) {
            temp.coeff = aC + bC;
            temp.exp = aE;
            aRoot = detachTerm(aRoot);
            bRoot = detachTerm(bRoot);
        } else if (aE > bE) {
            temp.coeff = aC;
            temp.exp = aE;
            aRoot = detachTerm(aRoot);
        } else {
            temp.coeff = bC;
            temp.exp = bE;
            bRoot = detachTerm(bRoot);
        }
        polyAnswer = attachTerm(polyAnswer, temp);
    }
    while (!isEmpty(aRoot)) {
        Term temp = {aRoot->next->coeff, aRoot->next->exp, NULL};
        aRoot = detachTerm(aRoot);
        polyAnswer = attachTerm(polyAnswer, temp);
    }
    while (!isEmpty(bRoot)) {
        Term temp = {bRoot->next->coeff, bRoot->next->exp, NULL};
        bRoot = detachTerm(bRoot);
        polyAnswer = attachTerm(polyAnswer, temp);
    }
    return *polyAnswer;
}

bool comparePolynomials(Term *a, Term *b) {
    bool flag = true;
    while(a->next != NULL || b->next != NULL) {
        a = a->next;
        b = b->next;
        if((a->coeff != b->coeff) || (a->exp != b->exp)) {
            flag = false;
            break;
        }
    }
    if(a->next != NULL && b->next != NULL) {
        flag = false;
    }
    return flag;
}

bool askPolyQuestion() {
    char polA[100], polB[100];
    printf("\nEnter Polynomial A: \n");
    scanf("%s", polA);
    Term polyA = createPol(polA);
    displayTerm(&polyA);
    printf("\nEnter Polynomial B: \n");
    scanf("%s", polB);
    Term polyB = createPol(polB);
    displayTerm(&polyB);
    Term polyC = addPolynomial(&polyA, &polyB);
    printf("\nEnter your answer: \n");
    char userAns[100];
    scanf("%s", userAns);
    printf("\nAnswer after Addition Was:\n");
    Term userAnsPoly = createPol(userAns);
    displayTerm(&polyC);
    bool correct = comparePolynomials(&polyC, &userAnsPoly);
    if (correct) {
        printf("Your answer was correct!");
    }
    return correct;
}

Term generatePolynomial() {
    //number of terms
    printf("Inside");
    srand(time(NULL));
    int numTerms = (rand() % 5) + 1;
    Term temp;
    int topExp = (rand() % 20);
    while(numTerms > 0) {
        int randcoeff = rand() % 100;
        Term att = {randcoeff, topExp};
        topExp = rand() % topExp;
        numTerms--;
        printf("OK");
        attachTerm(&temp, att);
    }
    displayTerm(&temp);
    return temp;
}

#endif //POLYNOMIAL_H
