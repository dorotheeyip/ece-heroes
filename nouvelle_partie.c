#include "nouvelle_partie.h"
#include <stdio.h>

void lancer_nouvelle_partie(GameState *game) {
    game->vies = 1;
    game->niveau = 1;
    initialiser_niveau(game);
}

void initialiser_niveau(GameState *game) {

    game->progression = 0;

    if (game->niveau == 1) {
        game->coups_restants = 20;
        game->objectif_couleur = ROUGE;
        game->objectif_total = 10;
        game->temps_restants = 500; 
        printf("\nNIVEAU 1 : 10 ROUGE en 20 coups et 500 secondes\n");
    }
    else if (game->niveau == 2) {
        game->coups_restants = 20;
        game->objectif_couleur = BLEU;
        game->objectif_total = 20;
        game->temps_restants = 350; 
        printf("\nNIVEAU 2 : 20 BLEU en 20 coups et 350 secondes\n");
    }
    else if (game->niveau == 3) {
        game->coups_restants = 15;
        game->objectif_couleur = VERT;
        game->objectif_total = 20;
        game->temps_restants = 250; 
        printf("\nNIVEAU 3 : 20 VERT en 15 coups et 250 secondes\n");
    }
}

void action_destruction(GameState *game, int couleur) {
    if (game->coups_restants <= 0) return;

    game->coups_restants--;

    if (couleur == game->objectif_couleur)
        game->progression++;
}

void verifier_etat(GameState *game) {

    if (game->progression >= game->objectif_total) {
        if (game->niveau == 3) {
            printf("\nGAGNÉ \n");
        } else {
            printf("\nNiveau %d réussi\n", game->niveau);
            game->niveau++;
            initialiser_niveau(game);
        }
        return;
    }

    if (game->coups_restants == 0) {
        printf("\n ÉCHOUÉ \n");
        initialiser_niveau(game);
    }
}

