#include <stdio.h>
#include "etudiant.h"
#include "stockage.h"
#include "reutilisable.h"

void menuEleve(void) {
    int choix = -1;

    while (choix != 0) {
        nettoyerEcran();

        printf("==============================\n");
        printf("         MODE ETUDIANT        \n");
        printf("==============================\n");
        printf("1. Afficher les QCM\n");
        printf("2. Passer un QCM\n");
        printf("0. Retour\n");

        choix = demanderChoixMenu(0, 2);

        if (choix == 1) {
            afficherListeQCM();
        }
        if (choix == 2) {
            choisirQCM();
        }
    }
}

void choisirQCM(void) {
    int nbQCM;
    int choix;
    char nomQCM[TAILLE_NOM];
    QCM qcm;

    nbQCM = compterQCMDisponibles();

    if (nbQCM == 0) {
        printf("Aucun QCM disponible.\n");
        return;
    }

    afficherListeQCM();

    printf("Choisissez un QCM : ");
    choix = demanderChoixMenu(1, nbQCM);

    if (recupererNomQCM(choix, nomQCM) == 1) {
        if (chargerQCM(nomQCM, &qcm) == 1) {
            passerQCM(qcm);
        } else {
            printf("Erreur pendant le chargement du QCM.\n");
        }
    }
}

void passerQCM(QCM qcm) {
    int reponsesEleve[MAX_QUESTIONS][MAX_REPONSES];
    int i, j;
    float note;

    for (i = 0; i < MAX_QUESTIONS; i++) {
        for (j = 0; j < MAX_REPONSES; j++) {
            reponsesEleve[i][j] = 0;
        }
    }

    for (i = 0; i < qcm.nbQuestions; i++) {
        poserQuestion(qcm, i, reponsesEleve);
    }

    note = calculerNote(qcm, reponsesEleve);
    afficherResultat(note);
}

void poserQuestion(QCM qcm, int indiceQuestion, int reponsesEleve[MAX_QUESTIONS][MAX_REPONSES]) {
    int choix;
    int nbChoisis;
    Question question;

    question = qcm.questions[indiceQuestion];

    printf("\nQuestion %d :\n", indiceQuestion + 1);
    afficherQuestion(question);

    nbChoisis = 0;

    if (qcm.plusieursBonnesReponses == 1) {
        choix = -1;

        while (choix != 0) {
            printf("Choisissez une reponse, 0 pour finir : ");
            choix = demanderChoixMenu(0, question.nbReponses);

            if (choix != 0) {
                reponsesEleve[indiceQuestion][choix - 1] = 1;
                nbChoisis++;
            }

            if (choix == 0 && qcm.modeSequentiel == 1 && nbChoisis == 0) {
                printf("Vous devez choisir au moins une reponse.\n");
                choix = -1;
            }
        }
    } else {
        if (qcm.modeSequentiel == 1) {
            choix = demanderChoixMenu(1, question.nbReponses);
        } else {
            choix = demanderChoixMenu(0, question.nbReponses);
        }

        if (choix != 0) {
            reponsesEleve[indiceQuestion][choix - 1] = 1;
        }
    }
}

void afficherResultat(float note) {
    printf("\nVotre note est : %.2f / 20\n", note);
}
