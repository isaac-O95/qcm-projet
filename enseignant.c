#include <stdio.h>
#include <string.h>
#include "enseignant.h"
#include "stockage.h"
#include "reutilisable.h"

#define MOT_DE_PASSE "anakin"

int verifierMotDePasse(void) {
    char motDePasse[50];

    printf("Mot de passe enseignant : ");
    lireTexte(motDePasse, 50);

    if (strcmp(motDePasse, MOT_DE_PASSE) == 0) {
        return 1;
    }

    printf("Mot de passe incorrect.\n");
    return 0;
}

void menuEnseignant(void) {
    int choix = -1;

    if (verifierMotDePasse() == 0) {
        return;
    }

    while (choix != 0) {
        nettoyerEcran();

        printf("==============================\n");
        printf("        MODE ENSEIGNANT       \n");
        printf("==============================\n");
        printf("1. Creer un QCM\n");
        printf("2. Afficher les QCM\n");
        printf("3. Modifier un QCM\n");
        printf("4. Supprimer un QCM\n");
        printf("0. Retour\n");

        choix = demanderChoixMenu(0, 4);

        if (choix == 1) {
            creerQCM();
        }
        if (choix == 2) {
            afficherListeQCMEnseignant();
        }
        if (choix == 3) {
            modifierQCM();
        }
        if (choix == 4) {
            supprimerQCM();
        }
    }
}

void creerQCM(void) {
    QCM qcm;
    int continuer = 1;

    initialiserQCM(&qcm);

    printf("Nom du QCM : ");
    lireTexte(qcm.nom, TAILLE_NOM);

    saisirParametresQCM(&qcm);

    while (continuer == 1 && qcm.nbQuestions < MAX_QUESTIONS) {
        ajouterQuestion(&qcm);

        if (qcm.nbQuestions < MAX_QUESTIONS) {
            continuer = demanderOuiNon("Ajouter une autre question");
        }
    }

    if (sauvegarderQCM(qcm) == 1) {
        ajouterQCMDansListe(qcm.nom);
        printf("QCM sauvegarde.\n");
    } else {
        printf("Erreur pendant la sauvegarde.\n");
    }
}

void saisirParametresQCM(QCM *qcm) {
    qcm->pointsNegatifs = demanderOuiNon("Activer les points negatifs");
    qcm->plusieursBonnesReponses = demanderOuiNon("Autoriser plusieurs bonnes reponses");
    qcm->modeSequentiel = demanderOuiNon("Obliger a repondre a chaque question");
}

void ajouterQuestion(QCM *qcm) {
    int i;
    int indice;
    int bonneReponse;
    int nbReponses;

    indice = qcm->nbQuestions;

    printf("Enonce de la question : ");
    lireTexte(qcm->questions[indice].enonce, TAILLE_TEXTE);

    nbReponses = 0;

    while (nbReponses < 2 || nbReponses > MAX_REPONSES) {
        printf("Nombre de reponses possibles entre 2 et %d : ", MAX_REPONSES);
        nbReponses = lireEntier();
    }

    qcm->questions[indice].nbReponses = nbReponses;

    for (i = 0; i < nbReponses; i++) {
        printf("Reponse %d : ", i + 1);
        lireTexte(qcm->questions[indice].reponses[i].texte, TAILLE_TEXTE);
        qcm->questions[indice].reponses[i].estCorrecte = 0;
    }

    if (qcm->plusieursBonnesReponses == 1) {
        for (i = 0; i < nbReponses; i++) {
            qcm->questions[indice].reponses[i].estCorrecte =
                demanderOuiNon("Cette reponse est correcte");
        }
    } else {
        printf("Numero de la bonne reponse : ");
        bonneReponse = demanderChoixMenu(1, nbReponses);
        qcm->questions[indice].reponses[bonneReponse - 1].estCorrecte = 1;
    }

    qcm->nbQuestions++;
}

void modifierQCM(void) {
    printf("Modification non disponible pour le moment.\n");
}

void supprimerQCM(void) {
    printf("Suppression non disponible pour le moment.\n");
}

void afficherListeQCMEnseignant(void) {
    afficherListeQCM();
}
