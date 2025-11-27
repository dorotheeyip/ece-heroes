#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Active les couleurs ANSI sous Windows
void activer_couleurs() {
    system(" ");
    // PowerShell et CMD récents activent ANSI automatiquement
}

void afficher_tab_symboles(int tab1[10][15]) {
    activer_couleurs();

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 15; j++) {

            switch (tab1[i][j]) {
                case 1: printf("\x1b[31m*\x1b[0m "); break; // rouge
                case 2: printf("\x1b[32m^\x1b[0m "); break; // vert
                case 3: printf("\x1b[33m&\x1b[0m "); break; // jaune
                case 4: printf("\x1b[34m+\x1b[0m "); break; // bleu
                case 5: printf("\x1b[35m%%\x1b[0m "); break; // magenta (%% pour afficher %)
                case 0: printf("  "); break;               // vide après suppression
                default: printf("? "); break;
            }

        }
        printf("\n");
    }
}

void combinaison_ligne(int tab1[10][15]);
void combinaison_colonne(int tab1[10][15]);
void combinaison_carre(int tab1[10][15]);
void renouvellement_case(int tab1[10][15]);
void afficher_tab(int tab1[10][15]);

int main(){
    int i, j;
    int tab1[10][15];
    srand(time(NULL));
    for (i=0; i<10; i++) {
        for (j=0; j<15; j++) {
            tab1[i][j] = 1 + rand() % 5;
        }
    }
    printf("\nTABLEAU INITIAL :\n");
    afficher_tab_symboles(tab1);
    combinaison_ligne(tab1);
    renouvellement_case(tab1);
    printf("\nAPRÈS COMBINAISON LIGNE :\n");
    afficher_tab_symboles(tab1);
    combinaison_colonne(tab1);
    renouvellement_case(tab1);
    printf("\nAPRÈS COMBINAISON COLONNE :\n");
    afficher_tab_symboles(tab1);
    combinaison_carre(tab1);
    renouvellement_case(tab1);
    printf("\nAPRÈS COMBINAISON CARRE :\n");
    afficher_tab_symboles(tab1);
    renouvellement_case(tab1);
    printf("\nAPRÈS RENOUVELLEMENT :\n");
    afficher_tab_symboles(tab1);

    return 0;
}

void afficher_tab(int tab1[10][15]){
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 15; j++) {
            printf("%d ", tab1[i][j]);
        }
        printf("\n");
    }
}

void combinaison_ligne(int tab1[10][15]){
    int i, j, item_supprime=-1; 
    for(i=0; i<10; i++){
        for(j=0; j<15-5; j++){
            if(tab1[i][j]==tab1[i][j+1] && tab1[i][j+1]==tab1[i][j+2] && tab1[i][j+2]==tab1[i][j+3] && tab1[i][j+3]==tab1[i][j+4] && tab1[i][j+4]==tab1[i][j+5]){              
                item_supprime=tab1[i][j];
            }
        }
        if(item_supprime!=-1){
            int k, l;
            for(k=0; k<10; k++){
                for(l=0; l<15; l++){
                    if(tab1[k][l]==item_supprime){
                        tab1[k][l]=0;
                    }
                }
            }
            item_supprime=-1;
        }
    }
}

void combinaison_colonne(int tab1[10][15]){
    int i, j, item_supprime=-1; 
    for(j=0; j<15; j++){
        for(i=0; i<10-5; i++){
            if(tab1[i][j]==tab1[i+1][j] && tab1[i+1][j]==tab1[i+2][j] && tab1[i+2][j]==tab1[i+3][j] && tab1[i+3][j]==tab1[i+4][j] && tab1[i+4][j]==tab1[i+5][j]){              
                item_supprime=tab1[i][j];
            }
        }
        if(item_supprime!=-1){
            int k, l;
            for(l=0; l<15; l++){
                for(k=0; k<10; k++){
                    if(tab1[k][l]==item_supprime){
                        tab1[k][l]=0;
                    }
                }
            }
            item_supprime=-1;
        }
    }
}

void combinaison_carre(int tab1[10][15]){
    int i, j, k, l;
    int cote_gauche, cote_droit, cote_haut, cote_bas;
    for(i=0; i<10-3; i++){
        for(j=0; j<15-3; j++){
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
}

void renouvellement_case(int tab1[10][15]){
    int remplace;
    int i, j, k;

    /* faire tomber tous les zéros */
    do {
        remplace = 0;
        for (j = 0; j < 15; j++) {
            for (i = 9; i > 0; i--) {
                if (tab1[i][j] == 0 && tab1[i-1][j] != 0) {
                    tab1[i][j] = tab1[i-1][j];
                    tab1[i-1][j] = 0;
                    remplace = 1;
                }
            }
        }
    } while (remplace);

    /* remplir le haut */
    for (j = 0; j < 15; j++) {
        for (i = 0; i < 10; i++) {
            if (tab1[i][j] == 0) {
                tab1[i][j] = 1 + rand() % 5;
            }
        }
    }
}