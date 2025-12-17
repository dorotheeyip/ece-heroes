#ifndef SAUVEGARDE_H
#define SAUVEGARDE_H

#define LINE 10
#define COLUMN 10

// Déclaration de la fonction de sauvegarde
// pseudo : pseudo du joueur
// niveau : niveau actuel
// vies : nombre de vies restantes
// temps : temps restant ou écoulé
// objectif : avancement de l'objectif (ex: pourcentage)
// rows, cols : dimensions du plateau
// plateau : tableau représentant le plateau de jeu
int save_game(const char* pseudo, int niveau, int vies, float temps, int objectif,
              int rows, int cols, int plateau[LINE][COLUMN]);

#endif // SAUVEGARDE_H
