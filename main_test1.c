#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#ifdef _WIN32
    #include <windows.h>
    #include "affichage_console.h"
#else
    #include "affichage_console_mac.h"
#endif
#include "moteur_de_jeu.h"
#include "g_entree_user.h"
#include "interface_console.h"
#include "extensions.h"
#include "nouvelle_partie.h"
#include "sauvegarde.h"

// Fonction principale du jeu
void jouer_niveau(int num_niveau, GameState *game, int reinitialiser) {
    srand(time(NULL));
    int compteur_item0[6] = {0}; 
    game->niveau = num_niveau;
    int niveau_reussi = game->niveau;
    if (reinitialiser) {
        initialiser_niveau(game); // seulement pour nouvelle partie ou niveau fraîchement démarré
    }

    int continuer = 1;
    int marque[LINE][COLUMN] = {0};
    int niveau_echoue = 0;

    while (continuer) {
        continuer = 0;

        // Réinitialiser la grille de marques
        for (int i = 0; i < LINE; i++)
            for (int j = 0; j < COLUMN; j++)
                marque[i][j] = 0;

        // Détecter les combinaisons
        if (combinaison_ligne_6(game->plateau, marque) ||
            combinaison_colonne_6(game->plateau, marque) ||
            combinaison_croix(game->plateau, marque) ||
            combinaison_carre(game->plateau, marque) ||
            combinaison_ligne_4(game->plateau, marque) ||
            combinaison_colonne_4(game->plateau, marque)) {

            continuer = 1;

            // Supprimer les combinaisons
            supprim_combin(game->plateau, marque, compteur_item0);

            // Faire tomber et renouveler les cases
            renouvellement_case(game->plateau);
        }
    }
    
    Cursor c = {0, 0};

    SelectionState s = {0, -1, -1, -1, -1};
    int running = 1;
    
    clrscr();
    hide_cursor();

    
    
    while (running) {
        
        // Afficher le plateau
        gotoxy(0, 0);
        afficher_tab_symboles(game->plateau);
        afficher_objectifs(game);
        
         // --- Gestion échec niveau ---
        if (!niveau_echoue && maj_temps(game)) {
            if (!gerer_echec_niveau(game, "Temps écoulé !")) {
                // Plus de vies -> retour menu principal
                return;
            } else {
                // Niveau perdu mais vies restantes -> menu niveaux
                niveau_echoue = 1;
            }
        }

        if (!niveau_echoue && game->coups_restants <= 0) {
            if (!gerer_echec_niveau(game, "Plus de coups !")) {
                return; // partie terminée
            } else {
                niveau_echoue = 1; // niveau perdu mais vies restantes
            }
        }

        if (niveau_echoue) {
            int choix = menu_niveau_options(game);

            if (choix == 1) {
                // Rejouer le niveau actuel
                jouer_niveau(game->niveau, game, 1);
                return;
            } else if (choix == 2) {
                // Passer au niveau suivant
                game->niveau++;
                jouer_niveau(game->niveau, game, 1);
                return;
            } else {
                // Retour menu principal
                return;
            }
        }

        // Mise à jour du temps
        // if (maj_temps(game)) {
        //     if (!gerer_echec_niveau(game, "Temps écoulé !")) return; 
        // }

        // Afficher le nouveau en blanc
        afficher_item_selec(c.line, c.col * 2, game->plateau[c.line][c.col]);
        
        // Afficher les infos
        gotoxy(0, LINE + 2);
        printf("Position curseur: (%d, %d)  ", c.line, c.col);
        gotoxy(0, LINE + 3);
        printf("Selection: %d  ", s.selected);
        if (s.selected > 0) {
            printf("Item1: (%d,%d)  ", s.r1, s.c1);
        }
        if (s.selected > 1) {
            printf("Item2: (%d,%d)  ", s.r2, s.c2);
        }
        gotoxy(0, LINE + 4);
        printf("ZQSD ou Fleches = Deplacer | ESPACE = Selectionner | ECHAP = Quitter");
        
        // Lire une touche
        int touche = lire_touche();
        if (touche != -1) {
            
            // Quitter
            if (touche == 27) { // ESC
                running = 0;
                continue;
            }
            
            // Déplacement du curseur
            deplacer_curseur(&c, LINE, COLUMN, touche);
            
            // Sélection item
            if (touche == ' ') {
                
                if (s.selected == 0) {
                    // Première sélection
                    selectionner_item1(&s, c, game);
                    
                } else if (s.selected == 1) {
                    // Deuxième sélection
                    
                    // Vérifier si les cases sont adjacentes
                    int diff_r = abs(s.r1 - c.line);
                    int diff_c = abs(s.c1 - c.col);
                    
                    if ((diff_r == 1 && diff_c == 0) || (diff_r == 0 && diff_c == 1)) {
                        // Cases adjacentes
                        selectionner_item2(&s, c, game);
                        
                        // Test combinaison valide
                        if (combinaison_valide(s, game)) {
                            // Permuter
                            permuter_items(&s, game);
                            
                            // Décrémenter le nombre de coups restants
                            game->coups_restants--;

                            // if (game->coups_restants <= 0) {
                            //     if (!gerer_echec_niveau(game, "Plus de coups !")) return; 
                            // }

                            // Afficher la permutation
                            clrscr();
                            gotoxy(0, 0);
                            afficher_tab_symboles(game->plateau);
                            afficher_objectifs(game);
                            pause_avec_temps(game, 300);
                            
                            // Traiter les combinaisons
                            int continuer = 1;
                            int marque[LINE][COLUMN]={0};
                            int compteur_item[6]={0}; // Compteur pour les items supprimés 
                            while (continuer) {
                                continuer = 0;
                                for(int i=0; i<LINE; i++){
                                    for(int j=0; j<COLUMN; j++){
                                        marque[i][j]=0;
                                    }
                                }
                                
                                // Détecter et supprimer
                                if (combinaison_ligne_6(game->plateau, marque) ||
                                    combinaison_colonne_6(game->plateau, marque) ||
                                    combinaison_croix(game->plateau, marque) ||
                                    combinaison_carre(game->plateau, marque) ||
                                    combinaison_ligne_4(game->plateau, marque) ||
                                    combinaison_colonne_4(game->plateau, marque)) {
                                    
                                    continuer = 1;

                                    // Montrer les combinaisons
                                    clrscr();
                                    gotoxy(0, 0);
                                    afficher_tab_symboles(game->plateau);
                                    afficher_objectifs(game);
                                    pause_avec_temps(game, 500);
                                    
                                    // Supprimer
                                    supprim_combin(game->plateau, marque, compteur_item);
                                    
                                    if (num_niveau >= 2) {
                                        // Appliquer les effets des extensions
                                        effet_extensions(game->plateau, compteur_item);
                                    }

                                    for (int i = 1; i <= 5; i++) {
                                        game->progression_items[i] += compteur_item[i];
                                        compteur_item[i] = 0;
                                    }
                                    
                                    // Montrer les trous
                                    clrscr();
                                    gotoxy(0, 0);
                                    afficher_tab_symboles(game->plateau);
                                    afficher_objectifs(game);
                                    pause_avec_temps(game, 500);
                                    
                                    // Faire tomber et remplir
                                    renouvellement_case(game->plateau);
                                }
                            }
                            
                            // Vérifier si le contrat du niveau est rempli
                            if (contrat_rempli(game)) {
                                clrscr();
                                printf("\nNiveau %d réussi !\n", game->niveau);
                                Sleep(1500);

                                // Débloquer le niveau suivant pour le menu
                                if (game->niveau < MAX_NIVEAUX) {
                                    game->niveau_max_debloque = game->niveau + 1;
                                }
                            
                                sauvegarder_partie(game);
                                // Afficher l'écran des niveaux
                                afficher_ecran_niveaux(game);

                                // // Proposer de passer au niveau suivant ou revenir au menu
                                // if (menu_niveau_options(game)) {
                                //     // Jouer le niveau suivant
                                //     game->niveau++;                 // débloquer le niveau suivant
                                //     jouer_niveau(game->niveau, game, 1); // lancer nouveau niveau
                                //     return; // le joueur a choisi de continuer au niveau suivant
                                // } else {
                                //     return; // retour au menu principal
                                // }
                            
                            int choix = menu_niveau_options(game);

                            if (choix == 1) {
                                // Rejouer le niveau réussi
                                jouer_niveau(niveau_reussi, game, 1);
                                return;
                            }

                            if (choix == 2) {
                                // Passer au niveau suivant
                                jouer_niveau(niveau_reussi + 1, game, 1);
                                return;
                            }

                            // Retour menu principal
                            return;


                                // return; // on sort du niveau actuel
                            }

                            // Réinitialiser la sélection
                            s.selected = 0;

                            // Sauvegarder la partie après chaque coup
                            sauvegarder_partie(game);
                            
                        } else {
                            // Combinaison invalide - annuler
                            gotoxy(0, LINE + 5);
                            text_color(RED);
                            printf("Mouvement invalide !     ");
                            text_color(WHITE);
                            Sleep(1000);
                            s.selected = 0;
                        }
                        
                    } else {
                        // Cases non adjacentes
                        gotoxy(0, LINE + 5);
                        text_color(RED);
                        printf("Les cases doivent etre adjacentes !     ");
                        text_color(WHITE);
                        Sleep(1000);
                        s.selected = 0;
                    }
                }
            }
            
            // Effacer la ligne d'erreur
            gotoxy(0, LINE + 5);
            printf("                                              ");
        }
        
        Sleep(50); // Petite pause pour ne pas surcharger le CPU
    }

    
    show_cursor();
    clrscr();
}

void jouer_partie(GameState *game, int nouvelle) {
    jouer_niveau(game->niveau, game, nouvelle);
}

// Fonction pour afficher le menu
void afficher_menu() {
    printf("\n===== MENU =====\n");
    printf("1 - Lire les regles du jeu\n");
    printf("2 - Demarrer une nouvelle partie\n");
    printf("3 - Reprendre une partie sauvegardee\n");
    printf("0 - Quitter\n");
    printf("Votre choix : ");
}

// Fonction pour lire les règles
int lire_regle_du_jeu() {
    FILE *f = fopen("regles_jeu.txt", "r");
    char texte[256];

    if (!f) {
        printf("Impossible d'ouvrir le fichier regles_jeu.txt.\n");
        printf("\nREGLES DU JEU:\n");
        printf("- Utilisez ZQSD ou les fleches pour deplacer le curseur\n");
        printf("- Appuyez sur ESPACE pour selectionner un item\n");
        printf("- Selectionnez deux items adjacents pour les echanger\n");
        printf("- Formez des combinaisons de 4+ symboles identiques\n");
        printf("- Appuyez sur ECHAP pour quitter\n");
        return 1;
    }

    while (fgets(texte, sizeof(texte), f) != NULL) {
        printf("%s", texte);
    }

    fclose(f);
    return 0;
}

// Programme principal
int main() {
    int choix;
    GameState game;

    do {
        afficher_menu();
        scanf("%d", &choix);

        switch (choix) {
            case 1: // 1 - Lire les règles du jeu
                lire_regle_du_jeu();
                printf("\nAppuyez sur Entree pour continuer...");
                getchar(); // Consommer le '\n' restant
                getchar(); // Attendre l'utilisateur
                break;

            case 2: // 2 - Démarrer une nouvelle partie
                printf("Entrez votre pseudo : ");
                scanf("%s", game.pseudo);
                lancer_nouvelle_partie(&game);
                jouer_partie(&game, 1); // nouvelle partie
                break;

            case 3: // 3 - Reprendre une partie sauvegardée
                printf("Entrez votre pseudo : ");
                scanf("%s", game.pseudo);   

                if (charger_sauvegarde(&game) == 1) {
                    printf("Sauvegarde chargée pour le joueur %s au niveau %d.\n", game.pseudo, game.niveau);
                    Sleep(1000);
                    jouer_partie(&game, 0); // reprendre partie
                } 
                else {
                    printf("Aucune sauvegarde trouvée. Démarrage d'une nouvelle partie pour %s.\n", game.pseudo);
                    Sleep(1000);
                    lancer_nouvelle_partie(&game);
                    jouer_partie(&game, 1); // nouvelle partie
                }
                Sleep(1500);
                break;

            case 0: // 0 - Quitter
                printf("Au revoir !\n");
                break;

            default:
                printf("Choix invalide.\n");
                Sleep(1000);
        }

    } while (choix != 0);

    return 0;
}