#ifndef ENSEIGNANT_H
#define ENSEIGNANT_H

#include "qcm.h"

int verifierMotDePasse(void);
void menuEnseignant(void);
void creerQCM(void);
void saisirParametresQCM(QCM *qcm);
void ajouterQuestion(QCM *qcm);
void modifierQCM(void);
void supprimerQCM(void);
void afficherListeQCMEnseignant(void);

#endif
