#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "extensions.h"

void supprimer_element(int plateau[LINE][COLUMN], int i, int j, int compteur_item[6]){
    if (plateau[i][j]>=1 && plateau[i][j]<=5) compteur_item[plateau[i][j]]++;
    plateau[i][j]=0;
}

void bombe(int plateau[LINE][COLUMN], int ligne, int colonne, int compteur_item[6]){
    for(int i=ligne-2; i<ligne+3; i++){
        for(int j=colonne-2; j<colonne+3; j++){
            if (i>=0 && i<LINE && j>=0 && j<COLUMN) supprimer_element(plateau, i, j, compteur_item);
        }
    }
}

void fusee(int plateau[LINE][COLUMN], int ligne, int colonne, int orientation, int compteur_item[6]){
    if(orientation==1){ // verticale
        for(int i=0; i<LINE; i++){
            supprimer_element(plateau, i, colonne, compteur_item);
        }
    }
    else if(orientation==2){ // horizontale
        for(int j=0; j<COLUMN; j++){
        supprimer_element(plateau, ligne, j, compteur_item);
        } 
    }
}

void joker(int plateau[LINE][COLUMN], int ligne, int colonne, int type){ 
    plateau[ligne][colonne]=type;
}

void placer_itembonus(int plateau[LINE][COLUMN], int ligne, int colonne, int typebonus, int orientation, int type, int compteur_item[6]){
    if (typebonus==1){
        bombe(plateau, ligne, colonne, compteur_item);
    }
    else if (typebonus==2){
        fusee(plateau, ligne, colonne, orientation, compteur_item);
    }
    else if (typebonus==3){
        joker(plateau, ligne, colonne, type);
    }
}

int detecter_diagonale4(int plateau[LINE][COLUMN], int *ligne, int *colonne, int *orientation){
    for (int i=0; i<LINE-3; i++){
        for (int j=0; j<COLUMN; j++){
            if (j<COLUMN-3){
                if (plateau[i][j]!= 0 && plateau[i][j]==plateau[i+1][j+1] && plateau[i][j]==plateau[i+2][j+2] && plateau[i][j]==plateau[i+3][j+3]){
                    *ligne=i;
                    *colonne=j;
                    *orientation=1;
                    return 1;
                }
            }
            if (j>2){
                if (plateau[i][j]!= 0 && plateau[i][j]==plateau[i+1][j-1] && plateau[i+1][j-1]==plateau[i+2][j-2] && plateau[i][j]==plateau[i+3][j-3]){
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

int detecter_carre2x2(int plateau[LINE][COLUMN], int *ligne, int *colonne){
    for (int i=0; i<LINE-1; i++){
        for (int j=0; j<COLUMN-1; j++){
            if(plateau[i][j]!= 0 && plateau[i][j]==plateau[i][j+1] && plateau[i][j]==plateau[i+1][j] && plateau[i][j]==plateau[i+1][j+1]){
                *ligne=i;
                *colonne=j;
                return 1;
            }
        }
    }
    return 0;
}

int detecter_ligne7(int plateau[LINE][COLUMN], int *ligne, int *colonne){
    for (int i=0; i<LINE; i++){
        for(int j=0; j<COLUMN; j++){
            if (j<COLUMN-7){
                if (plateau[i][j]!= 0 && plateau[i][j]==plateau[i][j+1] && plateau[i][j]==plateau[i][j+2] && plateau[i][j]==plateau[i][j+3] && plateau[i][j]==plateau[i][j+4] && plateau[i][j]==plateau[i][j+5] && plateau[i][j]==plateau[i][j+6]){
                    *ligne=i;
                    *colonne=j;
                    return 1;
                }
            }
            if (i<LINE-7){
                if (plateau[i][j]!= 0 && plateau[i][j]==plateau[i+1][j] && plateau[i][j]==plateau[i+2][j] && plateau[i][j]==plateau[i+3][j] && plateau[i][j]==plateau[i+4][j] && plateau[i][j]==plateau[i+5][j] && plateau[i][j]==plateau[i+6][j]){
                    *ligne=i;
                    *colonne=j;
                    return 1;
                }
            }
        }
    }
    return 0;
}

int detecter_figures_speciales(int plateau[LINE][COLUMN], int *ligne, int *colonne, int *orientation){
    if (detecter_diagonale4(plateau, ligne, colonne, orientation)) return 1;
    else if (detecter_carre2x2(plateau, ligne, colonne)) return 2;
    else if (detecter_ligne7(plateau, ligne, colonne)) return 3;
    return 0;
}

void effet_diagonale4(int plateau[LINE][COLUMN], int ligne, int colonne, int orientation, int compteur_item[6]){ //ajout orientation 1=vers droite 2=vers gauche
    int l=0 ,c=0;
    if (orientation==1){
        for(int i=0; l>=0 && c>=0; i++){
            l=ligne-i;
            c=colonne-i;
            supprimer_element(plateau, l, c, compteur_item);
        }
        for(int i=0; l<LINE && c<COLUMN; i++){
            l=ligne+i;
            c=colonne+i;
            supprimer_element(plateau, l, c, compteur_item);
        }
    }
    else if (orientation==2) {
        for(int i=0; l>=0 && c<COLUMN; i++){
            l=ligne-i;
            c=colonne+i;
            supprimer_element(plateau, l, c, compteur_item);
        }
        for(int i=0; l<LINE && c>=0; i++){
            l=ligne+i;
            c=colonne-i;
            supprimer_element(plateau, l, c, compteur_item);
        }
    }
}

void effet_carre2x2(int plateau[LINE][COLUMN], int ligne, int colonne, int compteur_item[6]){
    int l[16]={0,0,1,1,-1,-1,-1,-1,0,1,2,2,2,2,1,0};
    int c[16]={0,1,0,1,-1,0,1,2,2,2,2,1,0,-1,-1,-1};
    for(int i=0; i<16; i++){
        if (ligne+l[i]>=0 && ligne+l[i]<LINE && colonne+c[i]>=0 && colonne+c[i]<COLUMN) supprimer_element(plateau, ligne+l[i], colonne+c[i], compteur_item);
    }
}

void effet_ligne7(int plateau[LINE][COLUMN], int ligne, int colonne, int orientation, int compteur_item[6]){ 
    int special=plateau[ligne][colonne]+5;
    if (orientation==1) {
        for (int i=0; i<7; i++){
            supprimer_element(plateau, ligne+i, colonne, compteur_item);
        }
        plateau[ligne+3][colonne]=special; //verticale
    }
    else if (orientation==2) {
        for (int j=0; j<7; j++){
            supprimer_element(plateau, ligne, colonne+j, compteur_item);
        }
        plateau[ligne][colonne+3]=special; //horizontale
    }
}

void effet_item_ligne7(int plateau[LINE][COLUMN], int ligne, int colonne, int compteur_item[6]){
    fusee(plateau, ligne, colonne, 1, compteur_item);
    fusee(plateau, ligne, colonne, 2, compteur_item);
    effet_diagonale4(plateau, ligne, colonne, 1, compteur_item);
    effet_diagonale4(plateau, ligne, colonne, 2, compteur_item);
}

