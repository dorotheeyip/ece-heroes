#ifndef SAVE_H
#define SAVE_H

#include <stdio.h>

/**
 * Charge une partie à partir d'un fichier correspondant au pseudo du joueur.
 * Si le fichier n'existe pas, une nouvelle partie est lancée.
 *
 * @return int retourne 0 (peut être modifié selon la gestion des erreurs)
 */
int load_game(void);

#endif // SAVE_H
