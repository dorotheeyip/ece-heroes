// #include "moteur_de_jeu.h"
#include "g_entree_user.h"

int main() {

    Plateau p;   // <-- un SEUL plateau commun

    initialiser_plateau(&p); // si tu veux une fonction dédiée
    boucle_jeu(&p);          // <-- ton fichier utilisateur
     // agit sur LE MÊME plateau
}
