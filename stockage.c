#include <stdio.h>
#include <string.h>
#include "stockage.h"

void enleverRetourLigne(char texte[]) {
    int i = 0;

    while (texte[i] != '\0') {
        if (texte[i] == '\n') {
            texte[i] = '\0';
        }
        i++;
    }
}

int sauvegarderQCM(QCM qcm) {
    FILE *fichier;
    char nomFichier[100];
    int i, j;

    strcpy(nomFichier, qcm.nom);
    strcat(nomFichier, ".txt");

    fichier = fopen(nomFichier, "w");

    if (fichier == NULL) {
        return 0;
    }

    fprintf(fichier, "%s\n", qcm.nom);
    fprintf(fichier, "%d\n", qcm.pointsNegatifs);
    fprintf(fichier, "%d\n", qcm.plusieursBonnesReponses);
    fprintf(fichier, "%d\n", qcm.modeSequentiel);
    fprintf(fichier, "%d\n", qcm.nbQuestions);

    for (i = 0; i < qcm.nbQuestions; i++) {
        fprintf(fichier, "%s\n", qcm.questions[i].enonce);
        fprintf(fichier, "%d\n", qcm.questions[i].nbReponses);

        for (j = 0; j < qcm.questions[i].nbReponses; j++) {
            fprintf(fichier, "%s\n", qcm.questions[i].reponses[j].texte);
            fprintf(fichier, "%d\n", qcm.questions[i].reponses[j].estCorrecte);
        }
    }

    fclose(fichier);
    return 1;
}

int chargerQCM(char nomFichier[], QCM *qcm) {
    FILE *fichier;
    char nomComplet[100];
    int i, j;

    strcpy(nomComplet, nomFichier);
    strcat(nomComplet, ".txt");

    fichier = fopen(nomComplet, "r");

    if (fichier == NULL) {
        return 0;
    }

    initialiserQCM(qcm);

    fgets(qcm->nom, TAILLE_NOM, fichier);
    enleverRetourLigne(qcm->nom);

    fscanf(fichier, "%d", &qcm->pointsNegatifs);
    fgetc(fichier);
    fscanf(fichier, "%d", &qcm->plusieursBonnesReponses);
    fgetc(fichier);
    fscanf(fichier, "%d", &qcm->modeSequentiel);
    fgetc(fichier);
    fscanf(fichier, "%d", &qcm->nbQuestions);
    fgetc(fichier);

    for (i = 0; i < qcm->nbQuestions; i++) {
        fgets(qcm->questions[i].enonce, TAILLE_TEXTE, fichier);
        enleverRetourLigne(qcm->questions[i].enonce);

        fscanf(fichier, "%d", &qcm->questions[i].nbReponses);
        fgetc(fichier);

        for (j = 0; j < qcm->questions[i].nbReponses; j++) {
            fgets(qcm->questions[i].reponses[j].texte, TAILLE_TEXTE, fichier);
            enleverRetourLigne(qcm->questions[i].reponses[j].texte);

            fscanf(fichier, "%d", &qcm->questions[i].reponses[j].estCorrecte);
            fgetc(fichier);
        }
    }

    fclose(fichier);
    return 1;
}

void ajouterQCMDansListe(char nomQCM[]) {
    FILE *fichier;

    fichier = fopen("liste_qcm.txt", "a");

    if (fichier != NULL) {
        fprintf(fichier, "%s\n", nomQCM);
        fclose(fichier);
    }
}

void afficherListeQCM(void) {
    FILE *fichier;
    char nom[TAILLE_NOM];
    int numero = 1;

    fichier = fopen("liste_qcm.txt", "r");

    if (fichier == NULL) {
        printf("Aucun QCM disponible.\n");
        return;
    }

    while (fgets(nom, TAILLE_NOM, fichier) != NULL) {
        enleverRetourLigne(nom);
        printf("%d. %s\n", numero, nom);
        numero++;
    }

    fclose(fichier);
}

int compterQCMDisponibles(void) {
    FILE *fichier;
    char nom[TAILLE_NOM];
    int compteur = 0;

    fichier = fopen("liste_qcm.txt", "r");

    if (fichier == NULL) {
        return 0;
    }

    while (fgets(nom, TAILLE_NOM, fichier) != NULL) {
        compteur++;
    }

    fclose(fichier);
    return compteur;
}

int recupererNomQCM(int numero, char nomQCM[]) {
    FILE *fichier;
    char nom[TAILLE_NOM];
    int compteur = 1;

    fichier = fopen("liste_qcm.txt", "r");

    if (fichier == NULL) {
        return 0;
    }

    while (fgets(nom, TAILLE_NOM, fichier) != NULL) {
        enleverRetourLigne(nom);

        if (compteur == numero) {
            strcpy(nomQCM, nom);
            fclose(fichier);
            return 1;
        }

        compteur++;
    }

    fclose(fichier);
    return 0;
}
