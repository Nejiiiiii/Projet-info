#ifndef FONCTION_H
#define FONCTION_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Constantes maximales pour les données du programme.
#define MAX_SALLES 100
#define MAX_RANGES 50
#define MAX_CHAISE 100
#define MAX_CONCERTS 100
#define MAX_RESERVATIONS 10

// Structures nécessaires pour enregistrer les données du festival.
typedef struct {
    char nom[100];
    int nbRanges;
    int chaiseparRanges[MAX_RANGES];
    char categories[MAX_RANGES];
    float prix[MAX_RANGES];
    int reserve[MAX_RANGES][MAX_CHAISE];
} Salle;

typedef struct {
    char nomConcert[100];
    char date[11];
    int rangee;
    int siege;
    char categorie;
    double prix;
} Reservation;

typedef struct {
    char nom[100];
    char **artistes;
    float heuredebut;
    float heurefin;
    int nbArtistes;
    int sallesIndex[MAX_SALLES]; // Liste des indices des salles où se déroule le concert.
    int nbSalles;
} Concert;

typedef struct {
    char nom[100];
    int nombreReservations;
    Reservation reservations[MAX_RESERVATIONS];
} Utilisateur;

// Déclarations des variables globales.
Concert concert[MAX_CONCERTS];
int nbConcerts = 0;
Salle salles[MAX_SALLES];
int nbSalles = 0;
Utilisateur utilisateur;

// Déclaration explicite des fonctions.
void initialiserUtilisateur();
void afficherPlanSalle(Salle *salle);
void reserverSiege(Concert concerts[], int nbConcerts, Utilisateur *utilisateur);
void afficherConcerts(Concert concerts[], int nbConcerts, Salle salles[]);
void voirMesReservations(Utilisateur utilisateur);
void modeFestivalier(Concert concerts[], int nbConcerts, Utilisateur *utilisateur, Salle salles[]);
void libererMemoire();
void creationConcert();
void afficherConcertsManager();
void modifierConcert();
void assignerSalleToConcert();
void menuConcerts();
void creerSalle();
void afficherSalles();
void modifierSalle();
void sauvegarderDansFichier();
void chargerDepuisFichier();
void modeManager();
void menuPrincipal();
int lireEntier();
#endif
