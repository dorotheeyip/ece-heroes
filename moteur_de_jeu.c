#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define LINES 10    
#define COLUMN 15

// Active les couleurs ANSI sous Windows
void activer_couleurs() {
    system(" ");
    // PowerShell et CMD récents activent ANSI automatiquement
}

void afficher_tab_symboles(int tab1[LINES][COLUMN]) {
    for (int i = 0; i < LINES; i++) {
        for (int j = 0; j < COLUMN; j++) {
            char symbole;
            switch (tab1[i][j]) {
                case 1: symbole = '*'; break;
                case 2: symbole = '^'; break;
                case 3: symbole = '&'; break;
                case 4: symbole = '+'; break;
                case 5: symbole = '%'; break;
                case 0: symbole = ' '; break;
                default: symbole = '?'; break;
            }
            printf("%c ", symbole); // Chaque cellule occupe exactement 2 caractères
        }
        printf("\n");
    }
}

void combinaison_ligne(int tab1[LINES][COLUMN]);
void combinaison_colonne(int tab1[LINES][COLUMN]);
void combinaison_carre(int tab1[LINES][COLUMN]);
void renouvellement_case(int tab1[LINES][COLUMN]);
void afficher_tab(int tab1[LINES][COLUMN]);

int main(){
    int i, j;
    int tab1[LINES][COLUMN];
    srand(time(NULL));
    for (i=0; i<LINES; i++) {
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

void afficher_tab(int tab1[LINES][COLUMN]){
    for (int i = 0; i < LINES; i++) {
        for (int j = 0; j < COLUMN; j++) {
            printf("%d ", tab1[i][j]);
        }
        printf("\n");
    }
}

void combinaison_ligne(int tab1[LINES][COLUMN]){
    int i, j, item_supprime=-1; 
    for(i=0; i<LINES; i++){
        for(j=0; j<COLUMN-5; j++){
            if(tab1[i][j]==tab1[i][j+1] && tab1[i][j+1]==tab1[i][j+2] && tab1[i][j+2]==tab1[i][j+3] && tab1[i][j+3]==tab1[i][j+4] && tab1[i][j+4]==tab1[i][j+5]){              
                item_supprime=tab1[i][j];
            }
        }
        if(item_supprime!=-1){
            int k, l;
            for(k=0; k<LINES; k++){
                for(l=0; l<COLUMN; l++){
                    if(tab1[k][l]==item_supprime){
                        tab1[k][l]=0;
                    }
                }
            }
            item_supprime=-1;
        }
    }
    printf("\x1b[2J"); // nettoie l'écran
    printf("\x1b[H");  // place le curseur en haut
    afficher_tab_symboles(tab1);
}

void combinaison_colonne(int tab1[LINES][COLUMN]){
    int i, j, item_supprime=-1; 
    for(j=0; j<COLUMN; j++){
        for(i=0; i<LINES-5; i++){
            if(tab1[i][j]==tab1[i+1][j] && tab1[i+1][j]==tab1[i+2][j] && tab1[i+2][j]==tab1[i+3][j] && tab1[i+3][j]==tab1[i+4][j] && tab1[i+4][j]==tab1[i+5][j]){              
                item_supprime=tab1[i][j];
            }
        }
        if(item_supprime!=-1){
            int k, l;
            for(l=0; l<COLUMN; l++){
                for(k=0; k<LINES; k++){
                    if(tab1[k][l]==item_supprime){
                        tab1[k][l]=0;
                    }
                }
            }
            item_supprime=-1;
        }
    }
    printf("\x1b[2J"); // nettoie l'écran
    printf("\x1b[H");  // place le curseur en haut
    afficher_tab_symboles(tab1);
}

void combinaison_carre(int tab1[LINES][COLUMN]){
    int i, j, k, l;
    int cote_gauche, cote_droit, cote_haut, cote_bas;
    for(i=0; i<LINES-3; i++){
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
    printf("\x1b[2J"); // nettoie l'écran
    printf("\x1b[H");  // place le curseur en haut
    afficher_tab_symboles(tab1);
}

void renouvellement_case(int tab1[LINES][COLUMN]){
    int remplace;
    int i, j, k;

    /* faire tomber tous les zéros */
    do {
        remplace = 0;
        for (j = 0; j < COLUMN; j++) {
            for (i = LINES-1; i > 0; i--) {
                if (tab1[i][j] == 0 && tab1[i-1][j] != 0) {
                    tab1[i][j] = tab1[i-1][j];
                    tab1[i-1][j] = 0;
                    remplace = 1;
                }
            }
        }
    } while (remplace);

    /* remplir le haut */
    for (j = 0; j < COLUMN; j++) {
        for (i = 0; i < LINES; i++) {
            if (tab1[i][j] == 0) {
                tab1[i][j] = 1 + rand() % 5;
            }
        }
    }
}