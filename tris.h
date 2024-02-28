// Fonction tri fusion qui trie les cartes en fonction de leurs numéros
void triFusionDeCartes(carte* tabCartes, int debut, int fin); // triFusionDeCartes(deckJoueur, 0, n-1)

// Fonction tri fusion qui trie les cartes en fonction de leurs numéros
void triFusionJoueur(carte* tabCartes, int* tabNumero, int debut, int fin); // triFusionDeCartes(deckJoueur, 0, n-1)

// Fonction tri fusion qui trie les scores des joueurs
void triFusionScoreboard(joueur* joueurs,int debut,int fin);

// Fonction fusionner utile pour les tris fusions
void fusionner(joueur* joueurs,int debut,int milieu,int fin);