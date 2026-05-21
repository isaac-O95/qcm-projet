#include <stdio.h>
#include "enseignant.h"
#include "etudiant.h"
#include "reutilisable.h"

void menuPrincipal(void);

int main(void) {
    menuPrincipal();

    return 0;
}

void menuPrincipal(void){
    int choix;
    choix = -1;

while(choix != 0){
    nettoyerEcran();

    printf("===========================\n");
    printf("      MENU PRINCIPAL       \n");
    printf("===========================\n");
    printf("1. Mode Enseignant\n");
    printf("2. Mode etudiant\n");
    printf("0. Quitter\n");
    printf("==============================\n");

  choix = DemanderChoixMenu(0,2);
    if(choix == 1){
        menuEnseignant();
    }
    if(choix == 2){
        menuEtuduiant();
    }
}
  printf("fin du programme.\n" )
}
