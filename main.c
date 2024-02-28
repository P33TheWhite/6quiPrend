#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "structures.h"
#include "fonctions.h"
#include "affichage.h"
#include "tris.h"

#define ROUGE "\x1B[0;31m"
#define JAUNE "\x1B[33m"
#define CYAN   "\x1B[36m"
#define BLANC "\e[0;97m"
#define RESET "\x1B[0m"



int main() {
    system("clear");
    srand(time(NULL));
    // Initialisation des variables
    int conditionDeManche;
    int compteurManche=0;
    int compteurTour;
    int nombreJoueurs;
    int scoreMax=66;

    // Affichage début du jeu
    char message[200];
    affTableCache();
    printf("Bienvenue dans le 6quiprend !\nConseil : Mettez votre terminal en PLEIN ÉCRAN ! \n");
    afficherBox("Appuyez sur ENTRÉE pour commencer une partie");
    getchar();
    system("clear");

    // Choix du Score maximum
    affTableCache();
    printf("Bienvenue dans le 6quiprend !\nConseil : Mettez votre terminal en PLEIN ÉCRAN ! \n");
    afficherBox("Saisissez le SCORE maximum (66 est recommandé pour une partie d'environ 45 min) : ");
    scanf("%d", &scoreMax);

    if (scoreMax < 1 || scoreMax > 500) {
        printf(ROUGE "Score maximum incorrect" RESET" \n");
        exit(EXIT_FAILURE);

    }

    // Choix du nombre de joueurs et leurs noms
    system("clear");
    affTableCache();
    printf("Bienvenue dans le 6quiprend !\nConseil : Mettez votre terminal en PLEIN ÉCRAN ! \n");
    afficherBox("Saisissez le nombre de JOUEURS (entre 2 et 10) : ");
    scanf("%d", &nombreJoueurs);


    if (nombreJoueurs < 2 || nombreJoueurs > 10){
        printf(ROUGE "Erreur sur le nombre de joueurs !" RESET" \n");
        exit(EXIT_FAILURE);
    }

    videBuffer();
    joueur* joueurs = malloc(nombreJoueurs * sizeof(joueur));
    int* tabPosCarteSelect = malloc(nombreJoueurs * sizeof(int));
    printf("Pour ajouter un "CYAN"robot"RESET", tapez "CYAN"!PseudoDuRobot"RESET" ou appuyez sur ENTRÉE\n");
    for (int i = 0; i < nombreJoueurs; i++) {
        initJoueur(joueurs,i);
    }
        
    // Initialisation du tableau des scores
    scoreboard scboard;
    initScoreboard(&scboard,joueurs,nombreJoueurs,scoreMax);

    while (conditionDeJeu(joueurs,nombreJoueurs,scoreMax)) {
        // Incrément du compteur de manche et remise à 0 du compteur de tour
        compteurManche++;
        compteurTour =0;

        

        // Initialisation de la table de jeu
        table tableDeJeu;
        initTable(&tableDeJeu);
    
        // Initialisation des decks des joueurs
        for (int i = 0; i < nombreJoueurs; i++) {
            // Au début du jeu, le joueur pioche 10 cartes
            for (int k =0; k<10;k++) {
                piocherVersJoueur(&tableDeJeu,&joueurs[i]); // son tailleDeck augmente et taillePioche décrémente automatiquement grâce à la fonction
            }
            triFusionDeCartes(joueurs[i].deck,0,joueurs[i].tailleDeck-1);
        }

        system("clear"); // Permet d'effacer ce qui a été précedemment affiché dans le terminal

        // Condition de Jeu à déterminer
        conditionDeManche = 1;
        while (conditionDeManche) {
            compteurTour++;
            conditionDeManche = compteurTour !=10;

            // Phase 1 : Sélection des cartes pour chaque joueur
            for (int i = 0; i < nombreJoueurs; i++) { // Pour chaque joueur : faire
                int posCarteSelect;
                

                if (joueurs[i].estRobot) { // Si le joueur est un robot
                posCarteSelect = rand()%(11-compteurTour) +1;
                } else {    // Sinon si le joueur n'est pas un robot

                
                
                    afficherTable(tableDeJeu, &scboard);
                    printf("\nManche %d | Tour n°%d (%d/%d)\n", compteurManche,compteurTour,i+1,nombreJoueurs);
                    sprintf(message,JAUNE "%s" RESET ", Appuyez sur ENTRÉE",joueurs[i].pseudo);
                    afficherBox(message);
                    getchar();
                    system("clear");

                    
                    afficherTable(tableDeJeu, &scboard);
                    printf("\n " JAUNE"%s"RESET", à vous de jouer\n", joueurs[i].pseudo); // JAUNE: \e[0;33m , reset couleur: \033[0m

                    affDeckJoueur(joueurs[i].deck,joueurs[i].tailleDeck);
                
                    
                    int retour=0;
                    int nombre=0;
                    // Boucle qui attend une entrée correcte du joueur (un nombre entre 1 et la taille de son deck)
                    do {
                        if (nombre<1){
                            printf("Choisissez une " CYAN"carte" RESET" (1 étant la 1ère carte) :\n");
                        }
                        else if(nombre<10){
                            printf(ROUGE "Erreur de saisie" RESET ", veuillez choisir une " CYAN"carte"RESET" (1 étant la 1ère carte) :\n");
                        }
                        else {
                            printf(ROUGE "Trop d'erreurs, le programme va se fermer.\n" RESET);
                            exit(EXIT_FAILURE);
                        }
                        retour=scanf("%d", &posCarteSelect);
                        videBuffer();
                        nombre++;
                    }while (posCarteSelect>11-compteurTour||posCarteSelect<1||!retour);
                }

                posCarteSelect = posCarteSelect -1; // Adaptation aux indices des tableaux

                tabPosCarteSelect[i] = posCarteSelect; // Stockage des positions des cartes choisies pour chaque joueur
    
                //Passage joueur suivant
                system("clear");
            }  
        
            int* tabNumeroJoueurs = malloc(sizeof(int)*nombreJoueurs);
            carte* tabCarteSelect = malloc(sizeof(carte)*nombreJoueurs);
            for (int i=0; i<nombreJoueurs; i++) {
                    tabNumeroJoueurs[i] = i;
                    tabCarteSelect[i] = joueurs[i].deck[tabPosCarteSelect[i]];
                }


            
            // Phase 2 : Jeu : résultat 
            
            afficherTable(tableDeJeu, &scboard);
            printf("\n\n");
            sprintf(message,"Manche %d | Récap. du tour n°%d", compteurManche,compteurTour);
            afficherBox(message);
            getchar();
            system("clear");

            for (int i = 0; i < nombreJoueurs; i++) {
                
                int vaAcheter;
                
                int k,ancienScore,nouveauScore,differenceScore;
                
                // Pose des cartes en fonction de l'ordre de joueurs déterminé en fonction des numéros des cartes (ordre croissant)
                triFusionJoueur(tabCarteSelect,tabNumeroJoueurs,0,nombreJoueurs-1); // Définit l'ordre de passage des joueurs
                k = tabNumeroJoueurs[i];
                ancienScore = joueurs[k].score; // Récupération de l'ancien score
                vaAcheter = jouerCarteVersTable(&joueurs[k],tabPosCarteSelect[k],&tableDeJeu); // Modification du deck du joueur et de la table de jeu
                

                
                if (vaAcheter) {
                    afficherTable(tableDeJeu, &scboard);
                    printf("\nManche %d | Récap. du tour n°%d (%d/%d)\n", compteurManche,compteurTour,i+1,nombreJoueurs);
                    sprintf(message, JAUNE"%s"RESET", quelle rangée voulez-vous acheter ? "CYAN"1"RESET" (Haut) à "CYAN"4"RESET" (Bas)", joueurs[k].pseudo); 
                    afficherBox(message);
                    int indexRangee;
                    
                    if (joueurs[k].estRobot) { // Si le joueur est un robot
                        indexRangee = plusPetitTotalTdB(&tableDeJeu);
                    } 
                    
                    else { // Boucle pour humain
                        do {
                            scanf("%d",&indexRangee);
                            videBuffer();
                        } while (indexRangee>4||indexRangee<1);
                        indexRangee--;
                    }
                    acheterLigneTable(&joueurs[k],tabPosCarteSelect[k],indexRangee,&tableDeJeu);
                    system("clear");
                    
                }

                // Affichage
                afficherTable(tableDeJeu, &scboard);
                printf("\nManche %d | Récap du tour n°%d (%d/%d)\n", compteurManche,compteurTour,i+1,nombreJoueurs);
                                    nouveauScore = joueurs[k].score; // Récupération du nouveau score
                differenceScore = nouveauScore - ancienScore;
                if (differenceScore != 0) { // Message personnalisé en fonction d'un gain de TdB
                    if (joueurs[k].estRobot){
                        sprintf(message,"Jeu de "CYAN "%s 🤖"RESET" | " ROUGE"+%d TdB"RESET,joueurs[k].pseudo,differenceScore); // Jeu de X | +n TdB
                    }
                    else {
                    sprintf(message,"Jeu de "JAUNE "%s"RESET" | " ROUGE"+%d TdB"RESET,joueurs[k].pseudo,differenceScore); // Jeu de X | +n TdB
                    }
                } 
                else {
                    if (joueurs[k].estRobot){
                        sprintf(message,"Jeu de "CYAN "%s 🤖" RESET,joueurs[k].pseudo); // Jeu de X
                    }
                    else {
                        sprintf(message,"Jeu de "JAUNE "%s" RESET,joueurs[k].pseudo); // Jeu de X
                    }
                }
                afficherBox(message);
                getchar();
                system("clear");
        
            }

            free(tabCarteSelect);
            free(tabNumeroJoueurs);

        }

        // Si c'est la fin de la manche : Le 10 tour sont joués et que le score max. n'a pas été dépassé
        if (conditionDeJeu(joueurs,nombreJoueurs,scoreMax)){
            printf("\n");
            affichageScoreFinDeManche(&scboard, nombreJoueurs);
            printf("\n                                        La partie se joue en "ROUGE"%d"RESET"\n\n",scoreMax);
            sprintf(message,"Appuyez sur ENTRÉE pour passer à la manche %d",compteurManche+1);
            afficherBox(message);
            getchar();
            system("clear");

        }

        freeTable(tableDeJeu);
    }


    // FIN : Le score maximum à été dépassé à la fin d'une manche
    // Affichage des résultats
    triFusionScoreboard(joueurs,0,nombreJoueurs-1);
    printf("\n");
    affichageScoreFinDePartie(&scboard, nombreJoueurs);
    if (joueurs[0].estRobot){
        sprintf(message,""JAUNE "%s 🤖"RESET" a gagné la partie !" ,joueurs[0].pseudo);
    }
    else {
        sprintf(message,""JAUNE "%s"RESET" a gagné la partie !" ,joueurs[0].pseudo);
    }
    afficherBox(message);
    printf("\n");


    // Libération de la mémoire allouée
    for (int i = 0; i < nombreJoueurs; i++) {
        free(joueurs[i].pseudo);
        free(joueurs[i].deck);
    }
    free(joueurs);
    free(tabPosCarteSelect);

    return 0;
}