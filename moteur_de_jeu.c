#include <stdio.h>

void combinaison_ligne(int x, int y, int tab1[25][45]){
    int i, j, item_supprime; 
    for(i=0; i<25; i++){
        if(tab1[i][j]==tab1[i][j+1] && tab1[i][j+1]==tab1[i][j+2] && tab1[i][j+2]==tab1[i][j+3] && tab1[i][j+3]==tab1[i][j+4] && tab1[i][j+4]==tab1[i][j+5]){              
            item_supprime=tab1[i][j];
        }
        for(j=0; j<45; j++){
            if(tab1[i][j]==item_supprime){
                tab1[i][j]=0;
            }
        }
    }
}

void combinaison_colonne(int x, int y, int tab1[25][45]){
    int i, j, item_supprime; 
    for(j=0; j<45; j++){
        if(tab1[i][j]==tab1[i+1][j] && tab1[i+1][j]==tab1[i+2][j] && tab1[i+2][j]==tab1[i+3][j] && tab1[i+3][j]==tab1[i+4][j] && tab1[i+4][j]==tab1[i+5][j]){              
            item_supprime=tab1[i][j];
        }
        for(i=0; i<25; i++){
            if(tab1[i][j]==item_supprime){
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

void combinaison_carre(int x, int y, int tab1[25][45]){
    int i, j, item_supprime;
    for(i=0; i<25; i++){
        if(tab1[i][j]==tab1[i+1][j] && tab1[i+1][j]==tab1[i+2][j] && tab1[i+2][j]==tab1[i+3][j]){
            for(j=0; j<45; j++){
                if(tab1[i][j]==tab1[i][j+1] && tab1[i][j+1]==tab1[i][j+2] && tab1[i][j+2]==tab1[i][j+3]){
                    if(tab1[i+1][j+1]==tab1[i][j]){
                        tab1[i+1][j+1]=item_supprime;
                    }
                    if(tab1[i+1][j+2]==tab1[i][j]){
                        tab1[i+1][j+2]=item_supprime;
                    }
                    if(tab1[i+2][j+1]==tab1[i][j]){
                        tab1[i+2][j+1]=item_supprime;
                    }
                    if(tab1[i+2][j+2]==tab1[i][j]){
                        tab1[i+2][j+2]=item_supprime;
                    }
                    tab1[i][j]=item_supprime;
                    tab1[i+1][j]=item_supprime;
                    tab1[i+2][j]=item_supprime;
                    tab1[i+3][j]=item_supprime;
                    tab1[i][j]=item_supprime;
                    tab1[i][j+1]=item_supprime;
                    tab1[i][j+2]=item_supprime;
                    tab1[i][j+3]=item_supprime;
                }
                if(tab1[i][j]==item_supprime){
                    tab1[i][j]=0;
                }
            }
        }
    }
}

void renouvellement_case(int x, int y, int tab1[25][45]){
    int i, j;
    for(i=0; i<25; i++){
        for(j=0; j<45; j++){
            if(tab1[i][j]==0){
                for(i=25; i>0; i--){
                    tab1[i][j]=tab1[i-1][j];
                }
                if(i==0){
                    tab1[i][j]=1 + rand() % (5);
                }
            }
        }
    }
}