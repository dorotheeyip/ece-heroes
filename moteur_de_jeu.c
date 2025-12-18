#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "moteur_de_jeu.h"
#include "affichage_console.h"

// Active les couleurs ANSI sous Windows
void activer_couleurs() {
    system(" ");
    // PowerShell et CMD récents activent ANSI automatiquement
}

// void afficher_tab_symboles(int plateau[LINE][COLUMN]) {

//     printf("\x1b[H");  // repositionne en haut

//     for (int i = 0; i < LINE; i++) {
//         for (int j = 0; j < COLUMN; j++) {

//             char symbole;
//             int couleur;

//             switch (plateau[i][j]) {
//                 case 2: symbole = '*'; couleur = RED; break;
//                 case 3: symbole = '^'; couleur = GREEN; break;
//                 case 4: symbole = '&'; couleur = YELLOW; break;
//                 case 5: symbole = '+'; couleur = CYAN; break;
//                 case 6: symbole = '%'; couleur = MAGENTA; break;
//                 case 0: symbole = ' '; couleur = WHITE; break;
//                 default: symbole = '?'; couleur = WHITE; break;
//             }

//             text_color(couleur);     // couleur Windows
//             printf("%c ", symbole);  // symbole
//         }

//         printf("\n");
//     }

//     text_color(WHITE);  // reset
// }

void afficher_tab_symboles(int plateau[LINE][COLUMN]) {

    printf("\x1b[H");  // repositionne en haut

    for (int i = 0; i < LINE; i++) {
        for (int j = 0; j < COLUMN; j++) {

            char symbole;
            int couleur;

            switch (plateau[i][j]) {
                case 1: symbole = '*'; couleur = LIGHTRED; break;      // 12 au lieu de RED (4)
                case 2: symbole = '^'; couleur = LIGHTGREEN; break;    // 10 au lieu de GREEN (2)
                case 3: symbole = '&'; couleur = YELLOW; break;         // 14 (déjà ok)
                case 4: symbole = '+'; couleur = LIGHTCYAN; break;     // 11 au lieu de CYAN (3) ⭐
                case 5: symbole = '%'; couleur = LIGHTMAGENTA; break;  // 13 au lieu de MAGENTA (5) ⭐
                case 0: symbole = ' '; couleur = WHITE; break;
                default: symbole = '?'; couleur = WHITE; break;
            }

            text_color(couleur);
            printf("%c ", symbole);
        }

        printf("\n");
    }

    text_color(WHITE);
}

void afficher_tab(int plateau[LINE][COLUMN]){
    for (int i = 0; i < LINE; i++) {
        for (int j = 0; j < COLUMN; j++) {
            printf("%d ", plateau[i][j]);
        }
        printf("\n");
    }
}

int combinaison_ligne_6(int plateau[LINE][COLUMN]){
    int i, j, k; 
    for(i=0; i<LINE; i++){
        for(j=0; j<COLUMN-5; j++){
            if(plateau[i][j]!=0 && plateau[i][j]==plateau[i][j+1] && plateau[i][j+1]==plateau[i][j+2] && plateau[i][j+2]==plateau[i][j+3] && plateau[i][j+3]==plateau[i][j+4] && plateau[i][j+4]==plateau[i][j+5]){              
                    return 1;
            }
        }
    }
    return 0;
}

int combinaison_colonne_6(int plateau[LINE][COLUMN]){
    int i, j, k; 
    for(j=0; j<COLUMN; j++){
        for(i=0; i<LINE-5; i++){
            if(plateau[i][j]!=0 && plateau[i][j]==plateau[i+1][j] && plateau[i+1][j]==plateau[i+2][j] && plateau[i+2][j]==plateau[i+3][j] && plateau[i+3][j]==plateau[i+4][j] && plateau[i+4][j]==plateau[i+5][j]){              
                return 1;
            }
        }
    }
    return 0;
}

int combinaison_croix(int plateau[LINE][COLUMN]){
    int i, j, centre;
    for(i=2; i<LINE-2; i++){
        for(j=2; j<COLUMN-2; j++){
            centre=plateau[i][j]; 
            if(centre!=0 && centre==plateau[i-2][j] && centre==plateau[i-1][j] && centre==plateau[i+1][j] && centre==plateau[i+2][j] && centre==plateau[i][j-2] && centre==plateau[i][j-1] && centre==plateau[i][j+1] && centre==plateau[i][j+2]){
                return 1;
            }
        }
    }
    return 0;
}

int combinaison_carre(int plateau[LINE][COLUMN]){
    int i, j;
    int cote_gauche, cote_droit, cote_haut, cote_bas;
    for(i=0; i<LINE-3; i++){
        for(j=0; j<COLUMN-3; j++){
            if(plateau[i][j]!=0 && plateau[i][j] == plateau[i+1][j] && plateau[i+1][j] == plateau[i+2][j] && plateau[i+2][j] == plateau[i+3][j] &&
               plateau[i][j+3] == plateau[i+1][j+3] && plateau[i+1][j+3] == plateau[i+2][j+3] && plateau[i+2][j+3] == plateau[i+3][j+3] &&
               plateau[i][j] == plateau[i][j+1] && plateau[i][j+1] == plateau[i][j+2] && plateau[i][j+2] == plateau[i][j+3] &&
               plateau[i+3][j] == plateau[i+3][j+1] && plateau[i+3][j+1] == plateau[i+3][j+2] && plateau[i+3][j+2] == plateau[i+3][j+3]){
                cote_gauche=plateau[i][j];
                cote_droit=plateau[i][j+3];
                cote_haut=plateau[i][j];
                cote_bas=plateau[i+3][j];
                return 1;
            }
        }
    }
    return 0;
}

int combinaison_ligne_4(int plateau[LINE][COLUMN]){
    int i, j;
    for(i=0; i<LINE; i++){
        for(j=0; j<COLUMN-3; j++){
            if(plateau[i][j]!=0 && plateau[i][j]==plateau[i][j+1] && plateau[i][j+1]==plateau[i][j+2] && plateau[i][j+2]==plateau[i][j+3]){
                return 1;
            }
        }
    }
    return 0;
}

int combinaison_colonne_4(int plateau[LINE][COLUMN]){
    int i, j;
    for(i=0; i<LINE-3; i++){
        for(j=0; j<COLUMN; j++){
            if(plateau[i][j]!=0 && plateau[i][j]==plateau[i+1][j] && plateau[i+1][j]==plateau[i+2][j] && plateau[i+2][j]==plateau[i+3][j]){
                return 1;
            }
        }
    }
    return 0;
}

void supprime_combin(int plateau[LINE][COLUMN]){
    int i, j, ligne_6, colonne_6, centre, ligne_4, colonne_4;
    if(combinaison_ligne_6(plateau)){
        for(i=0; i<LINE; i++){
            for(j=0; j<COLUMN-5; j++){
                ligne_6=plateau[i][j];
                if(ligne_6!=0 && ligne_6==plateau[i][j+1] && ligne_6==plateau[i][j+2] && ligne_6==plateau[i][j+3] && ligne_6==plateau[i][j+4] && ligne_6==plateau[i][j+5]){
                    for(int k=0; k>LINE; k++){
                        for(int l=0; l<COLUMN; l++){
                            if(plateau[k][l]==plateau[i][j]){
                                plateau[k][l]=0;
                            }
                        }
                    }
                }
            }
        }
    }
    if(combinaison_colonne_6(plateau)){
        for(i=0; i<LINE-5; i++){
            for(j=0; j<COLUMN; j++){
                colonne_6=plateau[i][j];
                if(colonne_6!=0 && colonne_6==plateau[i+1][j] && colonne_6==plateau[i+2][j] && colonne_6==plateau[i+3][j] && colonne_6==plateau[i+4][j] && colonne_6==plateau[i+5][j]){
                    for(int k=0; k>LINE; k++){
                        for(int l=0; l<COLUMN; l++){
                            if(plateau[k][l]==plateau[i][j]){
                                plateau[k][l]=0;
                            }
                        }
                    }
                }
            }
        }
    }
    if(combinaison_croix(plateau)){
        for(i=2; i<LINE-2; i++){
            for(j=2; j<COLUMN-2; j++){
                centre=plateau[i][j];
                if(centre!=0 && centre==plateau[i-2][j] && centre==plateau[i-1][j] && centre==plateau[i+1][j] && centre==plateau[i+2][j] && centre==plateau[i][j-2] && centre==plateau[i][j-1] && centre==plateau[i][j+1] && centre==plateau[i][j+2]){
                    plateau[i][j]=0;
                    plateau[i-2][j]=0;
                    plateau[i-1][j]=0;
                    plateau[i+1][j]=0;
                    plateau[i+2][j]=0;
                    plateau[i][j-2]=0;
                    plateau[i][j-1]=0;
                    plateau[i][j+1]=0;
                    plateau[i][j+2]=0;
                }
            }
        }
    }
    if(combinaison_carre(plateau)){
        for(i=0; i<LINE-3; i++){
            for(j=0; j<COLUMN-3; j++){
                if(plateau[i][j]!=0 && plateau[i][j] == plateau[i+1][j] && plateau[i+1][j] == plateau[i+2][j] && plateau[i+2][j] == plateau[i+3][j] &&
               plateau[i][j+3] == plateau[i+1][j+3] && plateau[i+1][j+3] == plateau[i+2][j+3] && plateau[i+2][j+3] == plateau[i+3][j+3] &&
               plateau[i][j] == plateau[i][j+1] && plateau[i][j+1] == plateau[i][j+2] && plateau[i][j+2] == plateau[i][j+3] &&
               plateau[i+3][j] == plateau[i+3][j+1] && plateau[i+3][j+1] == plateau[i+3][j+2] && plateau[i+3][j+2] == plateau[i+3][j+3]){
                    plateau[i][j]=0;
                    plateau[i+1][j]=0;
                    plateau[i+2][j]=0;
                    plateau[i+3][j]=0;
                    plateau[i][j+3]=0;
                    plateau[i+1][j+3]=0;
                    plateau[i+2][j+3]=0;
                    plateau[i+3][j+3]=0;
                    plateau[i][j+1]=0;
                    plateau[i][j+2]=0;
                    plateau[i+3][j+1]=0;
                    plateau[i+3][j+2]=0;
                }
            }
        }
    }
    if(combinaison_ligne_4(plateau)){
        for(i=0; i<LINE; i++){
            for(j=0; j<COLUMN-3; j++){
                ligne_4=plateau[i][j];
                if(ligne_4!=0 && ligne_4==plateau[i][j+1] && ligne_4==plateau[i][j+2] && ligne_4==plateau[i][j+3]){
                    plateau[i][j]=0;
                    plateau[i][j+1]=0;
                    plateau[i][j+2]=0;
                    plateau[i][j+3]=0;
                }
            }
        }
    }
    if(combinaison_colonne_4(plateau)){
        for(i=0; i<LINE-3; i++){
            for(j=0; j<COLUMN; j++){
                colonne_4=plateau[i][j];
                if(colonne_4!=0 && colonne_4==plateau[i+1][j] && colonne_4==plateau[i+2][j] && colonne_4==plateau[i+3][j]){
                    plateau[i][j]=0;
                    plateau[i+1][j]=0;
                    plateau[i+2][j]=0;
                    plateau[i+3][j]=0;
                }
            }
        }
    }
}

void renouvellement_case(int plateau[LINE][COLUMN]) {
    int i, j;

    // Affiche l'état initial (trous visibles)
    printf("\x1b[H");
    afficher_tab_symboles(plateau);
    Sleep(500);

    // --------------------------------------------------------
    // 1) Appliquer la gravité jusqu'à stabilisation (par buffer)
    // --------------------------------------------------------
    int changed;
    do {
        changed = 0;
        int next[LINE][COLUMN];

        // copie
        for (i = 0; i < LINE; i++)
            for (j = 0; j < COLUMN; j++)
                next[i][j] = plateau[i][j];

        // application de la gravité en "parallèle"
        for (i = LINE - 1; i > 0; i--) {
            for (j = 0; j < COLUMN; j++) {
                if (plateau[i][j] == 0 && plateau[i - 1][j] != 0) {
                    next[i][j] = plateau[i - 1][j];
                    next[i - 1][j] = 0;
                    changed = 1;
                }
            }
        }

        // copie back
        for (i = 0; i < LINE; i++)
            for (j = 0; j < COLUMN; j++)
                plateau[i][j] = next[i][j];

        if (changed) {
            printf("\x1b[H");
            afficher_tab_symboles(plateau);
            Sleep(120);
        }
    } while (changed);

    // --------------------------------------------------------
    // 2) Préparer les nouvelles pièces par colonne (UNE FOIS)
    //    Après la gravité, les zéros doivent être tous en haut d'une colonne.
    // --------------------------------------------------------
    int need_fill = 0;
    int count_zero[COLUMN];
    int new_pieces[COLUMN][LINE]; // maximum LINE nouvelles pièces par colonne
    int max_m = 0;

    for (j = 0; j < COLUMN; j++) {
        // compter les zéros en haut (continus ou totaux : après gravité ce seront les zéros)
        int cnt = 0;
        for (i = 0; i < LINE; i++) {
            if (plateau[i][j] == 0) cnt++;
        }
        count_zero[j] = cnt;
        if (cnt > 0) need_fill = 1;
        if (cnt > max_m) max_m = cnt;

        // générer UNE SEULE FOIS les pièces nécessaires, de haut vers bas
        for (i = 0; i < cnt; i++) {
            new_pieces[j][i] = 1 + rand() % 5;
        }
    }

    if (!need_fill) {
        // rien à remplir
        printf("\x1b[H");
        afficher_tab_symboles(plateau);
        Sleep(200);
        return;
    }

    // --------------------------------------------------------
    // 3) Animation synchronisée : on fait avancer toutes les nouvelles pièces
    //    en augmentant un temps t de 0..max_m (à t = count_zero[j] la colonne j est remplie)
    // --------------------------------------------------------
    for (int t = 0; t <= max_m; t++) {
        int frame[LINE][COLUMN];

        // commencer par une copie du plateau actuel (avec zéros en haut)
        for (i = 0; i < LINE; i++)
            for (j = 0; j < COLUMN; j++)
                frame[i][j] = plateau[i][j];

        // pour chaque colonne, placer les nouvelles pièces temporairement selon t
        for (j = 0; j < COLUMN; j++) {
            int m = count_zero[j];
            if (m == 0) continue;

            // chaque nouvelle pièce k a start_row = - (m - k)
            // final_row = k (0..m-1)
            for (int k = 0; k < m; k++) {
                int start_row = -(m - k);
                int cur_row = start_row + t;

                if (cur_row < 0) {
                    // pas encore dans la grille -> rien à dessiner
                    continue;
                }
                if (cur_row > k) {
                    // ne dépasse pas sa position finale
                    cur_row = k;
                }
                if (cur_row >= 0 && cur_row < LINE) {
                    frame[cur_row][j] = new_pieces[j][k];
                }
            }

            // IMPORTANT : s'assurer que les cases au dessus des pièces temporaires restent visibles comme 0
            // (on laisse frame tel quel car on a initialisé depuis plateau qui a des zéros en haut)
        }

        // afficher la frame
        printf("\x1b[H");
        afficher_tab_symboles(frame);
        Sleep(120);
    }

    // --------------------------------------------------------
    // 4) Mettre à jour le plateau final avec les nouvelles pièces (stateful)
    // --------------------------------------------------------
    for (j = 0; j < COLUMN; j++) {
        int m = count_zero[j];
        if (m == 0) continue;

        // placer les nouvelles pièces en haut (0..m-1)
        for (i = 0; i < m; i++) {
            plateau[i][j] = new_pieces[j][i];
        }
        // les autres cases (i >= m) sont déjà les éléments tombés après la gravité
    }

    // affichage final
    printf("\x1b[H");
    afficher_tab_symboles(plateau);
    Sleep(200);
}
