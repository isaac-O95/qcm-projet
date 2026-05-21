#ifndef QCM_H
#define QCM_H

#define MAX_QUESTIONS 50
#define MAX_REPONSES 6
#define TAILLE_TEXTE 256
#define TAILLE_NOM 64

typedef struct {
    char texte[TAILLE_TEXTE];
    int estCorrecte;
} Reponse;

typedef struct {
    char enonce[TAILLE_TEXTE];
    int nbReponses;
    Reponse reponses[MAX_REPONSES];
} Question;

typedef struct {
    char nom[TAILLE_NOM];
    int pointsNegatifs;
    int plusieursBonnesReponses;
    int modeSequentiel;
    int nbQuestions;
    Question questions[MAX_QUESTIONS];
} QCM;

void initialiserQCM(QCM *qcm);
void afficherQCM(QCM qcm);
void afficherQuestion(Question question);
int verifierReponse(Question question, int reponsesEleve[]);
float calculerNote(QCM qcm, int reponsesEleve[MAX_QUESTIONS][MAX_REPONSES]);

#endif
