#include <stdio.h>
#include <string.h>
#include "qcm.h"

void initialiserQCM(QCM *qcm) {
    int i;
    int j;

    strcpy(qcm->nom, "");
    qcm->pointsNegatifs = 0;
    qcm->plusieursBonnesReponses = 0;
    qcm->modeSequentiel = 0;
    qcm->nbQuestions = 0;

    for (i = 0; i < MAX_QUESTIONS; i++) {
        strcpy(qcm->questions[i].enonce, "");
        qcm->questions[i].nbReponses = 0;

        for (j = 0; j < MAX_REPONSES; j++) {
            strcpy(qcm->questions[i].reponses[j].texte, "");
            qcm->questions[i].reponses[j].estCorrecte = 0;
        }
    }
}

void afficherQCM(QCM qcm) {
    printf("Nom du QCM : %s\n", qcm.nom);
    printf("Nombre de questions : %d\n", qcm.nbQuestions);

    printf("Points negatifs : ");
    if (qcm.pointsNegatifs == 1) {
        printf("oui\n");
    } else {
        printf("non\n");
    }

    printf("Plusieurs bonnes reponses : ");
    if (qcm.plusieursBonnesReponses == 1) {
        printf("oui\n");
    } else {
        printf("non\n");
    }
  
    printf("Mode sequentiel : ");
    if (qcm.modeSequentiel == 1) {
        printf("oui\n");
    } else {
        printf("non\n");
    }
}

void afficherQuestion(Question question) {
    int i;
    printf("%s\n", question.enonce);

    for (i = 0; i < question.nbReponses; i++) {
        printf("%d. %s\n", i + 1, question.reponses[i].texte);
    }
}

int verifierReponse(Question question, int reponsesEleve[]) {
    int i;

    for (i = 0; i < question.nbReponses; i++) {
        if (reponsesEleve[i] != question.reponses[i].estCorrecte) {
            return 0;
        }
    }
    return 1;
}

float calculerNote(QCM qcm, int reponsesEleve[MAX_QUESTIONS][MAX_REPONSES]) {
    int i;
    float note;
    float pointsParQuestion;
    note = 0;

    if (qcm.nbQuestions == 0) {
        return 0;
    }

    pointsParQuestion = 20.0 / qcm.nbQuestions;

    for (i = 0; i < qcm.nbQuestions; i++) {
        if (verifierReponse(qcm.questions[i], reponsesEleve[i]) == 1) {
            note = note + pointsParQuestion;
        } else {
            if (qcm.pointsNegatifs == 1) {
                note = note - pointsParQuestion / 2;
            }
        }
    }
    if (note < 0) {
        note = 0;
    }
    return note;
}
