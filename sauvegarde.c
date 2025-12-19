#include "sauvegarde.h"
#include <stdio.h>

int charger_sauvegarde(GameState *game) {

    char filename[60];
    sprintf(filename, "%s.txt", game->pseudo);

    FILE *f = fopen(filename, "r");
    if (!f) return 0;

    fscanf(f, "%d %d %d %f", &game->niveau, &game->vies, &game->coups_restants, &game->temps_restants);

    // Objectifs par item
    for (int i = 1; i <= 5; i++) {
        fscanf(f, "%d", &game->objectif_items[i]);
    }

    // Progression par item
    for (int i = 1; i <= 5; i++) {
        fscanf(f, "%d", &game->progression_items[i]);
    }

    for (int i = 0; i < LINE; i++) {
        for (int j = 0; j < COLUMN; j++) {
            fscanf(f, "%d", &game->plateau[i][j]);
        }
    }

    fclose(f);
    return 1;
}

void sauvegarder_partie(GameState *game) {

    char filename[60];
    sprintf(filename, "%s.txt", game->pseudo);

    FILE *f = fopen(filename, "w");
    if (!f) return;

    fprintf(f, "%d %d %d %f\n", game->niveau, game->vies, game->coups_restants, game->temps_restants);

    for (int i = 1; i <= 5; i++)
        fprintf(f, "%d ", game->objectif_items[i]);
    fprintf(f, "\n");

    for (int i = 1; i <= 5; i++)
        fprintf(f, "%d ", game->progression_items[i]);
    fprintf(f, "\n");

    for (int i = 0; i < LINE; i++) {
        for (int j = 0; j < COLUMN; j++) {
            fprintf(f, "%d ", game->plateau[i][j]);
        }
        fprintf(f, "\n");
    }

    fclose(f);
}
