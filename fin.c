#include <stdio.h>
#include <string.h>
#include "fin.h"

// Fonction de sauvegarde
int save_game(const char* pseudo, int niveau, int vies, float temps, int objectif,
              int rows, int cols, int plateau[LINE][COLUMN]) {

    char filename[60];
    sprintf(filename, "%s.txt", pseudo);

    // Ouvre le fichier pour écraser son contenu
    FILE *f = fopen(filename, "w");
    if (f == NULL) {
        printf("Erreur : impossible d'ouvrir le fichier %s\n", filename);
        return -1;
    }

    // Écriture des informations principales
    fprintf(f, "Pseudo: %s\n", pseudo);
    fprintf(f, "Niveau: %d\n", niveau);
    fprintf(f, "Vies: %d\n", vies);
    fprintf(f, "Temps: %.2f\n", temps);
    fprintf(f, "Avancement objectif: %d\n", objectif);

    // Écriture de la taille du plateau
    fprintf(f, "Rows: %d Columns: %d\n", rows, cols);

    // Écriture du plateau
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++)
            fprintf(f, "%d ", plateau[i][j]);
        fprintf(f, "\n");
    }

    fclose(f);
    printf("Partie sauvegardée avec succès dans %s\n", filename);
    return 0;
}