#include <stdio.h>

void combinaison_ligne(int x, int y, int tab1[25][45]){
    int i, j, item_supprimé; 
    for(i=0; i<25; i++){
        if(tab1[i][j]==tab1[i][j+1] && tab1[i][j+1]==tab1[i][j+2] && tab1[i][j+2]==tab1[i][j+3] && tab1[i][j+3]==tab1[i][j+4] && tab1[i][j+4]==tab1[i][j+5]){              
            item_supprimé=tab1[i][j];
        }
        for(j=0; j<45; j++){
            if(tab1[i][j]==item_supprimé){
                tab1[i][j]=0;
            }
            if(tab1[i][j]==0){
                for(i; i>0; i--){
                    tab1[i][j]=tab1[i-1][j];
                }
                if(i==0){
                    tab1[i][j]= 1 + rand() % (5);
                }
            }
        }
    }
}

void combinaison_colonne(int x, int y, int tab1[25][45]){
    int i, j, item_supprimé; 
    for(j=0; j<45; j++){
        if(tab1[i][j]==tab1[i+1][j] && tab1[i+1][j]==tab1[i+2][j] && tab1[i+2][j]==tab1[i+3][j] && tab1[i+3][j]==tab1[i+4][j] && tab1[i+4][j]==tab1[i+5][j]){              
            item_supprimé=tab1[i][j];
        }
        for(i=0; i<25; i++){
            if(tab1[i][j]==item_supprimé){
                tab1[i][j]=0;
            }
            if(tab1[i][j]==0){
                for(j; j>0; j--){
                    tab1[i][j]=tab1[i-1][j];
                }
                if(i==0){
                    tab1[i][j]= 1 + rand() % (5);
                }
            }
        }
    }
}