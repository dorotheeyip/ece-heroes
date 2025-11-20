#include <stdio.h>
#include <stdlib.h>

int main(){
    int i, j;
    int tab1[25][45];
    for(i=0; i<25; i++){
        for(j=0; j<45; j++){
            tab1[i][j]=1 + rand() % (5);
            printf("%d ", tab1[i][j]);
        }
        printf("\n");
    }
    return 0;
}
void combinaison_ligne(int x, int y, int tab1[25][45]){
    int i, j, item_supprime=-1; 
    for(i=0; i<25; i++){
        for(j=0; j<45-5; j++){
            if(tab1[i][j]==tab1[i][j+1] && tab1[i][j+1]==tab1[i][j+2] && tab1[i][j+2]==tab1[i][j+3] && tab1[i][j+3]==tab1[i][j+4] && tab1[i][j+4]==tab1[i][j+5]){              
                item_supprime=tab1[i][j];
            }
        }
        if(item_supprime!=-1){
            int k, l;
            for(k=0; k<25; k++){
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

void combinaison_colonne(int x, int y, int tab1[25][45]){
    int i, j, item_supprime=-1; 
    for(j=0; j<45; j++){
        for(i=0; i<25-5; i++){
            if(tab1[i][j]==tab1[i+1][j] && tab1[i+1][j]==tab1[i+2][j] && tab1[i+2][j]==tab1[i+3][j] && tab1[i+3][j]==tab1[i+4][j] && tab1[i+4][j]==tab1[i+5][j]){              
                item_supprime=tab1[i][j];
            }
        }
        if(item_supprime!=-1){
            int k, l;
            for(l=0; l<45; l++){
                for(k=0; k<25; k++){
                    if(tab1[k][l]==item_supprime){
                        tab1[k][l]=0;
                    }
                }
            }
            item_supprime=-1;
        }
    }
}

void combinaison_carre(int x, int y, int tab1[25][45]){
    int i, j, k, l;
    int cote_gauche, cote_droit, cote_haut, cote_bas;
    for(i=0; i<25-3; i++){
        for(j=0; j<45-3; j++){
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

void renouvellement_case(int x, int y, int tab1[25][45]){
    int i, j, k;
    for(j=0; j<45; j++){
        for(i=24; i>=0; i--){
            if(tab1[i][j]==0){
                for(k=i; k>0; k--){
                    tab1[k][j]=tab1[k-1][j];
                }
                tab1[0][j]=1 + rand() % (5);
            }
        }
    }
}
