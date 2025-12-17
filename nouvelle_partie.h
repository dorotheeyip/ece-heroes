#ifndef NOUVELLE_PARTIE_H
#define NOUVELLE_PARTIE_H

#define ROUGE 1
#define BLEU  2
#define VERT  3

typedef struct {
    char pseudo[50];

    int niveau;
    int vies;
    int coups_restants;

    int objectif_couleur;
    int objectif_total;
    float temps_restants;
    int progression;
} GameState;

/* Logique de jeu */
void lancer_nouvelle_partie(GameState *game);
void initialiser_niveau(GameState *game);
void action_destruction(GameState *game, int couleur);
void verifier_etat(GameState *game);

#endif
