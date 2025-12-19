#ifndef MOTEUR_DE_JEU_H
#define MOTEUR_DE_JEU_H
#define LINE 7   
#define COLUMN 10

typedef struct {
    int plateau[LINE][COLUMN];
} Plateau;

int combinaison_ligne_6(int plateau[LINE][COLUMN], int marque[LINE][COLUMN]);
// Identifie les combinaisons de 6 items en ligne

int combinaison_colonne_6(int plateau[LINE][COLUMN], int marque[LINE][COLUMN]);
// Identifie les combinaisons de 6 items en colonne

int combinaison_croix(int plateau[LINE][COLUMN], int marque[LINE][COLUMN]);
// Identifie les combinaisons de 9 items en croix

int combinaison_carre(int plateau[LINE][COLUMN], int marque[LINE][COLUMN]);
// Identifie les combinaisons de 16 items en carré de 4x4

int combinaison_ligne_4(int plateau[LINE][COLUMN], int marque[LINE][COLUMN]);
// Identifie les combinaisons de 4 items en ligne

int combinaison_colonne_4(int plateau[LINE][COLUMN], int marque[LINE][COLUMN]);
// Identifie les combinaisons de 4 items en colonne

void supprim_combin(int plateau[LINE][COLUMN], int marque[LINE][COLUMN], int compteur[6]);
// Supprime les combinaisons identifiées

void renouvellement_case(int plateau[LINE][COLUMN]);
// Animation de la descente des items et apparition de nouveaux items pour combler les vides après deescente par gravité

void afficher_tab(int plateau[LINE][COLUMN]);
// Affiche le tableau puis laisse un intervalle de temps

void afficher_tab_symboles(int plateau[LINE][COLUMN]);
#endif