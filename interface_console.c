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
void afficher_item_selec(int row, int col, int item) {
    const char symboles[] = {' ', '*', '^', '&', '+', '%', '?'};  // index 0-6
    
    text_color(WHITE);
    gotoxy(col, row);
    
    if (item >= 0 && item <= 6) {
        putchar(symboles[item]);  // <-- putchar n'a pas de problème avec %
        putchar(' ');
    }
    
    text_color(WHITE);
}
