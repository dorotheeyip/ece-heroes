#include <stdio.h>
#include "g_entree_user.h"
#include "affichage_console.h"

// ---------------------------------------
// Lire une touche (non bloquant)
// ---------------------------------------
int lire_touche() {
    if (kbhit()) {
        return getch();
    }
    return -1;  // aucune touche pressée
}


// ---------------------------------------
// Déplacer curseur (zqsd ou flèches)
// max_rows/max_cols = limites du plateau
// ---------------------------------------
void deplacer_curseur(Cursor *c, int max_line, int max_col, int touche) {

    switch (touche) {
        case 'z':  // haut
        case 72:   // flèche haut
            if (c->line > 0) c->line--;
            break;

        case 's':  // bas
        case 80:   // flèche bas
            if (c->line < max_line - 1) c->line++;
            break;

        case 'q':  // gauche
        case 75:   // flèche gauche
            if (c->col > 0) c->col--;
            break;

        case 'd':  // droite
        case 77:   // flèche droite
            if (c->col < max_col - 1) c->col++;
            break;
    }
}


// ---------------------------------------
// Sélectionner le premier item
// ---------------------------------------
void selectionner_item1(SelectionState *s, Cursor c) {
    s->selected = 1;
    s->r1 = c.line;
    s->c1 = c.col;
}


// ---------------------------------------
// Sélectionner le second item
// ---------------------------------------
void selectionner_item2(SelectionState *s, Cursor c) {
    s->r2 = c.line;
    s->c2 = c.col;
    s->selected = 2;
}

// ---------------------------------------
// Permuter deux items sur le plateau
// ---------------------------------------
void permuter_items(SelectionState *s, Plateau *p) {
    // Échange les valeurs dans la grille
    int temp = p->plateau[s->r1][s->c1];
    p->plateau[s->r1][s->c1] = p->plateau[s->r2][s->c2];
    p->plateau[s->r2][s->c2] = temp;
    
    // Réinitialise la sélection
    s->selected = 0;
}

// ---------------------------------------
// Vérifier si la permutation créerait une combinaison valide
// (test AVANT de permuter réellement)
// ---------------------------------------
int combinaison_valide(SelectionState s, Plateau *p) {
    
    // 1️⃣ PERMUTATION TEMPORAIRE (test)
    int temp = p->plateau[s.r1][s.c1];
    p->plateau[s.r1][s.c1] = p->plateau[s.r2][s.c2];
    p->plateau[s.r2][s.c2] = temp;
    
    // 2️⃣ VÉRIFIER LES COMBINAISONS sur le plateau "testé"
    int resultat = 0;  // Par défaut : pas de combinaison
    
    if (_______________________(p)) {
        resultat = 1;
    }
    else if (_______________________(p)) {
        resultat = 1;
    }
    else if (_______________________(p)) {
        resultat = 1;
    }
    // ... autres vérifications
    
    // 3️⃣ ANNULER LA PERMUTATION (on remet comme avant)
    temp = p->plateau[s.r1][s.c1];
    p->plateau[s.r1][s.c1] = p->plateau[s.r2][s.c2];
    p->plateau[s.r2][s.c2] = temp;
    
    return resultat;
}


// ---------------------------------------
// Boucle principale IHM
// (affichage + curseur + sélection)
// ---------------------------------------
void boucle_jeu(Plateau *plateau) {

    Cursor c = {0, 0};
    SelectionState s = {0, -1, -1, -1, -1};

    int running = 1;

    hide_cursor();

    while (running) {

        int touche = lire_touche();
        if (touche != -1) {

            // Déplacement du curseur
            deplacer_curseur(&c, 25, 45, touche);

            // Sélection item
            if (touche == ' ') {

                if (s.selected == 0) {
                    selectionner_item1(&s, c);
                }
                else if (s.selected == 1) {
                    selectionner_item2(&s, c);

                    // Test combinaison valide
                    if (combinaison_valide(s, plateau)) {
                        permuter_items(&s, plateau);
                        // pour l’instant on remet à zéro
                        s.selected = 0;
                    }
                    else {
                        // annuler sélection
                        s.selected = 0;
                    }
                }
            }

            // On actualise l’affichage
            clrscr();
            gotoxy(1,1);
            printf("Curseur : (%d , %d)\n", c.line, c.col);
            printf("Selection : %d\n", s.selected);
            printf("Item1 : (%d,%d)\n", s.r1, s.c1);
            printf("Item2 : (%d,%d)\n", s.r2, s.c2);
        }
    }

    show_cursor();
}
