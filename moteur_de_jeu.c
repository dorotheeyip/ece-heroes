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

void afficher_tab_symboles(int tab1[LINE][COLUMN]) {

    printf("\x1b[H");   // revient en haut sans effacer tout
                        // garde un écran stable 10×15

    for (int i = 0; i < LINE; i++) {
        for (int j = 0; j < COLUMN; j++) {

            char symbole;
            char *couleur;

            switch (tab1[i][j]) {
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

void combinaison_ligne(int tab1[LINE][COLUMN]);
void combinaison_colonne(int tab1[LINE][COLUMN]);
void combinaison_carre(int tab1[LINE][COLUMN]);
void renouvellement_case(int tab1[LINE][COLUMN]);
void afficher_tab(int tab1[LINE][COLUMN]);

int main(){
    int i, j;
    int tab1[LINE][COLUMN];
    srand(time(NULL));
    for (i=0; i<LINE; i++) {
        for (j=0; j<COLUMN; j++) {
            tab1[i][j] = 1 + rand() % 5;
        }
    }
    printf("\x1b[2J"); // efface tout
    afficher_tab_symboles(tab1);
    Sleep(500);

    combinaison_ligne(tab1);
    renouvellement_case(tab1);
    printf("\x1b[H");
    afficher_tab_symboles(tab1);
    Sleep(200);

    combinaison_colonne(tab1);
    renouvellement_case(tab1);
    printf("\x1b[H");
    afficher_tab_symboles(tab1);
    Sleep(200);

    combinaison_carre(tab1);
    renouvellement_case(tab1);
    printf("\x1b[H");
    afficher_tab_symboles(tab1);
    Sleep(200);

    return 0;
}

void afficher_tab(int tab1[LINE][COLUMN]){
    for (int i = 0; i < LINE; i++) {
        for (int j = 0; j < COLUMN; j++) {
            printf("%d ", tab1[i][j]);
        }
        printf("\n");
    }
}

void combinaison_ligne(int tab1[LINE][COLUMN]){
    int i, j, k; 
    for(i=0; i<LINE; i++){
        for(j=0; j<COLUMN-5; j++){
            if(tab1[i][j]==tab1[i][j+1] && tab1[i][j+1]==tab1[i][j+2] && tab1[i][j+2]==tab1[i][j+3] && tab1[i][j+3]==tab1[i][j+4] && tab1[i][j+4]==tab1[i][j+5]){              
                for(k=0; k<6; k++){
                    tab1[i][j+k]=0;
                }
            }
        }
       
    }
    printf("\x1b[H");  // place le curseur en haut
    afficher_tab_symboles(tab1);
}

void combinaison_colonne(int tab1[LINE][COLUMN]){
    int i, j, k; 
    for(j=0; j<COLUMN; j++){
        for(i=0; i<LINE-5; i++){
            if(tab1[i][j]==tab1[i+1][j] && tab1[i+1][j]==tab1[i+2][j] && tab1[i+2][j]==tab1[i+3][j] && tab1[i+3][j]==tab1[i+4][j] && tab1[i+4][j]==tab1[i+5][j]){              
                for(k=0; k<6; k++){
                    tab1[i][j+k]=0;
                }
            }
        }
    printf("\x1b[H");  // place le curseur en haut
    afficher_tab_symboles(tab1);
    }
}

void combinaison_carre(int tab1[LINE][COLUMN]){
    int i, j, k, l;
    int cote_gauche, cote_droit, cote_haut, cote_bas;
    for(i=0; i<LINE-3; i++){
        for(j=0; j<COLUMN-3; j++){
            if(tab1[i][j] == tab1[i+1][j] && tab1[i+1][j] == tab1[i+2][j] && tab1[i+2][j] == tab1[i+3][j] &&
               tab1[i][j+3] == tab1[i+1][j+3] && tab1[i+1][j+3] == tab1[i+2][j+3] && tab1[i+2][j+3] == tab1[i+3][j+3] &&
               tab1[i][j] == tab1[i][j+1] && tab1[i][j+1] == tab1[i][j+2] && tab1[i][j+2] == tab1[i][j+3] &&
               tab1[i+3][j] == tab1[i+3][j+1] && tab1[i+3][j+1] == tab1[i+3][j+2] && tab1[i+3][j+2] == tab1[i+3][j+3]){
                cote_gauche=tab1[i][j];
                cote_droit=tab1[i][j+3];
                cote_haut=tab1[i][j];
                cote_bas=tab1[i+3][j];
                for(k=0; k<4; k++){
                    tab1[i+k][j]=0;
                    tab1[i+k][j+3]=0;
                    tab1[i][j+k]=0;
                    tab1[i+3][j+k]=0;
                }
                for(k=i+1; k<i+3; k++){
                    for(l=j+1; l<j+3; l++){
                        if(tab1[k][l]==cote_gauche || tab1[k][l]==cote_droit || tab1[k][l]==cote_haut || tab1[k][l]==cote_bas){
                            tab1[k][l]=0;
                        }
                    }
                }
            }
        }
    }
    printf("\x1b[H");  // place le curseur en haut
    afficher_tab_symboles(tab1);
}

void afficher_et_pause(int tab1[LINE][COLUMN], int temps) {
    printf("\x1b[H");
    afficher_tab_symboles(tab1);
    Sleep(temps);
}

void renouvellement_case(int tab1[LINE][COLUMN]) {
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
                if (tab1[i][j] == 0 && tab1[i - 1][j] != 0) {

                    // ÉCHANGE
                    tab1[i][j] = tab1[i - 1][j];
                    tab1[i - 1][j] = 0;
                    remplace = 1;

                    // ANIMATION : afficher après chaque mouvement
                    printf("\x1b[H");
                    afficher_tab_symboles(tab1);
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

            if (tab1[i][j] == 0) {
                int nouvelle_piece = 1 + rand() % 5;

                // Chute animée depuis "au-dessus"
                for (int h = 0; h <= i; h++) {

                    // effacer la case temporaire précédente
                    if (h > 0) tab1[h - 1][j] = 0;

                    // placer temporairement la pièce
                    tab1[h][j] = nouvelle_piece;

                    // afficher
                    printf("\x1b[H");
                    afficher_tab_symboles(tab1);
                    Sleep(30);

                    // si pas encore arrivée → la retirer avant la prochaine frame
                    if (h != i)
                        tab1[h][j] = 0;
                }

                // finalement la placer
                tab1[i][j] = nouvelle_piece;
            }
        }
    }

    // AFFICHAGE FINAL
    printf("\x1b[H");
    afficher_tab_symboles(tab1);
}