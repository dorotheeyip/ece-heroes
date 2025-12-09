#ifndef INPUT_H
#define INPUT_H

#include "affichage_console.h"

// Position du curseur
typedef struct {
    int line;
    int col;
} Cursor;

// Structure pour gérer l'état de la sélection
typedef struct {
    int selected;  // 0: rien, 1: premier item sélectionné, 2: deux items sélectionnés
    int r1, c1;    // Position du premier item (row, col)
    int r2, c2;    // Position du deuxième item (row, col)
} SelectionState;


// Plateau de jeu
typedef struct {
    int rows;
    int cols;
    int **plateau;    // tableau 2D dynamique
} Plateau;


// Fonctions IHM
int lire_touche();
void deplacer_curseur(Cursor *c, int max_rows, int max_cols, int touche);
void selectionner_item1(SelectionState *s, Cursor c);
void selectionner_item2(SelectionState *s, Cursor c);
int combinaison_valide(SelectionState s);
void boucle_jeu();


// Structure pour gérer l'état de la sélection
typedef struct {
    int selected;  // 0: rien, 1: premier item sélectionné, 2: deux items sélectionnés
    int r1, c1;    // Position du premier item (row, col)
    int r2, c2;    // Position du deuxième item (row, col)
} SelectionState;

// Prototypes des fonctions
void selectionner_item1(SelectionState *s, Cursor c);
void selectionner_item2(SelectionState *s, Cursor c);
void permuter_items(SelectionState *s, Plateau *p);

#endif


