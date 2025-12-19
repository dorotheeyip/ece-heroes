#include "moteur_de_jeu.h"
#ifndef NOUVELLE_PARTIE_H
#define NOUVELLE_PARTIE_H

// #define ROUGE 1
// #define BLEU  2
// #define VERT  3

typedef struct {
    char pseudo[50];

    int niveau;
    int vies;
    int coups_restants;

    int objectif_items[5+1];
    float temps_restants;
    int progression_items[5+1];
    int plateau[LINE][COLUMN];
} GameState;

/* Logique de jeu */
void lancer_nouvelle_partie(GameState *game);
void initialiser_niveau(GameState *game);
// void action_destruction(GameState *game, int couleur);
// void verifier_etat(GameState *game);
int contrat_rempli(GameState *game);
void afficher_objectifs(GameState *game);
int maj_temps(GameState *game);
void pause_avec_temps(GameState *game, int duree_ms);

#endif
