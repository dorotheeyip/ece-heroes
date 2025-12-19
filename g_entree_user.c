#include <stdio.h>
#include "g_entree_user.h"
#ifdef _WIN32
    #include "affichage_console.h"
#else
    #include "affichage_console_mac.h"
#endif
#include "moteur_de_jeu.h"
#include "interface_console.h"

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
        case 'w':  // haut
        case 72:   // flèche haut
            if (c->line > 0) c->line--;
            break;

        case 's':  // bas
        case 80:   // flèche bas
            if (c->line < max_line - 1) c->line++;
            break;

        case 'a':  // gauche
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
void selectionner_item1(SelectionState *s, Cursor c, GameState *game) {
    s->selected = 1;
    s->r1 = c.line;
    s->c1 = c.col;
    // Appeler la fonction pour mettre en valeur l'item sélectionné
    afficher_item_selec(s->r1, s->c1, game->plateau[s->r1][s->c1]);

}


// ---------------------------------------
// Sélectionner le second item
// ---------------------------------------
void selectionner_item2(SelectionState *s, Cursor c, GameState *game) {
    s->r2 = c.line;
    s->c2 = c.col;
    s->selected = 2;
    // Appeler la fonction pour mettre en valeur l'item sélectionné
    // afficher_item_selec(s->r2, s->c2);
    
    afficher_item_selec(s->r2, s->c2, game->plateau[s->r2][s->c2]);

}

// ---------------------------------------
// Permuter deux items sur le plateau
// ---------------------------------------
void permuter_items(SelectionState *s, GameState *game) {

    // int (*tab)[COLUMN] = p->plateau;
    // Échange les valeurs dans la grille
    int temp = game->plateau[s->r1][s->c1];
    game->plateau[s->r1][s->c1] = game->plateau[s->r2][s->c2];
    game->plateau[s->r2][s->c2] = temp;
    s->selected = 0;
    
    // Réinitialise la sélection
    s->selected = 0;
}

// ---------------------------------------
// Vérifier si la permutation créerait une combinaison valide
// (test AVANT de permuter réellement)
// ---------------------------------------
int combinaison_valide(SelectionState s, GameState *game) {
    
    // ⚠️ Attention : son plateau = int plateau[LINE][COLUMN]
    int (*tab)[COLUMN] = game->plateau;

    // 1) permutation temporaire
    int temp = tab[s.r1][s.c1];
    tab[s.r1][s.c1] = tab[s.r2][s.c2];
    tab[s.r2][s.c2] = temp;
    
    // 2️⃣ VÉRIFIER LES COMBINAISONS sur le plateau "testé"
    int resultat = 0;  // Par défaut : pas de combinaison
    int marque[LINE][COLUMN]={0};

    if (combinaison_ligne_6(tab, marque)) resultat = 1;
    else if (combinaison_colonne_6(tab, marque)) resultat = 1;
    else if (combinaison_croix(tab, marque)) resultat = 1;
    else if (combinaison_carre(tab, marque)) resultat = 1;
    else if (combinaison_ligne_4(tab, marque)) resultat = 1;
    else if (combinaison_colonne_4(tab, marque)) resultat = 1;
    
    // 3️⃣ ANNULER LA PERMUTATION (on remet comme avant)
    temp = tab[s.r1][s.c1];
    tab[s.r1][s.c1] = tab[s.r2][s.c2];
    tab[s.r2][s.c2] = temp;
    
    return resultat;
}


// ---------------------------------------
// Boucle principale IHM
// (affichage + curseur + sélection)
// ---------------------------------------
// void boucle_jeu(Plateau *plateau) {

//     Cursor c = {0, 0};
//     SelectionState s = {0, -1, -1, -1, -1};

//     int running = 1;

//     hide_cursor();

//     while (running) {

//         int touche = lire_touche();
//         if (touche != -1) {

//             // Déplacement du curseur
//             deplacer_curseur(&c, 25, 45, touche);

//             // Sélection item
//             if (touche == ' ') {

//                 if (s.selected == 0) {
//                     selectionner_item1(&s, c, plateau);
//                 }
//                 else if (s.selected == 1) {
//                     selectionner_item2(&s, c, plateau);

//                     // Test combinaison valide
//                     if (combinaison_valide(s, plateau)) {
//                         permuter_items(&s, plateau);
//                         // pour l’instant on remet à zéro
//                         s.selected = 0;
//                     }
//                     else {
//                         // annuler sélection
//                         s.selected = 0;
//                     }
//                 }
//             }

//             // On actualise l’affichage
//             clrscr();
//             gotoxy(1,1);
//             printf("Curseur : (%d , %d)\n", c.line, c.col);
//             printf("Selection : %d\n", s.selected);
//             printf("Item1 : (%d,%d)\n", s.r1, s.c1);
//             printf("Item2 : (%d,%d)\n", s.r2, s.c2);
//         }
//     }

//     show_cursor();
// }
