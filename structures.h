// STRUCTURE carte
typedef struct{
	int numero;
	int tdb;
	int estRecente;
}carte;


// STRUCTURE joueur
typedef struct{
	char* pseudo;
	carte* deck;
	int score; //positif
	int tailleDeck;
	int estRobot;
}joueur;

// STRUCTURE table
typedef struct{
	carte* pioche;
	int taillePioche;

	carte** tabDecks; // Tableau des 4 decks posés sur la table
	int* tabTailleDecks; // Tableau de la taille des 4 decks posés sur la table

	joueur* infosJoueurs;
	int* compteurAffichage;
}table;

typedef struct {
	int compteurAffichage;
	joueur* infoJoueurs;
	int nombreJoueurs;
	int scoremax;
} scoreboard;