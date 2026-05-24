#ifndef STOCKAGE_H
#define STOCKAGE_H
#include "qcm.h"

void nettoyerLigne(char texte[]);
int enregistrerQCM(QCM qcm);
int lireQCM(char nomFichier[], QCM *qcm);
void ajouterDansListe(char nomQCM[]);
void voirListeQCM(void);
int nbQCM(void);
int chercherNomQCM(int numero, char nomQCM[]);

#endif
