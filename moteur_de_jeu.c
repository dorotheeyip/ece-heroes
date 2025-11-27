#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void combinaison_ligne(int tab1[10][15]);
void combinaison_colonne(int tab1[10][15]);
void combinaison_carre(int tab1[10][15]);
void renouvellement_case(int tab1[10][15]);

int main(){
    int i, j;
    int tab1[10][15];
    srand(time(NULL));
    for(i=0; i<10; i++){
        for(j=0; j<15; j++){
            tab1[i][j]=1 + rand() % (5);
        }
    }
    for(i=0; i<10; i++){
        for(j=0; j<15; j++){
            printf("%d ", tab1[i][j]);
        }
        printf("\n");
    }
    combinaison_ligne(tab1);
    combinaison_colonne(tab1);
    combinaison_carre(tab1);
    renouvellement_case(tab1);
    return 0;
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
                for(l=0; l<45; l++){
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
    int i, j, k;
    for(j=0; j<15; j++){
        for(i=9; i>=0; i--){
            if(tab1[i][j]==0){
                for(k=i; k>0; k--){
                    tab1[k][j]=tab1[k-1][j];
                }
                tab1[0][j]=1 + rand() % (5);
            }
        }
    }
}
