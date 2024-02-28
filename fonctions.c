#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "structures.h"
#include "fonctions.h"
#include "tris.h"

void videBuffer(){
	int c=0;
    while((c = getchar()) != '\n');
}


void initJoueur(joueur* joueurs,int numeroJoueur){
	joueurs[numeroJoueur].pseudo = malloc(36 * sizeof(char));
    joueurs[numeroJoueur].deck = malloc(10 * sizeof(carte));
	joueurs[numeroJoueur].estRobot =0;

    printf("Pseudo du joueur %d (36 caractères max.) :\n", numeroJoueur + 1);
	fgets(joueurs[numeroJoueur].pseudo,sizeof(char)*36,stdin);
	if ((strlen(joueurs[numeroJoueur].pseudo) > 0) && (joueurs[numeroJoueur].pseudo[strlen (joueurs[numeroJoueur].pseudo) - 1] == '\n')){
        joueurs[numeroJoueur].pseudo[strlen (joueurs[numeroJoueur].pseudo) - 1] = '\0';
	}

	// Si le joueur n'a pas de nom ou seulement ! comme nom : alors c'est un robot dont le nom va être déterminé automatiquement
	if (!strcmp(joueurs[numeroJoueur].pseudo,"") ||!strcmp(joueurs[numeroJoueur].pseudo,"!")) {
		sprintf(joueurs[numeroJoueur].pseudo,"!Robot%d",numeroJoueur+1);
	}

	// Si le pseudo du joueur à sa création commence par un ! : alors c'est un robot
	if (joueurs[numeroJoueur].pseudo[0] == '!') {
		for (int it=0;it<strlen(joueurs[numeroJoueur].pseudo)-1;it++){
			joueurs[numeroJoueur].pseudo[it]=joueurs[numeroJoueur].pseudo[it+1];
		}
		joueurs[numeroJoueur].pseudo[strlen(joueurs[numeroJoueur].pseudo)-1]='\0';
		joueurs[numeroJoueur].estRobot = 1;
	}
    joueurs[numeroJoueur].score = 0;
}


int conditionDeJeu(joueur* joueurs,int nombreJoueurs,int scoreMax){
	int valeur=1;
	for (int i=0;i<nombreJoueurs;i++){
		// Si un joueur atteint le scoremax, alors le jeu est terminé
		if (joueurs[i].score>=scoreMax){
			valeur=0;
		}
	}
	return valeur;
}


carte creerCarte(int numero) {
	carte c;
	c.numero = numero;
	// Initialisation des attributs
	c.tdb =0;
	c.estRecente =0;
	// Calcul des points
	if (numero %10 ==0) {
		c.tdb = 3; // Si ça finit par 0
	} else if (numero %5 == 0) {
		c.tdb = 2; // Sinon, si ça finit par 5
	} else if (numero/10 - numero%10 != 0) {
		c.tdb =1;
	}

	// Vérif doublet à faire
	if (numero/10 - numero%10 == 0) {
		c.tdb += 5;
	}
	return c;
}


void initPioche(carte* pioche) {
	int n=104;
	// Génération d'une pioche trié par ordre croissant
	for (int i=0;i<n;i++){
		pioche[i]=creerCarte(i+1);
	}


	// Mélange de la pioche
	int min = 255;
	int max = rand()%255 +min; // Détermine le nombre de mélange max
	int nbAl1, nbAl2; // Initialisation de deux nombre aléatoires
	carte tmp;
	for (int j=0;j<max;j++) { // Pour un nombre de fois aléatoire
		nbAl1 = rand()%n;
		nbAl2 = rand()%n;

		// Echange entre deux cartes sélectionnés aléatoirement dans la pioche
		tmp = pioche[nbAl1];
		pioche[nbAl1] = pioche[nbAl2];
		pioche[nbAl2] = tmp;
	}
}


void deplacerCarte(carte* tab1, int posDepart, carte* tab2, int posArrivee, int taille1, int taille2) {
    carte temp;
    temp = tab1[posDepart]; // ça marche

    // Déplacement des cartes de la droite vers la gauche dans tab1
    for (int i= posDepart; i<taille1-1;i++) {
        tab1[i] = tab1[i+1];
    }

    // Déplacement des cartes de la gauche vers la droite dans tab2
    for (int i = taille2; i > posArrivee; i--) {
        tab2[i] = tab2[i-1];
    }

    // Ajout de la carte à la pos Arrivée de tab2
    tab2[posArrivee] = temp;

}


void initTable(table *tableDeJeu) {
	// Initialisation de la pioche et de sa taille
	tableDeJeu->taillePioche = 104;
	tableDeJeu->pioche = malloc(sizeof(carte)*tableDeJeu->taillePioche);
	initPioche(tableDeJeu->pioche);

	// Allocation des tables de jeux et de leurs tailles
	tableDeJeu->tabDecks = malloc(sizeof(carte*)*4);
	tableDeJeu->tabTailleDecks = malloc(sizeof(int)*4);

	// Initialisation des tables de jeux et de leurs tailles
	for (int i=0;i<4;i++) {
		tableDeJeu->tabDecks[i] = malloc(sizeof(carte)*6);
		tableDeJeu->tabTailleDecks[i] = 0;
	}

	// Création d'une mini pioche de 4 cartes (pour ensuite la trier)
	carte* miniPioche = malloc(4*sizeof(carte));
	for (int i=0;i<4;i++) {
		deplacerCarte(tableDeJeu->pioche,tableDeJeu->taillePioche-(i+1),miniPioche,i, tableDeJeu->taillePioche, i);
	}
	tableDeJeu->taillePioche -= 4;

	// Tri de la mini pioche
	triFusionDeCartes(miniPioche,0,3);

	// Pose des 4 cartes triées sur les différentes lignes de la table
	// L'ordre décroissant est utilisé pour éviter des décalages de tableaux
	for (int i=0;i<4;i++) {
		deplacerCarte(miniPioche,(3-i),tableDeJeu->tabDecks[(3-i)],0, (4-i), 0); //
		tableDeJeu->tabTailleDecks[3-i] += 1; 	// Actualisation de la taille des lignes de la table
	}
	free(miniPioche); // Libération de la mémoire de la mini pioche
}


void initScoreboard (scoreboard* s,joueur* tabJoueurs, int nombreJoueurs,int scoremax) {
	s->infoJoueurs = tabJoueurs;
	s->compteurAffichage =-1;
	s->nombreJoueurs = nombreJoueurs;
	s->scoremax=scoremax;
}


void piocherVersJoueur(table* tableDeJeu, joueur* p_j) {
	deplacerCarte(tableDeJeu->pioche, tableDeJeu->taillePioche-1, p_j->deck, p_j->tailleDeck, tableDeJeu->taillePioche-1, p_j->tailleDeck);
	p_j->tailleDeck +=1; // Augmentation de la taille du deck du joueur
	tableDeJeu->taillePioche -= 1; // Décrement de la taille de la pioche
}


int totalTdb(carte* deck, int tailleDeck) {
	int somme =0;
	for (int i=0; i< tailleDeck;i++) {
		somme += deck[i].tdb;
	}
	return somme;
}


int plusPetitTotalTdB (table* tableDeJeu) {
	int indexMin = 0;
	int tailleIndex, tailleMin;
	// Recherche de la rangée ayant le plus petit nombre de TdB 
	for (int i=1;i<4;i++) {
		tailleIndex = tableDeJeu->tabTailleDecks[i];
		tailleMin = tableDeJeu->tabTailleDecks[indexMin];
		if (totalTdb(tableDeJeu->tabDecks[i], tailleIndex) < totalTdb(tableDeJeu->tabDecks[indexMin], tailleMin)) {
			indexMin = i;
		}
	}
	return indexMin;
}


int calculDifference(carte* deck, int tailleDeck, carte c) {
	int diff = -1;

	if (deck[tailleDeck-1].numero < c.numero) {
		diff = c.numero - deck[tailleDeck-1].numero;
	}
	return diff;
}


int plusPetiteDifference(table* tableDeJeu, carte c) {
	int min = 0;
	for (int i=1;i<4;i++) {
		// Si le deck de la table est supérieur à la carte, alors on dit que le l'indice min est l'autre deck de la table
		if ((calculDifference(tableDeJeu->tabDecks[min], tableDeJeu->tabTailleDecks[min], c) == -1 && calculDifference(tableDeJeu->tabDecks[i], tableDeJeu->tabTailleDecks[i], c) != -1  )) {
			min = i;
		// Sinon on cherche le deck de la table avec la plus petite différence, (sauf si la différence est négative)
		} else if (calculDifference(tableDeJeu->tabDecks[min], tableDeJeu->tabTailleDecks[min], c) > calculDifference(tableDeJeu->tabDecks[i], tableDeJeu->tabTailleDecks[i], c) && calculDifference(tableDeJeu->tabDecks[i], tableDeJeu->tabTailleDecks[i], c) != -1 ) {
			min = i;
		}
	}
	// Si toutes les cartes des decks de tables sont supérieure à la carte choisie alors on cherche le deck avec le plus petit nombre total de tdb
	if (calculDifference(tableDeJeu->tabDecks[min], tableDeJeu->tabTailleDecks[min], c) == -1) {
		return -1;
	}
	return min;
}


int jouerCarteVersTable(joueur* p_j, int posCarteSelect, table* tableDeJeu) {
	carte carteSelect = p_j->deck[posCarteSelect];
	int indexDeck = plusPetiteDifference(tableDeJeu,carteSelect);
	if (indexDeck == -1) { // Si on peut acheter
			return 1;
	} else {
	
		int dernierIndice = tableDeJeu->tabTailleDecks[indexDeck] - 1;

		// Si le numéro de la dernière carte du deck de la table est inférieur à la carte qu'on va jouer et que il reste de la place sur le deck de la table
		if (tableDeJeu->tabDecks[indexDeck][dernierIndice].numero < carteSelect.numero && tableDeJeu->tabTailleDecks[indexDeck] < 5) {
			// Alors on déplace la carte sur la table et on change la taille des tableaux modifiés
			deplacerCarte(p_j->deck,posCarteSelect,tableDeJeu->tabDecks[indexDeck],dernierIndice+1, p_j->tailleDeck,tableDeJeu->tabTailleDecks[indexDeck]);
			p_j->tailleDeck--;
			tableDeJeu->tabDecks[indexDeck][tableDeJeu->tabTailleDecks[indexDeck]].estRecente = 1; // TEST
			tableDeJeu->tabTailleDecks[indexDeck]++;
			return 0;
			

			// Sinon, si on est le sixème qui prend, alors
		} else {
			
			// Ajout des points négatifs au joueur
			p_j->score += totalTdb(tableDeJeu->tabDecks[indexDeck], tableDeJeu->tabTailleDecks[indexDeck]);

			// Ré initialisation du deck qui sera a nouveau vide
			free(tableDeJeu->tabDecks[indexDeck]);
			tableDeJeu->tabDecks[indexDeck] = malloc(sizeof(carte)*6);
			tableDeJeu->tabTailleDecks[indexDeck] = 0;

			// Puis rempli par la carte du joueur
			deplacerCarte(p_j->deck,posCarteSelect,tableDeJeu->tabDecks[indexDeck],0, p_j->tailleDeck,0);
			p_j->tailleDeck--;
			tableDeJeu->tabDecks[indexDeck][tableDeJeu->tabTailleDecks[indexDeck]].estRecente = 1; // TEST
			tableDeJeu->tabTailleDecks[indexDeck]++;
			return 0;
		}
			

	}
}
	

void acheterLigneTable(joueur* p_j, int posCarteSelect,int indexRangee, table* tableDeJeu) {
	int indexDeck = indexRangee;
	// Ajout des points négatifs au joueur
	p_j->score += totalTdb(tableDeJeu->tabDecks[indexDeck], tableDeJeu->tabTailleDecks[indexDeck]);

	// Ré initialisation du deck qui sera a nouveau vide
	free(tableDeJeu->tabDecks[indexDeck]);
	tableDeJeu->tabDecks[indexDeck] = malloc(sizeof(carte)*6);
	tableDeJeu->tabTailleDecks[indexDeck] = 0;

	// Puis rempli par la carte du joueur
	deplacerCarte(p_j->deck,posCarteSelect,tableDeJeu->tabDecks[indexDeck],0, p_j->tailleDeck,0);
	p_j->tailleDeck--;
	tableDeJeu->tabDecks[indexDeck][tableDeJeu->tabTailleDecks[indexDeck]].estRecente = 1; // TEST
	tableDeJeu->tabTailleDecks[indexDeck]++;

}


void freeTable(table tableDeJeu) {
	for (int i=0; i<4; i++) {
		free(tableDeJeu.tabDecks[i]);
	}
	free(tableDeJeu.tabDecks);
	free(tableDeJeu.tabTailleDecks);
	free(tableDeJeu.pioche);
}


void freeJoueur(joueur j) {
	free(j.deck);
}
