#include <stdio.h>
#include <string.h>
#include "stockage.h"

/*
    Cette fonction sert surtout après un fgets.
    Quand on lit une phrase dans un fichier, fgets garde souvent le '\n',
    donc on le retire pour éviter les problèmes dans les noms de QCM ou les réponses.
*/
void nettoyerLigne(char texte[]) {
    int i = 0;

    while (texte[i] != '\0') {
        if (texte[i] == '\n') {
            texte[i] = '\0';
        }
        i++;
    }
}
/*
    Enregistre dans un fichier le questionnaire Teiken préparé par l'enseignant.
    Le fichier porte le nom du QCM avec l'extension .txt.
*/
int enregistrerQCM(QCM qcm) {
    FILE *fichier;
    char nomFichier[100];
    int i, j;

    strcpy(nomFichier, qcm.nom);
    strcat(nomFichier, ".txt");

    fichier = fopen(nomFichier, "w");

    if (fichier == NULL) {
        return 0;
    }
    // Informations générales du questionnaire
    fprintf(fichier, "%s\n", qcm.nom);
    fprintf(fichier, "%d\n", qcm.pointsNegatifs);
    fprintf(fichier, "%d\n", qcm.plusieursBonnesReponses);
    fprintf(fichier, "%d\n", qcm.modeSequentiel);
    fprintf(fichier, "%d\n", qcm.nbQuestions);

    // Questions du Teiken et réponses possibles
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
/*
    Recharge un questionnaire déjà créé.
    On récupère les options du QCM puis toutes les questions avec leurs réponses.
*/
int lireQCM(char nomFichier[], QCM *qcm) {
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

    // Nom du questionnaire
    if (fgets(qcm->nom, TAILLE_NOM, fichier) == NULL) {
        fclose(fichier);
        return 0;
    }
    nettoyerLigne(qcm->nom);

    // Options choisies pour ce QCM
    if (fscanf(fichier, "%d", &qcm->pointsNegatifs) != 1) {
        fclose(fichier);
        return 0;
    }
    fgetc(fichier);

    if (fscanf(fichier, "%d", &qcm->plusieursBonnesReponses) != 1) {
        fclose(fichier);
        return 0;
    }
    fgetc(fichier);

    if (fscanf(fichier, "%d", &qcm->modeSequentiel) != 1) {
        fclose(fichier);
        return 0;
    }
    fgetc(fichier);

    if (fscanf(fichier, "%d", &qcm->nbQuestions) != 1) {
        fclose(fichier);
        return 0;
    }
    fgetc(fichier);

    if (qcm->nbQuestions < 0) {
        fclose(fichier);
        return 0;
    }

    // Lecture des questions du questionnaire
    for (i = 0; i < qcm->nbQuestions; i++) {
        if (fgets(qcm->questions[i].enonce, TAILLE_TEXTE, fichier) == NULL) {
            fclose(fichier);
            return 0;
        }
        nettoyerLigne(qcm->questions[i].enonce);

        if (fscanf(fichier, "%d", &qcm->questions[i].nbReponses) != 1) {
            fclose(fichier);
            return 0;
        }
        fgetc(fichier);

        if (qcm->questions[i].nbReponses < 0) {
            fclose(fichier);
            return 0;
        }

        // Lecture des réponses liées à la question
        for (j = 0; j < qcm->questions[i].nbReponses; j++) {
            if (fgets(qcm->questions[i].reponses[j].texte, TAILLE_TEXTE, fichier) == NULL) {
                fclose(fichier);
                return 0;
            }
            nettoyerLigne(qcm->questions[i].reponses[j].texte);

            if (fscanf(fichier, "%d", &qcm->questions[i].reponses[j].estCorrecte) != 1) {
                fclose(fichier);
                return 0;
            }
            fgetc(fichier);
        }
    }

    fclose(fichier);
    return 1;
}

/*
    Ajoute le nom du QCM dans liste_qcm.txt.
    Ce fichier sert de petit index pour retrouver les questionnaires déjà créés.
*/
void ajouterDansListe(char nomQCM[]) {
    FILE *fichier;

    fichier = fopen("liste_qcm.txt", "a");

    if (fichier != NULL) {
        fprintf(fichier, "%s\n", nomQCM);
        fclose(fichier);
    }
}

/*
    Affiche les QCM enregistrés pour que l'utilisateur puisse choisir
    lequel lancer ou modifier.
*/
void voirListeQCM(void) {
    FILE *fichier;
    char nom[TAILLE_NOM];
    int numero = 1;

    fichier = fopen("liste_qcm.txt", "r");

    if (fichier == NULL) {
        printf("Aucun QCM disponible.\n");
        return;
    }

    while (fgets(nom, TAILLE_NOM, fichier) != NULL) {
        nettoyerLigne(nom);
        printf("%d. %s\n", numero, nom);
        numero++;
    }

    fclose(fichier);
}

/*
    Compte le nombre de questionnaires déjà enregistrés.
    Utile pour vérifier qu'un choix de l'utilisateur est possible.
*/
int nbQCM(void) {
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
/*
    À partir du numéro choisi dans la liste, on récupère le vrai nom du QCM.
    Ce nom servira ensuite à ouvrir le bon fichier .txt.
*/
int chercherNomQCM(int numero, char nomQCM[]) {
    FILE *fichier;
    char nom[TAILLE_NOM];
    int compteur = 1;

    fichier = fopen("liste_qcm.txt", "r");

    if (fichier == NULL) {
        return 0;
    }
    while (fgets(nom, TAILLE_NOM, fichier) != NULL) {
        nettoyerLigne(nom);

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
