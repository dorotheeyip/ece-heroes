#include "sauvegarde.h"
#include <stdio.h>

int charger_sauvegarde(GameState *game) {

    char filename[60];
    sprintf(filename, "%s.txt", game->pseudo);

    FILE *f = fopen(filename, "r");
    if (!f) return 0;

    fscanf(f, "%d %d %d",
           &game->niveau,
           &game->vies,
           &game->coups_restants);

    fscanf(f, "%d %d %d",
           &game->objectif_couleur,
           &game->objectif_total,
           &game->progression);

    fclose(f);
    return 1;
}

void sauvegarder_partie(GameState *game) {

    char filename[60];
    sprintf(filename, "%s.txt", game->pseudo);

    FILE *f = fopen(filename, "w");
    if (!f) return;

    fprintf(f, "%d %d %d\n",
            game->niveau,
            game->vies,
            game->coups_restants);

    fprintf(f, "%d %d %d\n",
            game->objectif_couleur,
            game->objectif_total,
            game->progression);

    fclose(f);
}
