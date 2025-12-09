#include <stdio.h>

void afficher_menu() {
    printf("\n===== MENU =====\n");
    printf("1 - Lire les règles du jeu\n");
    printf("2 - Démarrer une nouvelle partie\n");
    printf("3 - Reprendre une partie sauvegardée\n");
    printf("0 - Quitter\n");
    printf("Votre choix : ");
}


int lire_regle_du_jeu(){
    
    FILE *f = fopen("regles_jeu.txt", "r");
    char texte[256];

    if (!f) {
        printf("Impossible d ouvrir le fichier.\n");
        return 1;
    }

    while (fgets(texte, sizeof(texte), f) != NULL) {
        printf("%s", texte);
    }

    fclose(f);
    return 0;

}

int main() {
    int choix;

    do {
        afficher_menu();
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                lire_regle_du_jeu();
                break;

            case 2:
                printf("En construction...\n");
                break;

            case 3:
                printf("En construction...\n");
                break;

            case 0:
                printf("Au revoir !\n");
                break;

            default:
                printf("Choix invalide.\n");
        }

    } while (choix != 0);

    return 0;
}