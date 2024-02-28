#include <stdlib.h>
#include "structures.h"

// Fonction tri fusion qui trie les cartes en fonction de leurs numéros
void triFusionDeCartes(carte* tabCartes, int debut, int fin){ // triFusionDeCartes(deckJoueur, 0, n-1)
	int p;
	carte* tmp;
	if (debut<fin){
		p=(debut+fin)/2;
		triFusionDeCartes(tabCartes,debut,p);
		triFusionDeCartes(tabCartes,p+1,fin);
		int g=debut;
		int d=p+1;
		tmp=malloc((fin+1)*sizeof(carte));
		int i=0;
		while (g<=p && d<=fin){
			if (tabCartes[g].numero<tabCartes[d].numero){
				tmp[i]=tabCartes[g];
				g++;
			}
			else {
				tmp[i]=tabCartes[d];
				d++;
			}
			i++;
		}
		while (g<=p){
			tmp[i]=tabCartes[g];
			g++;
			i++;
		}
		while (d<=fin){
			tmp[i]=tabCartes[d];
			d++;
			i++;
		}
		for (i=0;i<(fin-debut)+1;i++){
			tabCartes[i+debut]=tmp[i];
		}
		free(tmp);
	}
}

// Fonction tri fusion qui trie les cartes en fonction de leurs numéros
void triFusionJoueur(carte* tabCartes, int* tabNumero, int debut, int fin){ // triFusionDeCartes(deckJoueur, 0, n-1)
	int p;
	carte* tmp;
	int* tmpNumero;
	if (debut<fin){
		p=(debut+fin)/2;
		triFusionJoueur(tabCartes,tabNumero,debut,p);
		triFusionJoueur(tabCartes,tabNumero,p+1,fin);
		int g=debut;
		int d=p+1;
		tmp=malloc((fin+1)*sizeof(carte));
		tmpNumero=malloc((fin+1)*sizeof(int));
		int i=0;
		while (g<=p && d<=fin){
			if (tabCartes[g].numero<tabCartes[d].numero){
				tmp[i]=tabCartes[g];
				tmpNumero[i] = tabNumero[g];
				g++;
			}
			else {
				tmp[i]=tabCartes[d];
				tmpNumero[i] = tabNumero[d];
				d++;
			}
			i++;
		}
		while (g<=p){
			tmp[i]=tabCartes[g];
			tmpNumero[i] = tabNumero[g];
			g++;
			i++;
		}
		while (d<=fin){
			tmp[i]=tabCartes[d];
			tmpNumero[i] = tabNumero[d];
			d++;
			i++;
		}
		for (i=0;i<(fin-debut)+1;i++){
			tabCartes[i+debut]=tmp[i];
			tabNumero[i+debut] = tmpNumero[i];
		}
		free(tmp);
		free(tmpNumero);
	}
}

void fusionner(joueur* joueurs,int debut,int milieu,int fin){
    int i=0;
    int max=fin-debut;
    int gauche=debut;
    int droite=milieu+1;
    joueur* tmp;
    tmp=malloc(sizeof(joueur)*(fin+1));
    while ((gauche<=milieu)&&(droite<=fin)){
        if (joueurs[gauche].score<joueurs[droite].score){
            tmp[i]=joueurs[gauche];
            gauche++;
        }
        else {
            tmp[i]=joueurs[droite];
            droite++;
        }
        i++;
    }
    while (gauche<=milieu){
        tmp[i]=joueurs[gauche];
        gauche++;i++;
    }
    while (droite<=fin){
        tmp[i]=joueurs[droite];
        droite++;i++;
    }
    for (i = 0; i < max+1; i++){
        joueurs[i+debut]=tmp[i];
    }
    free(tmp);
}

void triFusionScoreboard(joueur* joueurs,int debut,int fin){
    int milieu;
    if (debut<fin){
        milieu=(debut+fin)/2;
        triFusionScoreboard(joueurs,debut,milieu);
        triFusionScoreboard(joueurs,milieu+1,fin);
        fusionner(joueurs,debut,milieu,fin);
    }
}