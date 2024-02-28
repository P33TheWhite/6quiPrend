
// Vide le buffer
void videBuffer();


// Initialise un joueur en fonction de son numéro de joueur et qui initialise son deck.
// Entrée(s) :  Tableau de joueur, Numéro du joueur
void initJoueur(joueur* joueurs,int numeroJoueur);


// Détermine si le jeu est toujours en cours ou non 
// Entrée(s) :  Tableau de joueur, Nombre de joueurs, Score maximum
// Sortie(s) :  Booléen (1 En cours / 0 Terminé)
int conditionDeJeu(joueur* joueurs,int nombreJoueurs,int scoreMax);


// Retourne une carte en fonction du numéro donné.
// Entrée(s) :  Numéro de carte
// Sortie(s) :  Carte
carte creerCarte(int numero);


// Initialise une pioche donné en une pioche de 104 cartes mélangéés.
// Entrée(s) :  Tableau de carte
void initPioche(carte* pioche);


// Déplace une carte d'une liste de carte à une autre (gère le décalage des tableaux) : changer la taille des tableaux après avoir utilisé cette fonction.
// Entrée(s) :  Tableau de carte de départ, Position de départ, Tableau de carte d'arrivée, Position d'arrivée, Taille du tableau de départ, Taille du tableau d'arrivée
void deplacerCarte(carte* tab1, int posDepart, carte* tab2, int posArrivee, int taille1, int taille2);


// Initialise la table de jeu (pioche, cartes sur table).
// Entrée(s) :  Pointeur de table
void initTable(table *tableDeJeu);


// Initialise le tableau de score.
// Entrée(s) :  Pointeur de scoreboard, Tableau de joueurs, Nombre de Joueurs, Score Maximum
void initScoreboard (scoreboard* s,joueur* tabJoueurs, int nombreJoueurs,int scoremax);


// Pioche une carte de la pioche vers le deck du joueur donné.
// Entrée(s) :  Pointeur de table, Pointeur de joueur
void piocherVersJoueur(table* tableDeJeu, joueur* p_j);


// Retourne la somme des tdb d'un deck donné (avec sa taille).
// Entrée(s) :  Tableau de cartes, Taille du tableau de cartes
// Sortie(s) :  Entier
int totalTdb(carte* deck, int tailleDeck);


// Retourne la position du tableau ayant le plus petit total de tdb.
// Entrée(s) :  Pointeur de table
// Sortie(s) :  Entier
int plusPetitTotalTdB (table* tableDeJeu);


// Retourne la différence entre la dernière carte d'un tableau de carte et une carte donnée si la carte donnée est supérieur à la dernière carte du tableau.
// Sinon elle renvoie -1.
// Entrée(s) :  Tableau de cartes, Taille du tableau de cartes, Carte
// Sortie(s) :  Entier
int calculDifference(carte* deck, int tailleDeck, carte c);


// Retourne la position du tableau ayant la plus petite différence avec la carte choisis du joueur.
// Entrée(s) :  Pointeur de table, Carte
// Sortie(s) :  Position
int plusPetiteDifference(table* tableDeJeu, carte c);


// Joue une carte du deck du joueur donné vers un deck de la table déterminé automatiquement par le jeu.
// Retourne 1 si le joueur peut acheter, 0 sinon.
// Entrée(s) :  Pointeur de joueur, Indice de position de carte, Pointeur de table
// Sortie(s) :  Booléen
int jouerCarteVersTable(joueur* p_j, int posCarteSelect, table* tableDeJeu);


// Fonction qui achète (remplace) une ligne table donné par une carte du deck du joueur donné et actualise ses points.
// Entrée(s) :  Pointeur de joueur, Indice de position de carte, Indice de rangée, Pointeur de table
void acheterLigneTable(joueur* p_j, int posCarteSelect,int indexRangee, table* tableDeJeu);


// Permet de libérer la mémoire alloué de la table .
// Entrée(s) :  Table
void freeTable(table tableDeJeu);


// Permet de libérer la mémoire alloué d'un joueur.
// Entrée(s) :  Joueur
void freeJoueur(joueur j);
