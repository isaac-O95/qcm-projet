#include <stdio.h>
#include "reutilisable.h"

void ViderBuffer(void){
  int c;
do {
    c = getchar();
} while(c != '\n');
}

int lireEntier(void){
    int nombre;
    scanf('%d', &nombre);
    ViderBuffer();
 return nombre;
}

void lireTexte(char texte[], int taille){
  fgets(texte, taille, stdin);
      int i=0;
      while(texte[i] != '\0'){
        if(texte[i] == '\n'){
          texte[i] = '\0';
        }
        i++;
      }
}

int demanderOuiNon(char message[]) {
    int choix;

    choix = -1;

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

    for (i = 0; i < 30; i++) {
        printf("\n");
    }
}

int demanderChoixMenu(int min, int max) {
    int choix;

    choix = min - 1;

    while (choix < min || choix > max) {
        printf("Votre choix : ");
        choix = lireEntier();

        if (choix < min || choix > max) {
            printf("Choix invalide, recommencez.\n");
        }
    }

    return choix;
}
