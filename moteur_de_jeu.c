#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "moteur_de_jeu.h"
#include "affichage_console.h"

// --------------------------------------------------------
// Active les couleurs ANSI sous Windows
// --------------------------------------------------------
void activer_couleurs() {
    system(" ");
}

// --------------------------------------------------------
// Affichage du plateau avec symboles colorés
// --------------------------------------------------------
void afficher_tab_symboles(int plateau[LINE][COLUMN]) {
    printf("\x1b[H");
    for (int i = 0; i < LINE; i++) {
        for (int j = 0; j < COLUMN; j++) {
            char symbole;
            int couleur;
            switch (plateau[i][j]) {
                case 1: symbole = '*'; couleur = LIGHTRED; break;
                case 2: symbole = '^'; couleur = LIGHTGREEN; break;
                case 3: symbole = '&'; couleur = YELLOW; break;
                case 4: symbole = '+'; couleur = LIGHTCYAN; break;
                case 5: symbole = '%'; couleur = LIGHTMAGENTA; break;
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

// --------------------------------------------------------
void afficher_tab(int plateau[LINE][COLUMN]){
    for(int i = 0; i < LINE; i++){
        for(int j = 0; j < COLUMN; j++){
            printf("%d ", plateau[i][j]);
        }
        printf("\n");
    }
}

// --------------------------------------------------------
// Détection des combinaisons
// --------------------------------------------------------
int combinaison_ligne_6(int plateau[LINE][COLUMN], int marque[LINE][COLUMN]){
    int trouve = 0;
    for(int i = 0; i < LINE; i++){
        for(int j = 0; j < COLUMN-5; j++){
            int val = plateau[i][j];
            if(val != 0 &&
               val == plateau[i][j+1] &&
               val == plateau[i][j+2] &&
               val == plateau[i][j+3] &&
               val == plateau[i][j+4] &&
               val == plateau[i][j+5]){
                for(int k = 0; k < LINE; k++){
                    for(int l=0; l < COLUMN; l++){
                        if(plateau[k][l]==val){
                            marque[k][l]=1;
                        }
                    }
                }
                trouve = 1;
            }
        }
    }
    return trouve;
}

int combinaison_colonne_6(int plateau[LINE][COLUMN], int marque[LINE][COLUMN]){
    int trouve = 0;
    for(int j = 0; j < COLUMN; j++){
        for(int i = 0; i < LINE-5; i++){
            int val = plateau[i][j];
            if(val != 0 &&
               val == plateau[i+1][j] &&
               val == plateau[i+2][j] &&
               val == plateau[i+3][j] &&
               val == plateau[i+4][j] &&
               val == plateau[i+5][j]){
                for(int k=0; k < LINE; k++){
                    for(int l=0; l < COLUMN; l++){
                        if(plateau[k][l]==val){
                            marque[k][l]=1;
                        }
                    }
                }
                trouve = 1;
            }
        }
    }
    return trouve;
}

int combinaison_croix(int plateau[LINE][COLUMN], int marque[LINE][COLUMN]){
    int trouve=0;
    for(int i=2; i<LINE-2; i++){
        for(int j=2; j<COLUMN-2; j++){
            int centre=plateau[i][j]; 
            if(centre!=0 && centre==plateau[i-2][j] && centre==plateau[i-1][j] && centre==plateau[i+1][j] && centre==plateau[i+2][j] && centre==plateau[i][j-2] && centre==plateau[i][j-1] && centre==plateau[i][j+1] && centre==plateau[i][j+2]){
                marque[i][j]=1;
                marque[i-2][j]=1;
                marque[i-1][j]=1;
                marque[i+1][j]=1;
                marque[i+2][j]=1;
                marque[i][j-2]=1;
                marque[i][j-1]=1;
                marque[i][j+1]=1;
                marque[i][j+2]=1;
                trouve=1;
            }
        }
    }
    return trouve;
}

int combinaison_carre(int plateau[LINE][COLUMN], int marque[LINE][COLUMN]){
    int trouve=0;
    for(int i=0; i<LINE-3; i++){
        for(int j=0; j<COLUMN-3; j++){
            if(plateau[i][j]!=0 && plateau[i][j] == plateau[i+1][j] && plateau[i+1][j] == plateau[i+2][j] && plateau[i+2][j] == plateau[i+3][j] &&
               plateau[i][j+3] == plateau[i+1][j+3] && plateau[i+1][j+3] == plateau[i+2][j+3] && plateau[i+2][j+3] == plateau[i+3][j+3] &&
               plateau[i][j] == plateau[i][j+1] && plateau[i][j+1] == plateau[i][j+2] && plateau[i][j+2] == plateau[i][j+3] &&
               plateau[i+3][j] == plateau[i+3][j+1] && plateau[i+3][j+1] == plateau[i+3][j+2] && plateau[i+3][j+2] == plateau[i+3][j+3]){
                marque[i][j]=1;
                marque[i+1][j]=1;
                marque[i+2][j]=1;
                marque[i+3][j]=1;
                marque[i][j+3]=1;
                marque[i+1][j+3]=1;
                marque[i+2][j+3]=1;
                marque[i+3][j+3]=1;
                marque[i][j+1]=1;
                marque[i][j+2]=1;
                marque[i+3][j+1]=1;
                marque[i+3][j+2]=1;
                trouve=1;
            }
        }
    }
    return trouve;
}

int combinaison_ligne_4(int plateau[LINE][COLUMN], int marque[LINE][COLUMN]){
    int trouve = 0;
    for(int i = 0; i < LINE; i++){
        for(int j = 0; j < COLUMN-3; j++){
            int val = plateau[i][j];
            if(val != 0 &&
               val == plateau[i][j+1] &&
               val == plateau[i][j+2] &&
               val == plateau[i][j+3]){
                for(int k = 0; k < 4; k++)
                    marque[i][j+k] = 1;
                trouve = 1;
            }
        }
    }
    return trouve;
}

int combinaison_colonne_4(int plateau[LINE][COLUMN], int marque[LINE][COLUMN]){
    int trouve = 0;
    for(int j = 0; j < COLUMN; j++){
        for(int i = 0; i < LINE-3; i++){
            int val = plateau[i][j];
            if(val != 0 &&
               val == plateau[i+1][j] &&
               val == plateau[i+2][j] &&
               val == plateau[i+3][j]){
                for(int k = 0; k < 4; k++)
                    marque[i+k][j] = 1;
                trouve = 1;
            }
        }
    }
    return trouve;
}

// --------------------------------------------------------
// Suppression + comptage (compteur[1..5])
// --------------------------------------------------------
void supprim_combin(int plateau[LINE][COLUMN], int marque[LINE][COLUMN], int compteur[6]){
    for(int i = 0; i < LINE; i++){
        for(int j = 0; j < COLUMN; j++){
            if(marque[i][j]){
                int item = plateau[i][j];
                if(item != 0){
                    compteur[item]++;
                    plateau[i][j] = 0;
                }
            }
        }
    }
    for(int k=0; k < LINE; k++){
        for(int l=0; l < COLUMN; l++){
            marque[k][l]=0;
        }
    }
}

// --------------------------------------------------------
// Gravité + renouvellement
// --------------------------------------------------------
// --------------------------------------------------------
// Gravité + renouvellement animé
// --------------------------------------------------------
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
    // --------------------------------------------------------
    int need_fill = 0;
    int count_zero[COLUMN];
    int new_pieces[COLUMN][LINE]; // maximum LINE nouvelles pièces par colonne
    int max_m = 0;

    for (j = 0; j < COLUMN; j++) {
        int cnt = 0;
        for (i = 0; i < LINE; i++) {
            if (plateau[i][j] == 0) cnt++;
        }
        count_zero[j] = cnt;
        if (cnt > 0) need_fill = 1;
        if (cnt > max_m) max_m = cnt;

        for (i = 0; i < cnt; i++) {
            new_pieces[j][i] = 2 + rand() % 5; // 2 à 6, change si tu veux 1-5
        }
    }

    if (!need_fill) {
        printf("\x1b[H");
        afficher_tab_symboles(plateau);
        Sleep(200);
        return;
    }

    // --------------------------------------------------------
    // 3) Animation synchronisée des nouvelles pièces
    // --------------------------------------------------------
    for (int t = 0; t <= max_m; t++) {
        int frame[LINE][COLUMN];

        // copie du plateau actuel
        for (i = 0; i < LINE; i++)
            for (j = 0; j < COLUMN; j++)
                frame[i][j] = plateau[i][j];

        for (j = 0; j < COLUMN; j++) {
            int m = count_zero[j];
            if (m == 0) continue;

            for (int k = 0; k < m; k++) {
                int start_row = -(m - k);
                int cur_row = start_row + t;

                if (cur_row < 0) continue;
                if (cur_row > k) cur_row = k;
                if (cur_row >= 0 && cur_row < LINE)
                    frame[cur_row][j] = new_pieces[j][k];
            }
        }

        printf("\x1b[H");
        afficher_tab_symboles(frame);
        Sleep(120);
    }

    // --------------------------------------------------------
    // 4) Mettre à jour le plateau final
    // --------------------------------------------------------
    for (j = 0; j < COLUMN; j++) {
        int m = count_zero[j];
        if (m == 0) continue;
        for (i = 0; i < m; i++) {
            plateau[i][j] = new_pieces[j][i];
        }
    }

    // affichage final
    printf("\x1b[H");
    afficher_tab_symboles(plateau);
    Sleep(200);
}
