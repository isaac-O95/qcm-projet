#include <stdio.h>
#include "reutilisable.h"

void ViderBuffer(void) {
    int c;

    do {
        c = getchar();
    } while (c != '\n');
}

int lireEntier(void) {
    int nombre;

    scanf("%d", &nombre);   // %d doit être entre guillemets doubles
    ViderBuffer();

    return nombre;
}

void lireTexte(char texte[], int taille) {
    int i = 0;

    fgets(texte, taille, stdin);

    // On enlève le retour à la ligne ajouté par fgets
    while (texte[i] != '\0') {
        if (texte[i] == '\n') {
            texte[i] = '\0';
        }
        i++;
    }
}

int demanderOuiNon(char message[]) {
    int choix;

    choix = -1;

    // On attend seulement 0 ou 1
    while (choix != 0 && choix != 1) {
        printf("%s (1 = oui, 0 = non) : ", message);
        choix = lireEntier();

        if (choix != 0 && choix != 1) {
            printf("Reponse invalide.\n");
        }
    }

    return choix;
}

void nettoyerEcran(void) {
    int i;

    // On saute plusieurs lignes pour séparer les menus
    for (i = 0; i < 30; i++) {
        printf("\n");
    }
}

int demanderChoixMenu(int min, int max) {
    int choix;

    choix = min - 1;

    // On redemande tant que le choix n'est pas dans l'intervalle
    while (choix < min || choix > max) {
        printf("Votre choix : ");
        choix = lireEntier();

        if (choix < min || choix > max) {
            printf("Choix invalide, recommencez.\n");
        }
    }

    return choix;
}
