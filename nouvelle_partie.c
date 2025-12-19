#include "nouvelle_partie.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "moteur_de_jeu.h"
#ifdef _WIN32
    #include "affichage_console.h"
#else
    #include "affichage_console_mac.h"
#endif

void lancer_nouvelle_partie(GameState *game) {
    game->vies = 1;
    game->niveau = 1;
    initialiser_niveau(game);
}

void initialiser_niveau(GameState *game) {

    game->coups_restants = 30;
    game->temps_restants = 60.0f;

    for (int i = 1; i <= 5; i++) {
        game->objectif_items[i] = 0;
        game->progression_items[i] = 0;
    }

    if (game->niveau == 1) {
        game->objectif_items[1] = 5; 
        game->objectif_items[2] = 5; 
        game->objectif_items[3] = 5; 
    }

    else if (game->niveau == 2) {
        game->objectif_items[2] = 30;
        game->objectif_items[4] = 25;
    }

    for (int i = 0; i < LINE; i++) {
        for (int j = 0; j < COLUMN; j++) {
            game->plateau[i][j] = 1 + rand() % 5;
        }
    }
}

int contrat_rempli(GameState *game) {
    for (int i = 1; i <= 5; i++) {
        if (game->progression_items[i] < game->objectif_items[i])
            return 0;
    }
    return 1;
}

void afficher_objectifs(GameState *game) {
    gotoxy(0, LINE + 6);
    printf("OBJECTIFS :\n");

    for (int i = 1; i <= 5; i++) {
        if (game->objectif_items[i] > 0) {
            printf(" - Item %d : %d / %d\n",
                   i,
                   game->progression_items[i],
                   game->objectif_items[i]);
        }
    }

    printf("Coups restants : %d\n", game->coups_restants);
    printf("Temps restant  : %.1f s\n", game->temps_restants);
}

int maj_temps(GameState *game) {
    static time_t dernier_temps = 0;
    time_t maintenant = time(NULL);

    if (dernier_temps == 0)
        dernier_temps = maintenant;

    if (maintenant != dernier_temps) {
        game->temps_restants--;
        dernier_temps = maintenant;

        if (game->temps_restants <= 0)
            return 1; // temps écoulé
    }

    return 0; // temps OK
}

void pause_avec_temps(GameState *game, int duree_ms) {
    int pas = 50;
    int iterations = duree_ms / pas;

    for (int i = 0; i < iterations; i++) {
        maj_temps(game);
        afficher_objectifs(game);
        Sleep(pas);
    }
}

// void initialiser_niveau(GameState *game) {

//     game->progression = 0;

//     if (game->niveau == 1) {
//         game->coups_restants = 20;
//         game->objectif_type = 1;
//         game->temps_restants = 500; 
//         printf("\nNIVEAU 1 : 10 ROUGE en 20 coups et 500 secondes\n");
//     }
//     else if (game->niveau == 2) {
//         game->coups_restants = 20;
//         game->objectif_type = 4;
//         game->temps_restants = 350; 
//         printf("\nNIVEAU 2 : 20 BLEU en 20 coups et 350 secondes\n");
//     }
//     else if (game->niveau == 3) {
//         game->coups_restants = 15;
//         game->objectif_type = 2;
//         game->temps_restants = 250; 
//         printf("\nNIVEAU 3 : 20 VERT en 15 coups et 250 secondes\n");
//     }
// }

// void action_destruction(GameState *game, int couleur) {
//     if (game->coups_restants <= 0) return;

//     game->coups_restants--;

//     if (couleur == game->objectif_couleur)
//         game->progression++;
// }

// void verifier_etat(GameState *game) {

//     if (game->progression >= game->objectif_total) {
//         if (game->niveau == 3) {
//             printf("\nGAGNÉ \n");
//         } else {
//             printf("\nNiveau %d réussi\n", game->niveau);
//             game->niveau++;
//             initialiser_niveau(game);
//         }
//         return;
//     }

//     if (game->coups_restants == 0) {
//         printf("\n ÉCHOUÉ \n");
//         initialiser_niveau(game);
//     }
// }

