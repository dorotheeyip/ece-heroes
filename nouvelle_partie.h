#include "moteur_de_jeu.h"
#ifndef NOUVELLE_PARTIE_H
#define NOUVELLE_PARTIE_H

#define MAX_NIVEAUX 5  // Nombre total de niveaux du jeu

typedef struct {
    char pseudo[50];
    
    int niveau;             // niveau en cours
    int niveau_max_debloque; // dernier niveau débloqué
    int vies;
    int coups_restants;

    int objectif_items[5+1];
    float temps_restants;
    int progression_items[5+1];
    int inventaire[4]; // pour les objets spéciaux
    int inventaire_max[4];
    int plateau[LINE][COLUMN];
} GameState;

/* Logique de jeu */
void lancer_nouvelle_partie(GameState *game);
void initialiser_niveau(GameState *game);
int contrat_rempli(GameState *game);
void afficher_objectifs(GameState *game);
int maj_temps(GameState *game);
void pause_avec_temps(GameState *game, int duree_ms);
int gerer_echec_niveau(GameState *game, const char *raison);
void afficher_ecran_niveaux(GameState *game);
int menu_niveau_options(GameState *game);

#endif
