#ifndef ETUDIANT_H
#define ETUDIANT_H

#include "qcm.h"

void menuEleve(void);
int choisirQCM(void);
void passerQCM(QCM qcm);
void poserQuestion(QCM qcm, int indiceQuestion, int reponsesEleve[MAX_QUESTIONS][MAX_REPONSES]);
void afficherResultat(float note);

#endif
