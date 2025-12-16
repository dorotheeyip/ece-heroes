#include <stdio.h>
#include <string.h>
#include "sauvegarde.h"

int save_game() {
    int niveau, vies, coups, rows, cols;
    int plateau[LINE][COLUMN];
    char pseudo[50];
    float temps;
    char filename[60];

    printf("Entrez le pseudo à sauvegarder : ");
    scanf("%s", pseudo);

    sprintf(filename, "%s.txt", pseudo);

    FILE *f = fopen(filename, "w");
    if (f == NULL) {
        printf("Erreur : impossible de créer le fichier\n");
        return -1;
    }

    fprintf(f, "%s\n", pseudo);
    fprintf(f, "%d\n", niveau);
    fprintf(f, "%d\n", vies);
    fprintf(f, "%d\n", coups);
    fprintf(f, "%f\n", temps);

    fprintf(f, "%d %d\n", rows, cols);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++)
            fprintf(f, "%d ", plateau[i][j]);
        fprintf(f, "\n");
    }

    fclose(f);
    return 0;
}

