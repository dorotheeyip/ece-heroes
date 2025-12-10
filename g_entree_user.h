#ifndef G_ENTREE_USER_H
#define G_ENTREE_USER_H

#include "moteur_de_jeu.h"  // Pour avoir accès à Plateau, LINE, COLUMN

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

// Prototypes des fonctions
int lire_touche();
void deplacer_curseur(Cursor *c, int max_line, int max_col, int touche);
void selectionner_item1(SelectionState *s, Cursor c, Plateau *p);
void selectionner_item2(SelectionState *s, Cursor c, Plateau *p);
void permuter_items(SelectionState *s, Plateau *p);
int combinaison_valide(SelectionState s, Plateau *p);

#endif