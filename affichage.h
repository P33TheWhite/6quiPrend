// Affiche un nombre formatté pour l'affichage dans une carte
// Entrée(s) :  Entier
void nombreFormatte(int nb);


/* 
┏━━━━━━━━┓┏━━━━━━━━┓┏━━━━━━━━┓┏━━━━━━━━┓┏━━━━━━━━┓┏━━━━━━━━┓┏━━━━━━━━┓┏━━━━━━━━┓
┃ 94     ┃┃ 64     ┃┃ 25     ┃┃ 52     ┃┃ 29     ┃┃ 62     ┃┃ 26     ┃┃ 75     ┃
┃        ┃┃        ┃┃        ┃┃        ┃┃        ┃┃        ┃┃        ┃┃        ┃
┃        ┃┃        ┃┃        ┃┃        ┃┃        ┃┃        ┃┃        ┃┃        ┃
┃   ✱    ┃┃   ✱    ┃┃  ✱ ✱   ┃┃   ✱    ┃┃   ✱    ┃┃   ✱    ┃┃   ✱    ┃┃  ✱ ✱   ┃
┃        ┃┃        ┃┃        ┃┃        ┃┃        ┃┃        ┃┃        ┃┃        ┃
┗━━━━━━━━┛┗━━━━━━━━┛┗━━━━━━━━┛┗━━━━━━━━┛┗━━━━━━━━┛┗━━━━━━━━┛┗━━━━━━━━┛┗━━━━━━━━┛

*/


// Affiche la ligne 1 d'une carte 
// Entrée(s) :  Carte
void affCarteLigne1(carte c);

// Affiche la ligne 2 d'une carte 
// Entrée(s) :  Carte
void affCarteLigne2(carte c);

// Affiche la ligne 3 d'une carte 
// Entrée(s) :  Carte
void affCarteLigne3(carte c);

// Affiche la ligne 4 d'une carte 
// Entrée(s) :  Carte
void affCarteLigne4(carte c);

// Affiche la ligne 5 d'une carte 
// Entrée(s) :  Carte
void affCarteLigne5(carte c);

// Affiche la ligne 6 d'une carte 
// Entrée(s) :  Carte
void affCarteLigne6(carte c);

// Affiche la ligne 7 (dernière) d'une carte 
// Entrée(s) :  Carte
void affCarteLigne7Last(carte c);

// Fonction qui permet d'afficher une seule ligne de plusieurs cartes côte à côte
// Entrée(s) :  Carte
void affLigneCarte(int ligne,carte* tabCartes, int taille);


// CARTE TRANSPARENTE DE PREVIEW
/* 
    printf("┏ ━ ━━ ━ ┓\n");
    printf("┃        ┃\n");
    printf("          \n");
    printf("┃        ┃\n");
    printf("          \n"); 
    printf("┃        ┃\n");
    printf("┗ ━ ━━ ━ ┛\n");

*/

// Affiche des cartes transparente (en pointillés) à droite des autres cartes
// Entrée(s) :  Position de ligne, Taille du tableau de cartes
void affVideLigne(int ligne,int taille);


// Affiche un deck de table ENTIER en se servant des fonctions précedentes
// Entrée(s) :  Tableau de cartes, Taille du tableau de cartes, Pointeur de scoreboard
void affDeckTable(carte* tabCartes, int taille, scoreboard* scboard);


// Affiche un deck d'un joueur
// Entrée(s) :  Tableau de cartes, Taille du tableau de cartes
void affDeckJoueur(carte* tabCartes, int taille);


// Réinitialise le compteur du scoreboard
// Entrée(s) :  Pointeur de scoreboard
void actualiserScoreboard(scoreboard* scboard);

// Affiche le scoreboard
// Entrée(s) :  Pointeur de scoreboard
void afficherScoreboard(scoreboard* scboard);

// Affiche une table entière
// Entrée(s) :  Table, Pointeur de scoreboard
void afficherTable(table table, scoreboard* scboard);

// Compte le nombre de caractère affectant la couleur dans une string
// Entrées(s) : Chaine de caractère
int colorCount(char* str);

// Affiche un texte centré dans la chaine fusion donnée
// Entrée(s) :  Chaine de caractère à écraser, Chaine de caractère à centrer, Chaine de caractère d'espace
void txtFormatte(char* strFusion,char* texte, char* espace);

// Affiche une string centré dans une boîte de texte
// Entrée(s) :  Message (sans \n)
void afficherBox(char* str);

// Affiche un scoreboard de fin de manche
// Entrée(s) :  Pointeur de scoreboard, Nombre de joueurs
void affichageScoreFinDeManche(scoreboard* scboard, int nombreJoueurs);

// Affiche un scoreboard de fin de partie
// Entrée(s) :  Pointeur de scoreboard, Nombre de joueurs
void affichageScoreFinDePartie(scoreboard* scboard, int nombreJoueurs);

// Affiche une table avec des cartes retournés
void affTableCache();

// AFFICHAGE N'IMPORTE QUELLE CARTE
/* Les cartes sontbien alignés quand on le print dans le terminal
┏━━━━━━━━┓┏━━━━━━━━┓┏━━━━━━━━┓┏━━━━━━━━┓┏━━━━━━━━┓┏━━━━━━━━┓┏━━━━━━━━┓┏━━━━━━━━┓
┃ 94     ┃┃ 64     ┃┃ 25     ┃┃ 52     ┃┃ 29     ┃┃ 62     ┃┃ 26     ┃┃ 75     ┃
┃        ┃┃        ┃┃        ┃┃        ┃┃        ┃┃        ┃┃        ┃┃        ┃
┃        ┃┃        ┃┃        ┃┃        ┃┃        ┃┃        ┃┃        ┃┃        ┃
┃   ✱    ┃┃   ✱    ┃┃  ✱ ✱   ┃┃   ✱    ┃┃   ✱    ┃┃   ✱    ┃┃   ✱    ┃┃  ✱ ✱   ┃
┃        ┃┃        ┃┃        ┃┃        ┃┃        ┃┃        ┃┃        ┃┃        ┃
┗━━━━━━━━┛┗━━━━━━━━┛┗━━━━━━━━┛┗━━━━━━━━┛┗━━━━━━━━┛┗━━━━━━━━┛┗━━━━━━━━┛┗━━━━━━━━┛

*/