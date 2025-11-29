#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define LINE 7   
#define COLUMN 10

// Active les couleurs ANSI sous Windows
void activer_couleurs() {
    system(" ");
    // PowerShell et CMD récents activent ANSI automatiquement
}

void afficher_tab_symboles(int plateau[LINE][COLUMN]) {

    printf("\x1b[H");   // revient en haut sans effacer tout
                        // garde un écran stable 10×15

    for (int i = 0; i < LINE; i++) {
        for (int j = 0; j < COLUMN; j++) {

            char symbole;
            char *couleur;

            switch (plateau[i][j]) {
                case 1: symbole = '*'; couleur = "\x1b[31m"; break;
                case 2: symbole = '^'; couleur = "\x1b[32m"; break;
                case 3: symbole = '&'; couleur = "\x1b[33m"; break;
                case 4: symbole = '+'; couleur = "\x1b[34m"; break;
                case 5: symbole = '%'; couleur = "\x1b[35m"; break;
                case 0: symbole = ' '; couleur = "\x1b[0m";  break;
                default: symbole = '?'; couleur = "\x1b[0m"; break;
            }

            printf("%s%c\x1b[0m ", couleur, symbole);
        }

        printf("\n");
    }
}

void combinaison_ligne_6(int plateau[LINE][COLUMN]);
void combinaison_colonne_6(int plateau[LINE][COLUMN]);
void combinaison_carre(int plateau[LINE][COLUMN]);
void renouvellement_case(int plateau[LINE][COLUMN]);
void afficher_tab(int plateau[LINE][COLUMN]);

int main(){
    int i, j;
    int plateau[LINE][COLUMN];
    srand(time(NULL));
    for (i=0; i<LINE; i++) {
        for (j=0; j<COLUMN; j++) {
            plateau[i][j] = 1 + rand() % 5;
        }
    }
    printf("\x1b[2J"); // efface tout
    afficher_tab_symboles(plateau);
    Sleep(500);

    combinaison_ligne_6(plateau);
    renouvellement_case(plateau);
    printf("\x1b[H");
    afficher_tab_symboles(plateau);
    Sleep(200);

    combinaison_colonne_6(plateau);
    renouvellement_case(plateau);
    printf("\x1b[H");
    afficher_tab_symboles(plateau);
    Sleep(200);

    combinaison_carre(plateau);
    renouvellement_case(plateau);
    printf("\x1b[H");
    afficher_tab_symboles(plateau);
    Sleep(200);

    return 0;
}

void afficher_tab(int plateau[LINE][COLUMN]){
    for (int i = 0; i < LINE; i++) {
        for (int j = 0; j < COLUMN; j++) {
            printf("%d ", plateau[i][j]);
        }
        printf("\n");
    }
}

void combinaison_ligne_6(int plateau[LINE][COLUMN]){
    int i, j, k; 
    for(i=0; i<LINE; i++){
        for(j=0; j<COLUMN-5; j++){
            if(plateau[i][j]==plateau[i][j+1] && plateau[i][j+1]==plateau[i][j+2] && plateau[i][j+2]==plateau[i][j+3] && plateau[i][j+3]==plateau[i][j+4] && plateau[i][j+4]==plateau[i][j+5]){              
                for(k=0; k<6; k++){
                    plateau[i][j+k]=0;
                }
            }
        }
       
    }
    printf("\x1b[H");  // place le curseur en haut
    afficher_tab_symboles(plateau);
}

void combinaison_colonne_6(int plateau[LINE][COLUMN]){
    int i, j, k; 
    for(j=0; j<COLUMN; j++){
        for(i=0; i<LINE-5; i++){
            if(plateau[i][j]==plateau[i+1][j] && plateau[i+1][j]==plateau[i+2][j] && plateau[i+2][j]==plateau[i+3][j] && plateau[i+3][j]==plateau[i+4][j] && plateau[i+4][j]==plateau[i+5][j]){              
                for(k=0; k<6; k++){
                    plateau[i][j+k]=0;
                }
            }
        }
    printf("\x1b[H");  // place le curseur en haut
    afficher_tab_symboles(plateau);
    }
}

void combinaison_carre(int plateau[LINE][COLUMN]){
    int i, j, k, l;
    int cote_gauche, cote_droit, cote_haut, cote_bas;
    for(i=0; i<LINE-3; i++){
        for(j=0; j<COLUMN-3; j++){
            if(plateau[i][j] == plateau[i+1][j] && plateau[i+1][j] == plateau[i+2][j] && plateau[i+2][j] == plateau[i+3][j] &&
               plateau[i][j+3] == plateau[i+1][j+3] && plateau[i+1][j+3] == plateau[i+2][j+3] && plateau[i+2][j+3] == plateau[i+3][j+3] &&
               plateau[i][j] == plateau[i][j+1] && plateau[i][j+1] == plateau[i][j+2] && plateau[i][j+2] == plateau[i][j+3] &&
               plateau[i+3][j] == plateau[i+3][j+1] && plateau[i+3][j+1] == plateau[i+3][j+2] && plateau[i+3][j+2] == plateau[i+3][j+3]){
                cote_gauche=plateau[i][j];
                cote_droit=plateau[i][j+3];
                cote_haut=plateau[i][j];
                cote_bas=plateau[i+3][j];
                for(k=0; k<4; k++){
                    plateau[i+k][j]=0;
                    plateau[i+k][j+3]=0;
                    plateau[i][j+k]=0;
                    plateau[i+3][j+k]=0;
                }
                for(k=i+1; k<i+3; k++){
                    for(l=j+1; l<j+3; l++){
                        if(plateau[k][l]==cote_gauche || plateau[k][l]==cote_droit || plateau[k][l]==cote_haut || plateau[k][l]==cote_bas){
                            plateau[k][l]=0;
                        }
                    }
                }
            }
        }
    }
    printf("\x1b[H");  // place le curseur en haut
    afficher_tab_symboles(plateau);
}

void afficher_et_pause(int plateau[LINE][COLUMN], int temps) {
    printf("\x1b[H");
    afficher_tab_symboles(plateau);
    Sleep(temps);
}

void renouvellement_case(int plateau[LINE][COLUMN]) {
    int remplace;
    int i, j;

    // -------------------------------------------
    // 1) ANIMATION DE LA CHUTE DES PIÈCES EXISTANTES
    // -------------------------------------------

    do {
        remplace = 0;

        for (j = 0; j < COLUMN; j++) {
            for (i = LINE - 1; i > 0; i--) {

                // Une pièce peut descendre d'une case
                if (plateau[i][j] == 0 && plateau[i - 1][j] != 0) {

                    // ÉCHANGE
                    plateau[i][j] = plateau[i - 1][j];
                    plateau[i - 1][j] = 0;
                    remplace = 1;

                    // ANIMATION : afficher après chaque mouvement
                    printf("\x1b[H");
                    afficher_tab_symboles(plateau);
                    Sleep(40);  // vitesse de chute
                }
            }
        }

    } while (remplace);


    // -------------------------------------------
    // 2) ANIMATION DES NOUVELLES PIÈCES QUI ARRIVENT DU HAUT
    // -------------------------------------------

    for (j = 0; j < COLUMN; j++) {

        for (i = 0; i < LINE; i++) {

            if (plateau[i][j] == 0) {
                int nouvelle_piece = 1 + rand() % 5;

                // Chute animée depuis "au-dessus"
                for (int h = 0; h <= i; h++) {

                    // effacer la case temporaire précédente
                    if (h > 0) plateau[h - 1][j] = 0;

                    // placer temporairement la pièce
                    plateau[h][j] = nouvelle_piece;

                    // afficher
                    printf("\x1b[H");
                    afficher_tab_symboles(plateau);
                    Sleep(30);

                    // si pas encore arrivée → la retirer avant la prochaine frame
                    if (h != i)
                        plateau[h][j] = 0;
                }

                // finalement la placer
                plateau[i][j] = nouvelle_piece;
            }
        }
    }

    // AFFICHAGE FINAL
    printf("\x1b[H");
    afficher_tab_symboles(plateau);
}



void activer_couleurs(){
    // Active les couleurs des symboles ANSI sous Windows
}

void afficher_tab_symboles(int plateau[LINE][COLUMN]){
    // Remplace les chiffres dans le plateau par leur symbole associé
}

void afficher_tab(int plateau[LINE][COLUMN]){
    // Affiche le tableau après les modifications
}

void combinaison_ligne_6(int plateau[LINE][COLUMN]){
    // Identifie les combinaisons de lignes de 6 items et les supprime
}
