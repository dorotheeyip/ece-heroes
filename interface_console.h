#ifndef DISPLAY_H
#define DISPLAY_H

#include "affichage_console.h"
#include "g_entree_user.h"

void effacer_ecran();
void changer_couleur(int color);
void afficher_item_selec(int row, int col);
void afficher_info_jeu(int niveau, int vies, int coups);

#endif

