#ifndef DISPLAY_H
#define DISPLAY_H

#ifdef _WIN32
    #include "affichage_console.h"
#else
    #include "affichage_console_mac.h"
#endif
#include "g_entree_user.h"

void effacer_ecran();
void changer_couleur(int color);
void afficher_item_selec(int row, int col, int item);

#endif

