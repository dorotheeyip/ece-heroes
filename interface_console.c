#include <stdio.h>
#include "interface_console.h"
#include "affichage_console.h"

// ---------------------------------------
// Effacer écran
// ---------------------------------------
void effacer_ecran() {
    clrscr();
}


// ---------------------------------------
// Changer couleur
// ---------------------------------------
void changer_couleur(int color) {
    text_color(color);
}


// ---------------------------------------
// Afficher un item sélectionné
// ---------------------------------------
void afficher_item_selec(int row, int col) {
    set_color(RED);
    gotoxy(col, row);
    printf("[X]");   // exemple visuel
    set_color(WHITE);
}


// ---------------------------------------
// Afficher infos du jeu
// ---------------------------------------
void afficher_info_jeu(int niveau, int vies, int coups) {
    gotoxy(1, 1);
    printf("Niveau : %d | Vies : %d | Coups restants : %d", niveau, vies, coups);
}
