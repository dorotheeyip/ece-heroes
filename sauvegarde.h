#ifndef SAVE_H
#define SAVE_H

#include <stdio.h>
#include "moteur_de_jeu.h"

/**
 * Sauvegarde la partie courante dans un fichier nommé
 * à partir du pseudo du joueur.
 *
 * @return int retourne 0 si la sauvegarde réussit,
 *         -1 en cas d'erreur d'ouverture de fichier
 */
int save_game(void);

#endif // SAVE_H
