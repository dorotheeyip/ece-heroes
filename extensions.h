#include "moteur_de_jeu.h"

void placer_itembonus(int plateau[LINE][COLUMN], int ligne, int colonne, int typebonus, int orientation, int type);
// Place un objet bonus choisi sur une case choisie par le joueur
// typebonus=1 : bombe
// typebonus=2 : fusée
// typebonus=3 : joker

void bombe(int plateau[LINE][COLUMN], int ligne, int colonne);
// Applique l'effet de destruction d'un carré 5x5, avec pour centre la case choisie par le joueur

void fusee(int plateau[LINE][COLUMN], int ligne, int colonne, int orientation);
// Applique l'effet de destruction d'une ligne entière, horizontale ou verticale selon l'orientation choisie
// orientation = 1 -> verticale
// orientation = 2 -> horizontale

void joker(int plateau[LINE][COLUMN], int ligne, int colonne, int type); // ajout type
// Remplace l'item d'une case choisie par le joueur par un item normal de son choix 


int detecter_diagonale4(int plateau[LINE][COLUMN], int *ligne, int *colonne, int *orientation); //ajout orientation 1=vers droite 2=vers gauche
// Détecte une diagonale de 4 items identiques et renvoie sa position via des pointeurs

int detecter_carre2x2(int plateau[LINE][COLUMN], int *ligne, int *colonne);
// Détecte un carré 2×2 d'items identiques et renvoie sa position via des pointeurs

int detecter_ligne7(int plateau[LINE][COLUMN], int *ligne, int *colonne);
// Détecte une suite horizontale ou verticale de 7 items identiques via des pointeurs

int detecter_figures_speciales(int plateau[LINE][COLUMN], int *ligne, int *colonne, int *orientation);
// Appelle detecter_diagonale4(), detecter_carre2x2() et detecter_ligne7() et renvoie un code correspondant à la figure trouvée(1 = diagonale4, 2 = carre2x2, 3 = ligne7)

void effet_diagonale4(int plateau[LINE][COLUMN], int ligne, int colonne, int orienttion); //ajout orientation 1=vers droite 2=vers gauche
// Détruit la diagonale entière sur laquelle se trouve la suite détectée

void effet_carre2x2(int plateau[LINE][COLUMN], int ligne, int colonne);
// Détruit le contour du carré 2x2, détruisant ainsi un carré 4x4

void effet_ligne7(int plateau[LINE][COLUMN], int ligne, int colonne, int orientation); // ajout orientation 1=verticale 0=horizontale
// Fusionne les 7 items alignés en un seul item spécial(=6) du même type placé au centre de la ligne (4e position)

void effet_item_ligne7(int plateau[LINE][COLUMN], int ligne, int colonne);
// Applique l'effet de destruction du carré 3x3 autour de la case de l'item spécial, des 2 diagonales et des lignes verticale et horizontale passant par cette case

