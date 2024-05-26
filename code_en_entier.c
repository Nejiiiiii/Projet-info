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
int main();

// Fonction pour lire un entier de manière sécurisée.
int lireEntier() {
    int valeur;
    while (scanf("%d", &valeur) != 1) {
        printf("Entrée invalide. Veuillez entrer un nombre entier: ");
        while (getchar() != '\n'); 
    }
    return valeur;
}

// Fonction pour initialiser l'utilisateur.
void initialiserUtilisateur() {
    utilisateur.nombreReservations = 0;
}

// Fonction pour vérifier si une heure est valide.
int heureValide(float heure) {
    int heures = (int)heure;
    int minutes = (int)((heure - heures) * 100);
    return (heures >= 0 && heures < 24) && (minutes >= 0 && minutes < 60);
}

// Fonction pour vérifier si une catégorie est valide.
int categorieValide(char categorie) {
    return categorie == 'a' || categorie == 'b' || categorie == 'c';
}

// Fonction pour afficher les sièges de la salle.
void afficherPlanSalle(Salle *salle) {
    printf("Plan de la salle %s:\n", salle->nom);
    printf("SCENE\n");
    printf("-------------------------------\n");

    // Boucle pour chaque rangée de la salle.
    for (int i = 0; i < salle->nbRanges; i++) {

        // Affichage du numéro de la rangée (1-indexé).
        printf("R%d ", i + 1);

        // Boucle pour afficher chaque siège dans la rangée.
        for (int j = 0; j < salle->chaiseparRanges[i]; j++) {

            // Vérifier si le siège est réservé.
            if (salle->reserve[i][j] == 1) {
                printf("X "); // Siège réservé
            } else {
                printf("O "); // Siège disponible
            }
        }
        printf("\n");
    }
    printf("Légende:\n");

    // Boucle pour afficher les différentes catégories et les prix de chaque rangée.
    for (int i = 0; i < salle->nbRanges; i++) {
        printf("R%d: Catégorie %c, Prix: %.2f euros\n", i + 1, salle->categories[i], salle->prix[i]);
    }
    printf("X - Siège réservé\n");
    printf("O - Siège disponible\n");
}

// Fonction pour réserver un siège d'un concert.
void reserverSiege(Concert concerts[], int nbConcerts, Utilisateur *utilisateur) {
    int choixConcert, choixSalle, choixRangee, choixSiege;

    // Demande à l'utilisateur de choisir un concert à réserver.
    printf("Choisissez un concert à réserver (1 à %d, 0 pour retourner): ", nbConcerts);
    choixConcert = lireEntier();

    // Si l'utilisateur choisit 0, retourne au menu précédent.
    if (choixConcert == 0) return;

    //Conversion du numero dans un index valable pour le tableau.
    choixConcert -= 1;

    // Vérifie si le numéro de concert est valide.
    if (choixConcert < 0 || choixConcert >= nbConcerts) {
        printf("Numéro de concert invalide.\n");
        return;
    }

    // Pointeur vers le concert choisi.
    Concert *concertChoisi = &concerts[choixConcert];
    
    // Securisation, si le concert a des salles assignées.
    if (concertChoisi->nbSalles == 0) {
        printf("Ce concert n'a pas de salle assignée.\n");
        return;
    }

    // Demande envers l'utilisateur de choisir une salle pour le concert.
    printf("Choisissez une salle pour ce concert (1 à %d, 0 pour retourner): ", concertChoisi->nbSalles);
    for (int i = 0; i < concertChoisi->nbSalles; i++) {
        printf("%d. %s\n", i + 1, salles[concertChoisi->sallesIndex[i]].nom);
    }
    choixSalle = lireEntier();

    // Retour au menu précédent.
    if (choixSalle == 0) return;
    
    // Numero de salle passé en index du tableau.
    choixSalle -= 1;

    //Securisation salle valide.
    if (choixSalle < 0 || choixSalle >= concertChoisi->nbSalles) {
        printf("Numéro de salle invalide.\n");
        return;
    }

    // Pointeur qui pointe vers la salle choisie.
    Salle *salle = &salles[concertChoisi->sallesIndex[choixSalle]];

    // Affichage du plan de la salle choisie.
    afficherPlanSalle(salle);

    printf("Choisissez une rangée (1 à %d, 0 pour retourner): ", salle->nbRanges);
    choixRangee = lireEntier();

    // Retour au menu.
    if (choixRangee == 0) return;
    
     // Numero de rangée passé en index du tableau.
    choixRangee -= 1;

    //Securisation de la rangée valide.
    if (choixRangee < 0 || choixRangee >= salle->nbRanges) {
        printf("Numéro de rangée invalide.\n");
        return;
    }

    // Demande à l'utilisateur de choisir un siège dans la rangée choisie au préalable.
    printf("Choisissez un siège (1 à %d, 0 pour retourner): ", salle->chaiseparRanges[choixRangee]);
    choixSiege = lireEntier();

    // Retour menu.
    if (choixSiege == 0) return;

    // Numero du siège passé en index du tableau.
    choixSiege -= 1;


    if (choixSiege < 0 || choixSiege >= salle->chaiseparRanges[choixRangee]) {
        printf("Numéro de siège invalide.\n");
        return;
    }

    // Vérification pour voir si le siège est déjà réservé.
    if (salle->reserve[choixRangee][choixSiege] == 1) {
        printf("Ce siège est déjà réservé.\n");
        return;
    }

    // Marque le siège comme réservé.
    salle->reserve[choixRangee][choixSiege] = 1;

    // Création d'une nouvelle réservation et la remplire.
    Reservation reservation;
    strcpy(reservation.nomConcert, concertChoisi->nom);
    strcpy(reservation.date, "28/06/2024"); // Date fictive.
    reservation.rangee = choixRangee;
    reservation.siege = choixSiege;
    reservation.categorie = salle->categories[choixRangee];
    reservation.prix = salle->prix[choixRangee];

    // Ajoute la réservation à l'utilisateur.
    utilisateur->reservations[utilisateur->nombreReservations++] = reservation;

    printf("Réservation réussie pour le concert %s, salle %s, rangée %d, siège %d.\n", concertChoisi->nom, salle->nom, choixRangee + 1, choixSiege + 1);
}

void afficherConcerts(Concert concerts[], int nbConcerts, Salle salles[]) {
   
    // Boucle pour chaque concert crée.
    for (int i = 0; i < nbConcerts; i++) {
        printf("Concert %d:\n", i + 1);
        printf("Nom: %s\n", concerts[i].nom);
        printf("Heure de début: %.2f\n", concerts[i].heuredebut);
        printf("Heure de fin: %.2f\n", concerts[i].heurefin);
        printf("Salles:\n");

        // Boucle pour chaque salle assignée au concert.
        for (int j = 0; j < concerts[i].nbSalles; j++) {

            // Pointeur vers la salle actuelle.
            Salle *salle = &salles[concerts[i].sallesIndex[j]];
            printf("  Salle %d: %s\n", j + 1, salle->nom);

            // Compte du nombre total de rangées dans la salle.
            int totalRangees = salle->nbRanges;
            
            // Initialisation du compteur du nombre total de sièges.
            int totalSieges = 0;

            // Boucle pour compter le nombre total de sièges dans toutes les rangées de la salle.
            for (int k = 0; k < salle->nbRanges; k++) {
                totalSieges += salle->chaiseparRanges[k];
            }
            printf("    Nombre de rangées: %d\n", totalRangees);
            printf("    Nombre de sièges: %d\n", totalSieges);
        }

        // Boucle qui affiche les artistes du concert.
        for (int j = 0; j < concerts[i].nbArtistes; j++) {
            printf("  Artiste %d: %s\n", j + 1, concerts[i].artistes[j]);
        }
    }
}

void voirMesReservations(Utilisateur utilisateur) {

    // Affiche le nom de l'utilisateur pour lequel les réservations sont affichées.
    printf("Réservations pour l'utilisateur %s:\n", utilisateur.nom);

    // Boucle pour obtenir la réservation actuelle de chaque utilisateur.
    for (int i = 0; i < utilisateur.nombreReservations; i++) {
        Reservation res = utilisateur.reservations[i];

        // Affiche les détails de la réservation.
        printf("Concert: %s, Date: %s, Rangée: %d, Siège: %d, Catégorie: %c, Prix: %.2f\n",
               res.nomConcert, res.date, res.rangee + 1, res.siege + 1, res.categorie, res.prix);
    }
}

// Mode festivalier pour un utilisateur.
void modeFestivalier(Concert concerts[], int nbConcerts, Utilisateur *utilisateur, Salle salles[]) {
    
    // Initialise l'utilisateur en réinitialisant ses réservations.
    initialiserUtilisateur();
    int choix;

    // Boucle do-while pour afficher le menu et traiter les choix de l'utilisateur.
    do {
        printf("\n-== Menu Festivalier ==-\n");
        printf("1. Réserver un siège\n");
        printf("2. Voir les concerts disponibles\n");
        printf("3. Voir mes réservations\n");
        printf("0. Retour au menu principal\n");
        printf("Entrez votre choix: ");
        choix = lireEntier();

        switch (choix) {
            case 1:
                reserverSiege(concerts, nbConcerts, utilisateur);
                break;
            case 2:
                afficherConcerts(concerts, nbConcerts, salles);
                break;
            case 3:
                voirMesReservations(*utilisateur);
                break;
            case 0:
                printf("Retour au menu principal...\n");
                break;
            default:
                printf("Choix invalide, veuillez réessayer.\n");
        }
    // Continue à afficher le menu tant que l'utilisateur ne choisit pas 0.
    } while (choix != 0);
}

// Fonction pour libérer la mémoire allouée dynamiquement pour les artistes.
void libererMemoire() {
    for (int i = 0; i < nbConcerts; i++) {
        for (int j = 0; j < concert[i].nbArtistes; j++) {
            free(concert[i].artistes[j]);
        }
        free(concert[i].artistes);
    }
}

void sauvegarderDansFichier() {
    FILE *file = fopen("salles.txt", "w");
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    fprintf(file, "%d\n", nbSalles);
    for (int i = 0; i < nbSalles; i++) {
        fprintf(file, "%s\n", salles[i].nom);
        fprintf(file, "%d\n", salles[i].nbRanges);
        for (int j = 0; j < salles[i].nbRanges; j++) {
            fprintf(file, "%d %c %f\n", salles[i].chaiseparRanges[j], salles[i].categories[j], salles[i].prix[j]);
        }
    }

    fclose(file);
    printf("Salles sauvegardées avec succès.\n");
}

void chargerDepuisFichier() {
    FILE *file = fopen("salles.txt", "r");
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    fscanf(file, "%d", &nbSalles);
    for (int i = 0; i < nbSalles; i++) {
        fscanf(file, "%s", salles[i].nom);
        fscanf(file, "%d", &salles[i].nbRanges);
        for (int j = 0; j < salles[i].nbRanges; j++) {
            fscanf(file, "%d %c %f", &salles[i].chaiseparRanges[j], &salles[i].categories[j], &salles[i].prix[j]);
        }
    }

    fclose(file);
    printf("Salles chargées avec succès.\n");
}

void creationConcert() {

    // Vérifie si le nombre maximal de concerts est atteint.
    if (nbConcerts >= MAX_CONCERTS) {
        printf("Nombre maximal de concerts atteint.\n");
        return;
    }

    // Pointeur vers le nouvel emplacement dans le tableau des concerts.
    Concert *nouveauConcert = &concert[nbConcerts];

    printf("Entrez le nom du concert: ");
    scanf("%s", nouveauConcert->nom);

    do {
        printf("Entrez l'heure de début (hh.mm): ");
        if (scanf("%f", &nouveauConcert->heuredebut) != 1 || !heureValide(nouveauConcert->heuredebut)) {
            printf("Heure invalide. Veuillez réessayer.\n");
            while(getchar() != '\n'); // Vide le buffer d'entrée.
        } else {
            break;
        }
    } while (1);

    do {
        printf("Entrez l'heure de fin (hh.mm): ");
        if (scanf("%f", &nouveauConcert->heurefin) != 1 || !heureValide(nouveauConcert->heurefin)) {
            printf("Heure invalide. Veuillez réessayer.\n");
            while(getchar() != '\n'); // Vide le buffer d'entrée.
        } else {
            break;
        }
    } while (1);

    printf("Entrez le nombre d'artistes: ");
    if (scanf("%d", &nouveauConcert->nbArtistes) != 1 || nouveauConcert->nbArtistes < 0) {
        printf("Nombre d'artistes invalide.\n");
        return;
    }

    // Alloue de la mémoire pour le tableau des artistes en fonction du nombre d'artistes.
    nouveauConcert->artistes = (char **)malloc(nouveauConcert->nbArtistes * sizeof(char *));

    // Boucle pour chaque artiste participant au concert.
    for (int i = 0; i < nouveauConcert->nbArtistes; i++) {

        // Alloue de la mémoire pour le nom de chaque artiste.
        nouveauConcert->artistes[i] = (char *)malloc(100 * sizeof(char));

        // Demande à l'utilisateur d'entrer le nom de l'artiste i+1.
        printf("Entrez le nom de l'artiste %d: ", i + 1);
        scanf("%s", nouveauConcert->artistes[i]);
    }

     // Incrémentation du compteur de concerts.
    nbConcerts++;
    printf("Concert créé avec succès.\n");
}

void afficherConcertsManager() {

    // Boucle pour chaque concert existant.
    for (int i = 0; i < nbConcerts; i++) {
        printf("Concert %d:\n", i + 1);
        printf("Nom: %s\n", concert[i].nom);
        printf("Heure de début: %.2f\n", concert[i].heuredebut);
        printf("Heure de fin: %.2f\n", concert[i].heurefin);

        // Boucle pour chaque artiste participant au concert.
        for (int j = 0; j < concert[i].nbArtistes; j++) {
            printf("  Artiste %d: %s\n", j + 1, concert[i].artistes[j]);
        }
    }
}

void modifierConcert() {
    int choix;
    printf("Entrez le numéro du concert à modifier: ");
    choix = lireEntier();

    //Vérification, le num. du concert doit exister.
    if (choix < 1 || choix > nbConcerts) {
        printf("Numéro de concert invalide.\n");
        return;
    }

    //Transformation en index de tableau.
    choix -= 1;

    // Pointeur vers le concert à modifier.
    Concert *modifConcert = &concert[choix];

    printf("Modifier le nom (actuel: %s): ", modifConcert->nom);
    scanf("%s", modifConcert->nom);

    do {
        printf("Modifier l'heure de début (actuelle: %.2f): ", modifConcert->heuredebut);
        if (scanf("%f", &modifConcert->heuredebut) != 1 || !heureValide(modifConcert->heuredebut)) {
            printf("Heure invalide. Veuillez réessayer.\n");
            while(getchar() != '\n'); // Vide le buffer d'entrée.
        } else {
            break;
        }
    } while (1);

    do {
        printf("Modifier l'heure de fin (actuelle: %.2f): ", modifConcert->heurefin);
        if (scanf("%f", &modifConcert->heurefin) != 1 || !heureValide(modifConcert->heurefin)) {
            printf("Heure invalide. Veuillez réessayer.\n");
            while(getchar() != '\n'); // Vide le buffer d'entrée.
        } else {
            break;
        }
    } while (1);

    printf("Modifier le nombre d'artistes (actuel: %d): ", modifConcert->nbArtistes);
    if (scanf("%d", &modifConcert->nbArtistes) != 1 || modifConcert->nbArtistes < 0) {
        printf("Nombre d'artistes invalide.\n");
        return;
    }

    // Réallocation de la mémoire pour le tableau des artistes en fonction du nouveau nombre d'artistes.
    modifConcert->artistes = (char **)realloc(modifConcert->artistes, modifConcert->nbArtistes * sizeof(char *));
    
    // Boucle pour modifier le nom de chaque artiste.
    for (int i = 0; i < modifConcert->nbArtistes; i++) {

        // Allocation de mémoire pour chaque nom d'artiste.
        modifConcert->artistes[i] = (char *)malloc(100 * sizeof(char));
        printf("Modifier le nom de l'artiste %d: ", i + 1);
        scanf("%s", modifConcert->artistes[i]);
    }

    printf("Concert modifié avec succès.\n");
}

void assignerSalleToConcert() {
    int choixConcert, choixSalle;
    printf("Entrez le numéro du concert: ");
    choixConcert = lireEntier();

    // Vérifie si le numéro du concert est valide (il doit être compris entre 1 et le nombre de concerts crées).
    if (choixConcert < 1 || choixConcert > nbConcerts) {
        printf("Numéro de concert invalide.\n");
        return;
    }

    //Transformation du choix en index valable pour les tableaux.
    choixConcert -= 1;

    printf("Entrez le numéro de la salle: ");
    choixSalle = lireEntier();

    //Deuxieme verification mais pour les salles.
    if (choixSalle < 1 || choixSalle > nbSalles) {
        printf("Numéro de salle invalide.\n");
        return;
    }

    //Deuxieme transformation en index valable.
    choixSalle -= 1;

    // Assigne la salle sélectionnée au concert en ajoutant l'index de la salle au tableau sallesIndex du concert.
    concert[choixConcert].sallesIndex[concert[choixConcert].nbSalles] = choixSalle;

    // Incrémentation du compteur de salles pour ce concert.
    concert[choixConcert].nbSalles++;
    printf("Salle assignée avec succès.\n");
}

void menuConcerts() {
    int choix;

    // Boucle do-while pour afficher le menu et traiter les choix de l'utilisateur tant que la réponse n'est pas 0.
    do {
        printf("\n-== Menu des Concerts ==-\n");
        printf("1. Créer un concert\n");
        printf("2. Afficher les concerts\n");
        printf("3. Modifier un concert\n");
        printf("4. Assigner une salle à un concert\n");
        printf("0. Retour au menu principal\n");
        printf("Entrez votre choix: ");
        choix = lireEntier();

        //Appel aux differentes fonctions selon la réponse de l'utilisateur.
        switch (choix) {
            case 1:
                creationConcert();
                break;
            case 2:
                afficherConcertsManager();
                break;
            case 3:
                modifierConcert();
                break;
            case 4:
                assignerSalleToConcert();
                break;
            case 0:
                printf("Retour au menu principal...\n");
                break;
            default:
                printf("Choix invalide, veuillez réessayer.\n");
        }
    } while (choix != 0);
}

void creerSalle() {

    // Vérifie si le nombre maximum de salles est atteint.
    if (nbSalles >= MAX_SALLES) {
        printf("Nombre maximal de salles atteint.\n");
        return;
    }

    // Pointeur vers la nouvelle salle dans le tableau 'salles'.
    Salle *nouvelleSalle = &salles[nbSalles];

    printf("Entrez le nom de la salle: ");
    scanf("%s", nouvelleSalle->nom);

    printf("Entrez le nombre de rangées: ");
    nouvelleSalle->nbRanges = lireEntier();
    if (nouvelleSalle->nbRanges <= 0 || nouvelleSalle->nbRanges > MAX_RANGES) {
        printf("Nombre de rangées invalide.\n");
        return;
    }

    for (int i = 0; i < nouvelleSalle->nbRanges; i++) {
        printf("Entrez le nombre de chaises pour la rangée %d: ", i + 1);
        nouvelleSalle->chaiseparRanges[i] = lireEntier();
        if (nouvelleSalle->chaiseparRanges[i] <= 0 || nouvelleSalle->chaiseparRanges[i] > MAX_CHAISE) {
            printf("Nombre de chaises invalide.\n");
            return;
        }
        printf("Entrez la catégorie pour la rangée %d: ", i + 1);
        scanf(" %c", &nouvelleSalle->categories[i]);
        if (!categorieValide(nouvelleSalle->categories[i])) {
            printf("Catégorie invalide. Veuillez entrer 'a', 'b' ou 'c'.\n");
            return;
        }
        printf("Entrez le prix pour la rangée %d: ", i + 1);
        if (scanf("%f", &nouvelleSalle->prix[i]) != 1 || nouvelleSalle->prix[i] < 0) {
            printf("Prix invalide.\n");
            return;
        }
    }

    // Incrémente le compteur de salles(qui servira pour pouvoir les modifier et/ou selectioner).
    nbSalles++;
    printf("Salle créée avec succès.\n");
}

void afficherSalles() {
    for (int i = 0; i < nbSalles; i++) {
        printf("Salle %d:\n", i + 1);
        printf("Nom: %s\n", salles[i].nom);
        printf("Nombre de rangées: %d\n", salles[i].nbRanges);
        for (int j = 0; j < salles[i].nbRanges; j++) {
            printf("  Rangée %d: %d chaises, Catégorie: %c, Prix: %.2f\n",
                   j + 1, salles[i].chaiseparRanges[j], salles[i].categories[j], salles[i].prix[j]);
        }
    }
}

void modifierSalle() {
    int choix;
    printf("Entrez le numéro de la salle à modifier: ");
    choix = lireEntier();

    // Vérification pour voir si le numéro de salle est valide (doit être compris entre 1 et le nombre de salles existantes).
    if (choix < 1 || choix > nbSalles) {
        printf("Numéro de salle invalide.\n");
        return;
    }

    //Étape pour convertir le numéro du choix en élement correspondant au tableau.
    choix -= 1;

    // Pointeur vers la salle à modifier.
    Salle *modifSalle = &salles[choix];

    printf("Modifier le nom (actuel: %s): ", modifSalle->nom);
    scanf("%s", modifSalle->nom);

    printf("Modifier le nombre de rangées (actuel: %d): ", modifSalle->nbRanges);
    modifSalle->nbRanges = lireEntier();
    if (modifSalle->nbRanges <= 0 || modifSalle->nbRanges > MAX_RANGES) {
        printf("Nombre de rangées invalide.\n");
        return;
    }

    //Boucle pour modifier rangée par rangée.
    for (int i = 0; i < modifSalle->nbRanges; i++) {
        printf("Modifier le nombre de chaises pour la rangée %d (actuel: %d): ", i + 1, modifSalle->chaiseparRanges[i]);
        modifSalle->chaiseparRanges[i] = lireEntier();
        if (modifSalle->chaiseparRanges[i] <= 0 || modifSalle->chaiseparRanges[i] > MAX_CHAISE) {
            printf("Nombre de chaises invalide.\n");
            return;
        }
        printf("Modifier la catégorie pour la rangée %d (actuelle: %c): ", i + 1, modifSalle->categories[i]);
        scanf(" %c", &modifSalle->categories[i]);
        if (!categorieValide(modifSalle->categories[i])) {
            printf("Catégorie invalide. Veuillez entrer 'a', 'b' ou 'c'.\n");
            return;
        }
        printf("Modifier le prix pour la rangée %d (actuel: %.2f): ", i + 1, modifSalle->prix[i]);
        if (scanf("%f", &modifSalle->prix[i]) != 1 || modifSalle->prix[i] < 0) {
            printf("Prix invalide.\n");
            return;
        }
    }

    printf("Salle modifiée avec succès.\n");
}

void modeManager() {
    int choix;
    do {
        printf("\n-== Menu Manager ==-\n");
        printf("1. Gérer les salles\n");
        printf("2. Gérer les concerts\n");
        printf("3. Sauvegarder les données\n");
        printf("4. Charger les données\n");
        printf("0. Retour au menu principal\n");
        printf("Entrez votre choix: ");
        choix = lireEntier();

        switch (choix) {
            case 1://Sous-menu salles.
                printf("\n-== Gestion des Salles ==-\n");
                printf("1. Créer une salle\n");
                printf("2. Afficher les salles\n");
                printf("3. Modifier une salle\n");
                printf("0. Retour au menu manager\n");
                printf("Entrez votre choix: ");
                int choixSalle;
                choixSalle = lireEntier();

                switch (choixSalle) {
                    case 1:
                        creerSalle();
                        break;
                    case 2:
                        afficherSalles();
                        break;
                    case 3:
                        modifierSalle();
                        break;
                    case 0:
                        printf("Retour au menu manager\n");
                        break;
                    default:
                        printf("Choix invalide, veuillez réessayer.\n");
                }
                break;
            case 2:
                menuConcerts();//Sous-menu concerts.
                break;
            case 3:
                sauvegarderDansFichier();
                break;
            case 4:
                chargerDepuisFichier();
                break;
            case 0:
                printf("Retour au menu principal\n");
                break;
            default:
                printf("Choix invalide, veuillez réessayer.\n");
        }
    } while (choix != 0);
}

void menuPrincipal() {
    int choix;

    do {
        printf("\n-== Menu Principal ==-\n");
        printf("1. Mode Festivalier\n");
        printf("2. Mode Manager\n");
        printf("0. Quitter\n");
        printf("Entrez votre choix: ");
        choix = lireEntier();

        switch (choix) {
            case 1:
                modeFestivalier(concert, nbConcerts, &utilisateur, salles);
                break;
            case 2:
                modeManager();
                break;
            case 0:
                libererMemoire();
                printf("FIN PROGRAMME\n");
                break;
            default:
                printf("Choix invalide, veuillez réessayer.\n");
        }
    } while (choix != 0);
}

int main() {
    menuPrincipal();
    return 0;
}

