void gerer_menu_apres_echec(GameState *game, int *niveau_echoue);

void mettre_a_jour_affichage(GameState *game, Cursor c, SelectionState s);

void traiter_combinaisons_apres_mouvement(GameState *game, int num_niveau);

void verifier_reussite_niveau(GameState *game, int niveau_reussi);

void jouer_niveau(int num_niveau, GameState *game, int reinitialiser);

void jouer_partie(GameState *game, int nouvelle);

void afficher_menu();

int lire_regle_du_jeu();
