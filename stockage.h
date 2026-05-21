#ifndef STOCKAGE_H
#define STOCKAGE_H

#include "qcm.h"

int sauvegarderQCM(QCM qcm);
int chargerQCM(char nomFichier[], QCM *qcm);
void ajouterQCMDansListe(char nomQCM[]);
void afficherListeQCM(void);
int compterQCMDisponibles(void);
int recupererNomQCM(int numero, char nomQCM[]);

#endif
