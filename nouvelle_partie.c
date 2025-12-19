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

void jouer_niveau(int num_niveau, GameState *game);

void lancer_nouvelle_partie(GameState *game) {
    game->vies = 3; // 3 vies par partie
    game->niveau = 1;
    game->niveau_max_debloque = 1;   // au début, seul le niveau 1 est débloqué
    initialiser_niveau(game);
}

void initialiser_niveau(GameState *game) {
    // Réinitialisation complète du niveau
    game->coups_restants = 30;
    game->temps_restants = 60.0f;

    for (int i = 1; i <= 5; i++) {
        game->objectif_items[i] = 0;
        game->progression_items[i] = 0; // Remettre la progression à zéro
    }

    switch (game->niveau) {
            case 1:
                game->objectif_items[1] = 4; 
                game->objectif_items[3] = 4;
                break;
            case 2:
                game->objectif_items[2] = 30;
                game->objectif_items[4] = 25;
                break;
            case 3:
                game->objectif_items[1] = 10;
                game->objectif_items[5] = 15;
                break;
    }

    // Remplir le plateau aléatoirement
    for (int i = 0; i < LINE; i++) {
        for (int j = 0; j < COLUMN; j++) {
            game->plateau[i][j] = 1 + rand() % 5;
        }
    }

    // Réinitialiser la progression initiale sur le plateau
    int marque[LINE][COLUMN] = {0};
    int compteur_item[6] = {0};
    int continuer = 1;

    // Supprimer toutes combinaisons automatiques dès le début
    while (continuer) {
        continuer = 0;

        for(int i=0;i<LINE;i++)
            for(int j=0;j<COLUMN;j++)
                marque[i][j]=0;

        if (combinaison_ligne_6(game->plateau, marque) ||
            combinaison_colonne_6(game->plateau, marque) ||
            combinaison_croix(game->plateau, marque) ||
            combinaison_carre(game->plateau, marque) ||
            combinaison_ligne_4(game->plateau, marque) ||
            combinaison_colonne_4(game->plateau, marque)) {

            continuer = 1;
            supprim_combin(game->plateau, marque, compteur_item);
            renouvellement_case(game->plateau);

            // // Mettre à jour la progression
            // for (int k = 1; k <= 5; k++) {
            //     game->progression_items[k] += compteur_item[k];
            //     compteur_item[k] = 0;
            // }
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
    printf("Vies restantes : %d\n", game->vies);

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

// Affiche les niveaux et leur statut
void afficher_ecran_niveaux(GameState *game) {
    clrscr();
    printf("===== Niveaux =====\n");

    for (int i = 1; i <= MAX_NIVEAUX; i++) {
        if (i < game->niveau_max_debloque) {
            printf("Niveau %d : REUSSI\n", i);
        } else if (i == game->niveau_max_debloque) {
            printf("Niveau %d : DEBLOQUE\n", i);
        } else {
            printf("Niveau %d : BLOQUE\n", i);
        }
    }

    printf("\n");
}

// Affiche le menu niveau après échec ou succès
// Retourne :
// 1 = rejouer niveau
// 2 = passer au niveau suivant
// 0 = retour menu principal
int menu_niveau_options(GameState *game) {
    int choix;
    int niveau_suivant_disponible = (game->niveau < game->niveau_max_debloque);

    while (1) {
        clrscr();
        afficher_ecran_niveaux(game);

        printf("\n===== Options Niveau %d =====\n", game->niveau);
        printf("1 - Rejouer le niveau\n");

        if (niveau_suivant_disponible) {
            printf("2 - Passer au niveau suivant\n");
        } else {
            printf("2 - [Passer au niveau suivant] (verrouillé)\n");
        }

        printf("0 - Revenir au menu principal\n");
        printf("Votre choix : ");
        scanf("%d", &choix);

        if (choix == 1) {
            return 1; // rejouer niveau
        }

        if (choix == 2) {
            if (niveau_suivant_disponible) {
                return 2; // passer au niveau suivant
            } else {
                printf("\n Niveau non débloqué !\n");
                Sleep(1500);
                continue; // on reste dans le menu
            }
        }

        if (choix == 0) {
            return 0; // retour menu principal
        }

        // Choix invalide
        printf("\nChoix invalide.\n");
        Sleep(1000);
    }
}


// Retourne 0 si la partie est terminée (toutes vies perdues), 1 sinon
int gerer_echec_niveau(GameState *game, const char *raison) {
    clrscr();
    printf("%s Niveau échoué.\n", raison);
    Sleep(1500);

    game->vies--;  // Décrémenter les vies

    if (game->vies <= 0) {
        clrscr();
        printf("\nToutes les vies sont perdues ! Partie terminée.\n");
        Sleep(2000);
        return 0;  // partie terminée
    }

    // Sinon, montrer le menu des niveaux
    afficher_ecran_niveaux(game);
    return 1; // niveau perdu mais partie continue
}

