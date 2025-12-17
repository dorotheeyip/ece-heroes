#include <stdio.h>
#include "nouvelle_partie.h"
#include "sauvegarde.h"

int main() {

    GameState game;
    int couleur;

    printf("Entrez votre pseudo : ");
    scanf("%49s", game.pseudo);

    if (charger_sauvegarde(&game)) {
        printf("Sauvegarde trouvée, reprise de la partie...\n");
    } else {
        printf("Aucune sauvegarde, nouvelle partie\n");
        lancer_nouvelle_partie(&game);
    }

    while (1) {
        printf("\nNiveau %d | Coups %d | Progression %d/%d\n",
               game.niveau,
               game.coups_restants,
               game.progression,
               game.objectif_total);

        printf("Couleur détruite (1=R 2=B 3=V) : ");
        scanf("%d", &couleur);

        action_destruction(&game, couleur);
        verifier_etat(&game);
        sauvegarder_partie(&game);
    }

    return 0;
}
