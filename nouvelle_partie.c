#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "moteur_de_jeu.h"
#include "extensions.h"
#ifdef _WIN32
    #include "affichage_console.h"
#else
    #include "affichage_console_mac.h"
#endif
#include "nouvelle_partie.h"

void jouer_niveau(int num_niveau, GameState *game);

void lancer_nouvelle_partie(GameState *game) {
    game->vies = 3; // 3 vies par partie
    game->niveau = 1;
    game->niveau_max_debloque = 1;   // au début, seul le niveau 1 est débloqué
    initialiser_niveau(game);
}

void initialiser_niveau(GameState *game) {
    // Réinitialisation complète du niveau
    for (int i = 1; i <= 5; i++) {
        game->objectif_items[i] = 0;
        game->progression_items[i] = 0; // Remettre la progression à zéro
    }

    switch (game->niveau) {
            case 1:
                game->coups_restants = 10;
                game->temps_restants = 90.0f;

                game->objectif_items[1] = 4; 
                game->objectif_items[2] = 4; 
                game->objectif_items[3] = 4;
                game->objectif_items[4] = 4; 
                game->objectif_items[5] = 4;

                game->inventaire_max[0] = 0;
                game->inventaire_max[1] = 0;
                game->inventaire_max[2] = 0;
                game->inventaire_max[3] = 0;
                break;
            case 2:
                game->coups_restants = 15;
                game->temps_restants = 120.0f;

                game->objectif_items[1] = 18; 
                game->objectif_items[2] = 24; 
                game->objectif_items[3] = 24;
                game->objectif_items[4] = 14; 
                game->objectif_items[5] = 0;

                game->inventaire_max[0] = 1;
                game->inventaire_max[1] = 0;
                game->inventaire_max[2] = 0;
                game->inventaire_max[3] = 0;
                break;
            case 3:
                game->coups_restants = 15;
                game->temps_restants = 120.0f;

                game->objectif_items[1] = 40; 
                game->objectif_items[2] = 0; 
                game->objectif_items[3] = 32;
                game->objectif_items[4] = 0; 
                game->objectif_items[5] = 40;

                game->inventaire_max[0] = 0;
                game->inventaire_max[1] = 2;
                game->inventaire_max[2] = 2;
                game->inventaire_max[3] = 0;
                break;
            case 4:
                game->coups_restants = 20;
                game->temps_restants = 160.0f;

                game->objectif_items[1] = 60; 
                game->objectif_items[2] = 0; 
                game->objectif_items[3] = 0;
                game->objectif_items[4] = 0; 
                game->objectif_items[5] = 0;

                game->inventaire_max[0] = 0;
                game->inventaire_max[1] = 1;
                game->inventaire_max[2] = 1;
                game->inventaire_max[3] = 3;
                break;
            case 5:
                game->coups_restants = 30;
                game->temps_restants = 300.0f;

                game->objectif_items[1] = 100; 
                game->objectif_items[2] = 100; 
                game->objectif_items[3] = 100;
                game->objectif_items[4] = 100; 
                game->objectif_items[5] = 100;

                game->inventaire_max[0] = 2;
                game->inventaire_max[1] = 1;
                game->inventaire_max[2] = 1;
                game->inventaire_max[3] = 2;
                break;
            default:
                printf("Niveau inconnu !\n");
                exit(1);
    }

    for (int i = 0; i < 4; i++) {
        game->inventaire[i] = game->inventaire_max[i]; // Remplir l'inventaire au max
    }
    
    int marque[LINE][COLUMN] = {0};
    int ligne, colonne, orientation;
    do {
        // Remplir le plateau aléatoirement
        for (int i = 0; i < LINE; i++) {
            for (int j = 0; j < COLUMN; j++) {
                game->plateau[i][j] = 1 + rand() % 5;
            }
        }
    } while (
        combinaison_ligne_6(game->plateau, marque) ||
        combinaison_colonne_6(game->plateau, marque) ||
        combinaison_croix(game->plateau, marque) ||
        combinaison_carre(game->plateau, marque) ||
        combinaison_ligne_4(game->plateau, marque) ||
        combinaison_colonne_4(game->plateau, marque) ||
        (game->niveau >= NIV_EXT && detecter_figures_speciales(game->plateau, &ligne, &colonne, &orientation)) 
    );
    // int plateau_test[LINE][COLUMN] = {
    // {1, 5, 3, 4, 5, 1, 2, 3, 4, 1},
    // {2, 1, 5, 3, 2, 5, 1, 2, 3, 1},
    // {3, 4, 1, 2, 5, 4, 1, 2, 3, 2},
    // {5, 5, 5, 5, 1, 5, 5, 2, 3, 5}, // <- ligne 7 horizontale identique (item 5)
    // {1, 2, 3, 5, 2, 2, 3, 4, 5, 2},
    // {2, 3, 1, 5, 2, 1, 4, 3, 2, 1},
    // {3, 4, 2, 3, 1, 2, 5, 1, 3, 4},
    // };
    // // Copier dans le plateau du jeu
    // for(int i = 0; i < LINE; i++){
    //     for(int j = 0; j < COLUMN; j++){
    //         game->plateau[i][j] = plateau_test[i][j];
    //     }
    // }
}

int contrat_rempli(GameState *game) {
    for (int i = 1; i <= 5; i++) {
        if (game->progression_items[i] < game->objectif_items[i])
            return 0;
    }
    return 1;
}

void afficher_objectifs(GameState *game) {
    if (game->niveau >= NIV_EXT) { 
        gotoxy(0, LINE + 9);
    } else {
        gotoxy(0, LINE + 6);
    }
    printf("=== Niveau %d ===\n", game->niveau);
    printf("Vies restantes : ");
    for (int i = 0; i < game->vies; i++) {
        printf("@ ");
    }

    printf("\nOBJECTIFS :");
    char symboles[6] = {' ', '*', '^', '&', '+', '%'};
    int couleurs[6] = {0, LIGHTRED, LIGHTGREEN, YELLOW, LIGHTCYAN, LIGHTMAGENTA}; // Couleurs ANSI pour les symboles
    for (int i = 1; i <= 5; i++) {
        if (game->objectif_items[i] > 0) {
            text_color(couleurs[i]);
            printf("\n - Item [%c] : %d / %d",
                   symboles[i],
                   game->progression_items[i],
                   game->objectif_items[i]);
            if (game->progression_items[i] >= game->objectif_items[i]) {
                printf(" (OK!)");
            }
        }
    }
    text_color(WHITE);
    printf("\nCoups restants : %d\n", game->coups_restants);
    if (game->temps_restants <= 30.0f) {
        text_color(LIGHTRED);
    }
    printf("Temps restant  : %.1f s     \n", game->temps_restants);
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
    int niveau_suivant_disponible = game->niveau < game->niveau_max_debloque;

    while (1) {
        clrscr();
        if (game->niveau >= MAX_NIVEAUX) {
            printf("PARTIE GAGNEE !\n");
            printf("Vous avez atteint le niveau maximum ! Felicitations !\n\n");
        }
        afficher_ecran_niveaux(game);

        printf("\n===== Options =====\n");
        printf("1 - Rejouer le niveau\n");

        if (niveau_suivant_disponible) {
            printf("2 - Passer au niveau suivant\n");
        } 
        else if (game->niveau < MAX_NIVEAUX) {
            printf("2 - [Passer au niveau suivant] (verrouille)\n");
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
                printf("\n Niveau non debloque !\n");
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
    printf("%s Niveau echoue.\n", raison);
    Sleep(1500);

    game->vies--;  // Décrémenter les vies

    if (game->vies <= 0) {
        clrscr();
        printf("\nToutes les vies sont perdues ! Partie terminee.\n");
        Sleep(2000);
        return 0;  // partie terminée
    }

    // Sinon, montrer le menu des niveaux
    clrscr();
    afficher_ecran_niveaux(game);
    return 1; // niveau perdu mais partie continue
}

