#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "extensions.h"

void bombe(int plateau[N][P], int ligne, int colonne){
    for(int i=ligne-2; i<ligne+3; i++){
        for(int j=colonne-2; j<colonne+3; j++){
            if (i>=0 && i<N && j>=0 && j<P) plateau[i][j]=0;
        }
    }
}

void fusee(int plateau[N][P], int ligne, int colonne, int orientation){
    if(orientation==1){ // verticale
        for(int i=0; i<N; i++){
            plateau[i][colonne]=0;
        }
    }
    else if(orientation==2){ // horizontale
        for(int j=0; j<P; j++){
        plateau[ligne][j]=0;
        } 
    }
}

void joker(int plateau[N][P], int ligne, int colonne, int type){ 
    plateau[ligne][colonne]=type;
}

void placer_itembonus(int plateau[N][P], int ligne, int colonne, int typebonus, int orientation, int type){
    if (typebonus==1){
        bombe(plateau, ligne, colonne);
    }
    else if (typebonus==2){
        fusee(plateau, ligne, colonne, orientation);
    }
    else if (typebonus==3){
        joker(plateau, ligne, colonne, type);
    }
}

int detecter_diagonale4(int plateau[N][P], int *ligne, int *colonne, int *orientation){
    for (int i=0; i<N-3; i++){
        for (int j=0; j<P; j++){
            if (j<P-3){
                if (plateau[i][j]==plateau[i+1][j+1] && plateau[i][j]==plateau[i+2][j+2] && plateau[i][j]==plateau[i+3][j+3]){
                    *ligne=i;
                    *colonne=j;
                    *orientation=1;
                    return 1;
                }
            }
            if (j>2){
                if (plateau[i][j]==plateau[i+1][j-1] && plateau[i+1][j-1]==plateau[i+2][j-2] && plateau[i][j]==plateau[i+3][j-3]){
                    *ligne=i;
                    *colonne=j;
                    *orientation=2;
                    return 1;
                }
            }
        }
    }
    return 0;
}

int detecter_carre2x2(int plateau[N][P], int *ligne, int *colonne){
    for (int i=0; i<N-1; i++){
        for (int j=0; j<P-1; j++){
            if(plateau[i][j]==plateau[i][j+1] && plateau[i][j]==plateau[i+1][j] && plateau[i][j]==plateau[i+1][j+1]){
                *ligne=i;
                *colonne=j;
                return 1;
            }
        }
    }
    return 0;
}

int detecter_ligne7(int plateau[N][P], int *ligne, int *colonne){
    for (int i=0; i<N; i++){
        for(int j=0; j<P; j++){
            if (j<P-7){
                if (plateau[i][j]==plateau[i][j+1] && plateau[i][j]==plateau[i][j+2] && plateau[i][j]==plateau[i][j+3] && plateau[i][j]==plateau[i][j+4] && plateau[i][j]==plateau[i][j+5] && plateau[i][j]==plateau[i][j+6]){
                    *ligne=i;
                    *colonne=j;
                    return 1;
                }
            }
            if (i<N-7){
                if (plateau[i][j]==plateau[i+1][j] && plateau[i][j]==plateau[i+2][j] && plateau[i][j]==plateau[i+3][j] && plateau[i][j]==plateau[i+4][j] && plateau[i][j]==plateau[i+5][j] && plateau[i][j]==plateau[i+6][j]){
                    *ligne=i;
                    *colonne=j;
                    return 1;
                }
            }
        }
    }
    return 0;
}

int detecter_figures_speciales(int plateau[N][P], int *ligne, int *colonne, int *orientation){
    if (detecter_diagonale4(plateau, ligne, colonne, orientation)) return 1;
    else if (detecter_carre2x2(plateau, ligne, colonne)) return 2;
    else if (detecter_ligne7(plateau, ligne, colonne)) return 3;
    return 0;
}

void effet_diagonale4(int plateau[N][P], int ligne, int colonne, int orientation){ //ajout orientation 1=vers droite 2=vers gauche
    int l=0 ,c=0;
    if (orientation==1){
        for(int i=0; l>=0 && c>=0; i++){
            l=ligne-i;
            c=colonne-i;
            plateau[l][c]=0;
        }
        for(int i=0; l<N && c<P; i++){
            l=ligne+i;
            c=colonne+i;
            plateau[l][c]=0;
        }
    }
    else if (orientation==2) {
        for(int i=0; l>=0 && c<P; i++){
            l=ligne-i;
            c=colonne+i;
            plateau[l][c]=0;
        }
        for(int i=0; l<N && c>=0; i++){
            l=ligne+i;
            c=colonne-i;
            plateau[l][c]=0;
        }
    }
}

void effet_carre2x2(int plateau[N][P], int ligne, int colonne){
    int l[16]={0,0,1,1,-1,-1,-1,-1,0,1,2,2,2,2,1,0};
    int c[16]={0,1,0,1,-1,0,1,2,2,2,2,1,0,-1,-1,-1};
    for(int i=0; i<16; i++){
        if (ligne+l[i]>=0 && ligne+l[i]<N && colonne+c[i]>=0 && colonne+c[i]<P) plateau[ligne+l[i]][colonne+c[i]]=0;
    }
}

void effet_ligne7(int plateau[N][P], int ligne, int colonne, int orientation){ 
    int special=plateau[ligne][colonne]+5;
    if (orientation==1) {
        for (int i=0; i<7; i++){
            plateau[ligne+i][colonne]=0;
        }
        plateau[ligne+3][colonne]=special; //verticale
    }
    else if (orientation==2) {
        for (int j=0; j<7; j++){
            plateau[ligne][colonne+j]=0;
        }
        plateau[ligne][colonne+3]=special; //horizontale
    }
}

void effet_item_ligne7(int plateau[N][P], int ligne, int colonne){
    fusee(plateau, ligne, colonne, 1);
    fusee(plateau, ligne, colonne, 2);
    effet_diagonale4(plateau, ligne, colonne, 1);
    effet_diagonale4(plateau, ligne, colonne, 2);
}

