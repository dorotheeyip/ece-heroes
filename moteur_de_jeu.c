#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "moteur_de_jeu.h"
#ifdef _WIN32
    #include <windows.h>
    #include "affichage_console.h"
#else
    #include "affichage_console_mac.h"
#endif

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
// Réinitialisation du tableau marque (OBLIGATOIRE)
// --------------------------------------------------------
void reset_marque(int marque[LINE][COLUMN]){
    for(int i = 0; i < LINE; i++)
        for(int j = 0; j < COLUMN; j++)
            marque[i][j] = 0;
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
                for(int k = 0; k < 6; k++)
                    marque[i][j+k] = 1;
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
                for(int k = 0; k < 6; k++)
                    marque[i+k][j] = 1;
                trouve = 1;
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
void supprim_items_marques(int plateau[LINE][COLUMN],
                           int marque[LINE][COLUMN],
                           int compteur[6]){
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
}

// --------------------------------------------------------
// Gravité + renouvellement
// --------------------------------------------------------
void renouvellement_case(int plateau[LINE][COLUMN]) {
    int changed;
    do {
        changed = 0;
        int next[LINE][COLUMN];
        for(int i = 0; i < LINE; i++)
            for(int j = 0; j < COLUMN; j++)
                next[i][j] = plateau[i][j];

        for(int i = LINE-1; i > 0; i--){
            for(int j = 0; j < COLUMN; j++){
                if(plateau[i][j] == 0 && plateau[i-1][j] != 0){
                    next[i][j] = plateau[i-1][j];
                    next[i-1][j] = 0;
                    changed = 1;
                }
            }
        }

        for(int i = 0; i < LINE; i++)
            for(int j = 0; j < COLUMN; j++)
                plateau[i][j] = next[i][j];

    } while(changed);
    int count_zero[COLUMN];
    for(int j = 0; j < COLUMN; j++){
        int cnt = 0;
        for(int i = 0; i < LINE; i++)
            if(plateau[i][j] == 0) cnt++;
        count_zero[j] = cnt;

<<<<<<< HEAD
        // générer UNE SEULE FOIS les pièces nécessaires, de haut vers bas
        for (i = 0; i < cnt; i++) {
            new_pieces[j][i] = 1 + rand() % 5;
        }
=======
        //  CORRECTION RANDOM : 1 à 5
        for(int i = 0; i < cnt; i++)
            plateau[i][j] = 1 + rand() % 5;
>>>>>>> 35d21df (optimisation de moteur_de_jeu)
    }
}
