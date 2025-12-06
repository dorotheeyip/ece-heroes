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
                case 2: symbole = '*'; couleur = "\x1b[31m"; break;
                case 3: symbole = '^'; couleur = "\x1b[32m"; break;
                case 4: symbole = '&'; couleur = "\x1b[33m"; break;
                case 5: symbole = '+'; couleur = "\x1b[34m"; break;
                case 6: symbole = '%'; couleur = "\x1b[35m"; break;
                case 0: symbole = ' '; couleur = "\x1b[0m";  break;
                default: symbole = '?'; couleur = "\x1b[0m"; break;
            }

            printf("%s%c\x1b[0m ", couleur, symbole);
        }

        printf("\n");
    }
}

int combinaison_ligne_6(int plateau[LINE][COLUMN]);
int combinaison_colonne_6(int plateau[LINE][COLUMN]);
int combinaison_croix(int plateau[LINE][COLUMN]);
int combinaison_carre(int plateau[LINE][COLUMN]);
int combinaison_ligne_4(int plateau[LINE][COLUMN]);
int combinaison_colonne_4(int plateau[LINE][COLUMN]);
void supprime_combin(int plateau[LINE][COLUMN]);
void renouvellement_case(int plateau[LINE][COLUMN]);
void afficher_tab(int plateau[LINE][COLUMN]);

int main(){
    int i, j;
    int plateau[LINE][COLUMN];
    srand(time(NULL));

    // Initialisation du plateau
    for (i = 0; i < LINE; i++) {
        for (j = 0; j < COLUMN; j++) {
            plateau[i][j] = 2 + rand() % 5;
        }
    }

    printf("\x1b[2J"); // efface la console
    afficher_tab_symboles(plateau);
    Sleep(500);

    // ---------------------------------------------------------
    // DÉTECTION DES COMBINAISONS
    // ---------------------------------------------------------
    int trouv = 0;
    if (combinaison_ligne_6(plateau)) trouv = 1;
    if (combinaison_colonne_6(plateau)) trouv = 1;
    if (combinaison_croix(plateau)) trouv = 1;
    if (combinaison_carre(plateau)) trouv = 1;
    if (combinaison_ligne_4(plateau)) trouv = 1;
    if (combinaison_colonne_4(plateau)) trouv = 1;

    // ---------------------------------------------------------
    // AFFICHAGE DES COMBINAISONS AVANT SUPPRESSION
    // ---------------------------------------------------------
    if (trouv) {
        printf("\x1b[H");
        afficher_tab_symboles(plateau);
        Sleep(800);   // Permet de voir les combinaisons trouvées
    }

    // ---------------------------------------------------------
    // SUPPRESSION DES COMBINAISONS
    // ---------------------------------------------------------
    supprime_combin(plateau);

    // ---------------------------------------------------------
    // AFFICHAGE DES VIDES AVANT DESCENTE
    // ---------------------------------------------------------
    printf("\x1b[H");
    afficher_tab_symboles(plateau);
    Sleep(800);  // Tu vois les cases vides

    // ---------------------------------------------------------
    // ANIMATION DE CHUTE + REMPLISSAGE
    // ---------------------------------------------------------
    renouvellement_case(plateau);

    // ---------------------------------------------------------
    // AFFICHAGE FINAL
    // ---------------------------------------------------------
    printf("\x1b[H");
    afficher_tab_symboles(plateau);
    Sleep(300);

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
            if(plateau[i][j]==plateau[i+1][j] && plateau[i+1][j]==plateau[i+2][j] && plateau[i+2][j]==plateau[i+3][j] && plateau[i+3][j]==plateau[i+4][j] && plateau[i+4][j]==plateau[i+5][j]){              
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
            if(centre==0){
                continue;
            }  
            if(centre==plateau[i-2][j] && centre==plateau[i-1][j] && centre==plateau[i+1][j] && centre==plateau[i+2][j] && centre==plateau[i][j-2] && centre==plateau[i][j-1] && centre==plateau[i][j+1] && centre==plateau[i][j+2]){
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
            if(plateau[i][j] == plateau[i+1][j] && plateau[i+1][j] == plateau[i+2][j] && plateau[i+2][j] == plateau[i+3][j] &&
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
            if(plateau[i][j]==plateau[i][j+1] && plateau[i][j+1]==plateau[i][j+2] && plateau[i][j+2]==plateau[i][j+3]){
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
            if(plateau[i][j]==plateau[i+1][j] && plateau[i+1][j]==plateau[i+2][j] && plateau[i+2][j]==plateau[i+3][j]){
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
                if(ligne_6==plateau[i][j+1] && ligne_6==plateau[i][j+2] && ligne_6==plateau[i][j+3] && ligne_6==plateau[i][j+4] && ligne_6==plateau[i][j+5]){
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
                if(colonne_6==plateau[i+1][j] && colonne_6==plateau[i+2][j] && colonne_6==plateau[i+3][j] && colonne_6==plateau[i+4][j] && colonne_6==plateau[i+5][j]){
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
                if(centre==plateau[i-2][j] && centre==plateau[i-1][j] && centre==plateau[i+1][j] && centre==plateau[i+2][j] && centre==plateau[i][j-2] && centre==plateau[i][j-1] && centre==plateau[i][j+1] && centre==plateau[i][j+2]){
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
                if(plateau[i][j] == plateau[i+1][j] && plateau[i+1][j] == plateau[i+2][j] && plateau[i+2][j] == plateau[i+3][j] &&
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
                if(ligne_4==plateau[i][j+1] && ligne_4==plateau[i][j+2] && ligne_4==plateau[i][j+3]){
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
                if(colonne_4==plateau[i+1][j] && colonne_4==plateau[i+2][j] && colonne_4==plateau[i+3][j]){
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

    // --------------------------------------------------------
    // 1) MONTRER LA DISPARITION (les zéros restent visibles)
    // --------------------------------------------------------
    printf("\x1b[H");
    afficher_tab_symboles(plateau);
    Sleep(800);


    // --------------------------------------------------------
    // 2) GRAVITÉ ANIMÉE — DESCENTE CASE PAR CASE
    // --------------------------------------------------------
    int movement;

    do {
        movement = 0;

        for (j = 0; j < COLUMN; j++) {

            for (i = LINE - 1; i > 0; i--) {

                if (plateau[i][j] == 0 && plateau[i - 1][j] != 0) {

                    plateau[i][j] = plateau[i - 1][j];
                    plateau[i - 1][j] = 0;
                    movement = 1;

                    printf("\x1b[H");
                    afficher_tab_symboles(plateau);
                    Sleep(120);
                }
            }
        }

    } while (movement);


    // --------------------------------------------------------
    // 3) REMPLISSAGE DES ZÉROS (ANIMATION, CORRIGÉ)
    //    → on remplit de BAS en HAUT pour éviter les trous
    // --------------------------------------------------------
    for (j = 0; j < COLUMN; j++) {

        for (i = LINE - 1; i >= 0; i--) {

            if (plateau[i][j] == 0) {

                int piece = 2 + rand() % 5;

                // La pièce tombe depuis au-dessus de la grille
                for (int h = -1; h <= i; h++) {

                    // efface l'ancienne position
                    if (h > 0)
                        plateau[h - 1][j] = 0;

                    // dessine la pièce si dans la grille
                    if (h >= 0)
                        plateau[h][j] = piece;

                    printf("\x1b[H");
                    afficher_tab_symboles(plateau);
                    Sleep(120);

                    // efface la trace intermédiaire
                    if (h >= 0 && h != i)
                        plateau[h][j] = 0;
                }

                plateau[i][j] = piece; // position finale
            }
        }
    }


    // --------------------------------------------------------
    // 4) AFFICHAGE FINAL
    // --------------------------------------------------------
    printf("\x1b[H");
    afficher_tab_symboles(plateau);
    Sleep(200);
}
