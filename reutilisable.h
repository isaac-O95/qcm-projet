#ifndef REUTILISABLE_H
#define REUTILISABLE_H

void viderBuffer(void);
int lireEntier(void);
void lireTexte(char texte[], int taille);
int demanderOuiNon(char message[]);
void nettoyerEcran(void);
int demanderChoixMenu(int min, int max);

#endif
