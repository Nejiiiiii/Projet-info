// IL MANQUE L'AFFICHAGE AVEC LES COULEURS LES X, LES O ET LES COULEURS DANS LE MODE FESTIVALIER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SALLES 100
#define MAX_RANGES 50
#define MAX_CHAISE 100
#define MAX_CONCERTS 100
#define MAX_USERS 10
#define MAX_RESERVATIONS 10
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define ANSI_COLOR_WHITE   "\x1b[37m"

typedef struct {
    char nom[100];
    int nbRanges;
    int chaiseparRanges[MAX_RANGES];
    char categories[MAX_RANGES];
    float prix[MAX_RANGES];
    int reserve[MAX_RANGES][MAX_CHAISE];
} Salle;

typedef struct {
    int estReserve;
    double prix;
    int categorie;
    int idUtilisateur;
} Siege;

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
    int salleIndex;
} Concert;

typedef struct {
    int id;
    char nom[100];
    int nombreReservations;
    Reservation reservations[MAX_RESERVATIONS];
} Utilisateur;

Utilisateur* trouverOuCreerUtilisateur(Utilisateur utilisateurs[], int *nbUtilisateurs, const char *nom);
void reserverSiege(Concert concerts[], int nbConcerts, Utilisateur *utilisateur);
void voirConcertsDisponibles(Concert concerts[], int nbConcerts);
void voirMesReservations(Utilisateur utilisateur);
void modeFestivalier(Concert concerts[], int nbConcerts, Utilisateur utilisateurs[], int *nbUtilisateurs);
void libererMemoire();
void saveToFile();
void loadFromFile();
void creationConcert();
void afficherConcerts();
void modifierConcert();
void assignSalleToConcert();
void menuConcerts();
void creerSalle();
void afficherSalles();
void modifierSalle();
void modeManager();
void menuPrincipal();

Concert concert[MAX_CONCERTS];
int nbConcerts = 0;

Salle salles[MAX_SALLES];
int nbSalles = 0;

Utilisateur* trouverOuCreerUtilisateur(Utilisateur utilisateurs[], int *nbUtilisateurs, const char *nom) {
    for (int i = 0; i < *nbUtilisateurs; i++) {
        if (strcmp(utilisateurs[i].nom, nom) == 0) {
            return &utilisateurs[i];
        }
    }
    if (*nbUtilisateurs < MAX_USERS) {
        Utilisateur *nouveauUtilisateur = &utilisateurs[*nbUtilisateurs];
        nouveauUtilisateur->id = *nbUtilisateurs;
        strcpy(nouveauUtilisateur->nom, nom);
        nouveauUtilisateur->nombreReservations = 0;
        (*nbUtilisateurs)++;
        return nouveauUtilisateur;
    } else {
        printf("Nombre maximal d'utilisateurs atteint.\n");
        return NULL;
    }
}

void reserverSiege(Concert concerts[], int nbConcerts, Utilisateur *utilisateur) {
    int choixConcert, choixRangee, choixSiege;
    printf("Choisissez un concert à réserver (0 à %d): ", nbConcerts - 1);
    scanf("%d", &choixConcert);

    if (choixConcert < 0 || choixConcert >= nbConcerts) {
        printf("Numéro de concert invalide.\n");
        return;
    }

    Concert *concertChoisi = &concerts[choixConcert];
    if (concertChoisi->salleIndex == -1) {
        printf("Ce concert n'a pas de salle assignée.\n");
        return;
    }

    Salle *salle = &salles[concertChoisi->salleIndex];

    printf("Choisissez une rangée (0 à %d): ", salle->nbRanges - 1);
    scanf("%d", &choixRangee);

    if (choixRangee < 0 || choixRangee >= salle->nbRanges) {
        printf("Numéro de rangée invalide.\n");
        return;
    }

    printf("Choisissez un siège (0 à %d): ", salle->chaiseparRanges[choixRangee] - 1);
    scanf("%d", &choixSiege);

    if (choixSiege < 0 || choixSiege >= salle->chaiseparRanges[choixRangee]) {
        printf("Numéro de siège invalide.\n");
        return;
    }

    if (salle->reserve[choixRangee][choixSiege]) {
        printf("Ce siège est déjà réservé.\n");
        return;
    }

    salle->reserve[choixRangee][choixSiege] = 1;

    Reservation reservation;
    strcpy(reservation.nomConcert, concertChoisi->nom);
    strcpy(reservation.date, "01/01/2024"); // Date fictive
    reservation.rangee = choixRangee;
    reservation.siege = choixSiege;
    reservation.categorie = salle->categories[choixRangee];
    reservation.prix = salle->prix[choixRangee];

    utilisateur->reservations[utilisateur->nombreReservations++] = reservation;

    printf("Réservation réussie pour le concert %s, rangée %d, siège %d.\n", concertChoisi->nom, choixRangee, choixSiege);
}

void voirConcertsDisponibles(Concert concerts[], int nbConcerts) {
    for (int i = 0; i < nbConcerts; i++) {
        printf("Concert %s:\n", concerts[i].nom);
        printf("Heure de début: %.2f\n", concerts[i].heuredebut);
        printf("Heure de fin: %.2f\n", concerts[i].heurefin);
        printf("Salle assignée: %s\n", (concerts[i].salleIndex != -1) ? salles[concerts[i].salleIndex].nom : "Aucune");
        for (int j = 0; j < concerts[i].nbArtistes; j++) {
            printf("  Artiste nº%d : %s\n", j + 1, concerts[i].artistes[j]);
        }
    }
}

void voirMesReservations(Utilisateur utilisateur) {
    printf("Réservations pour l'utilisateur %s:\n", utilisateur.nom);
    for (int i = 0; i < utilisateur.nombreReservations; i++) {
        Reservation res = utilisateur.reservations[i];
        printf("Concert: %s, Date: %s, Rangée: %d, Siège: %d, Catégorie: %c, Prix: %.2f\n",
               res.nomConcert, res.date, res.rangee, res.siege, res.categorie, res.prix);
    }
}

void modeFestivalier(Concert concerts[], int nbConcerts, Utilisateur utilisateurs[], int *nbUtilisateurs) {
    char nomUtilisateur[100];
    printf("Entrez votre nom: ");
    scanf("%s", nomUtilisateur);

    Utilisateur *utilisateur = trouverOuCreerUtilisateur(utilisateurs, nbUtilisateurs, nomUtilisateur);
    if (!utilisateur) return;

    int choix;
    do {
        printf("\n--- Menu Festivalier ---\n");
        printf("1. Réserver un siège\n");
        printf("2. Voir les concerts disponibles\n");
        printf("3. Voir mes réservations\n");
        printf("4. Retour au menu principal\n");
        printf("Entrez votre choix: ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                reserverSiege(concerts, nbConcerts, utilisateur);
                break;
            case 2:
                voirConcertsDisponibles(concerts, nbConcerts);
                break;
            case 3:
                voirMesReservations(*utilisateur);
                break;
            case 4:
                printf("Retour au menu principal...\n");
                break;
            default:
                printf("Choix invalide, veuillez réessayer.\n");
        }
    } while (choix != 4);
}

void libererMemoire() {
    for (int i = 0; i < nbConcerts; i++) {
        for (int j = 0; j < concert[i].nbArtistes; j++) {
            free(concert[i].artistes[j]);
        }
        free(concert[i].artistes);
    }
}

void saveToFile() {
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
            for (int k = 0; k < salles[i].chaiseparRanges[j]; k++) {
                fprintf(file, "%d ", salles[i].reserve[j][k]);
            }
            fprintf(file, "\n");
        }
    }

    fclose(file);
    printf("Salles sauvegardées avec succès.\n");
}

void loadFromFile() {
    FILE *file = fopen("salles.txt", "r");
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    fscanf(file, "%d\n", &nbSalles);
    for (int i = 0; i < nbSalles; i++) {
        fgets(salles[i].nom, 100, file);
        salles[i].nom[strcspn(salles[i].nom, "\n")] = '\0';
        fscanf(file, "%d\n", &salles[i].nbRanges);
        for (int j = 0; j < salles[i].nbRanges; j++) {
            fscanf(file, "%d %c %f\n", &salles[i].chaiseparRanges[j], &salles[i].categories[j], &salles[i].prix[j]);
            for (int k = 0; k < salles[i].chaiseparRanges[j]; k++) {
                fscanf(file, "%d ", &salles[i].reserve[j][k]);
            }
        }
    }

    fclose(file);
    printf("Salles chargées avec succès.\n");
}

void creationConcert() {
    if (nbConcerts >= MAX_CONCERTS) {
        printf("Nombre maximal de concerts atteint.\n");
        return;
    }

    printf("Saisissez le nom du concert: ");
    scanf("%s", concert[nbConcerts].nom);

    printf("Saisissez l'heure de début: ");
    scanf("%f", &concert[nbConcerts].heuredebut);

    printf("Saisissez l'heure de fin: ");
    scanf("%f", &concert[nbConcerts].heurefin);

    printf("Combien d'artistes vont au concert? ");
    scanf("%d", &concert[nbConcerts].nbArtistes);

    concert[nbConcerts].artistes = (char **)malloc(concert[nbConcerts].nbArtistes * sizeof(char *));
    for (int i = 0; i < concert[nbConcerts].nbArtistes; i++) {
        concert[nbConcerts].artistes[i] = (char *)malloc(100 * sizeof(char));
        printf("Saisissez le nom de l'artiste %d: ", i + 1);
        scanf("%s", concert[nbConcerts].artistes[i]);
    }

    concert[nbConcerts].salleIndex = -1; // Pas de salle assignée initialement

    nbConcerts++;
}

void afficherConcerts() {
    for (int i = 0; i < nbConcerts; i++) {
        printf("Concert %s:\n", concert[i].nom);
        printf("Heure de début: %.2f\n", concert[i].heuredebut);
        printf("Heure de fin: %.2f\n", concert[i].heurefin);
        printf("Salle assignée: %s\n", (concert[i].salleIndex != -1) ? salles[concert[i].salleIndex].nom : "Aucune");
        for (int j = 0; j < concert[i].nbArtistes; j++) {
            printf("  Artiste nº%d : %s\n", j + 1, concert[i].artistes[j]);
        }
    }
}

void modifierConcert() {
    int choix;
    printf("Saisissez le numéro du concert à modifier (0 à %d): ", nbConcerts - 1);
    scanf("%d", &choix);

    if (choix >= 0 && choix < nbConcerts) {
        printf("Saisissez le nouveau nom du concert: ");
        scanf("%s", concert[choix].nom);

        printf("Saisissez la nouvelle heure de début: ");
        scanf("%f", &concert[choix].heuredebut);

        printf("Saisissez la nouvelle heure de fin: ");
        scanf("%f", &concert[choix].heurefin);

        printf("Combien d'artistes vont au concert? ");
        scanf("%d", &concert[choix].nbArtistes);

        concert[choix].artistes = (char **)malloc(concert[choix].nbArtistes * sizeof(char *));
        for (int i = 0; i < concert[choix].nbArtistes; i++) {
            concert[choix].artistes[i] = (char *)malloc(100 * sizeof(char));
            printf("Saisissez le nom de l'artiste %d: ", i + 1);
            scanf("%s", concert[choix].artistes[i]);
        }
    } else {
        printf("Concert invalide.\n");
    }
}

void assignSalleToConcert() {
    int concertIndex, salleIndex;
    printf("Saisissez le numéro du concert (0 à %d): ", nbConcerts - 1);
    scanf("%d", &concertIndex);

    if (concertIndex < 0 || concertIndex >= nbConcerts) {
        printf("Numéro de concert invalide.\n");
        return;
    }

    printf("Saisissez le numéro de la salle (0 à %d): ", nbSalles - 1);
    scanf("%d", &salleIndex);

    if (salleIndex < 0 || salleIndex >= nbSalles) {
        printf("Numéro de salle invalide.\n");
        return;
    }

    concert[concertIndex].salleIndex = salleIndex;
    printf("Salle %s assignée au concert %s.\n", salles[salleIndex].nom, concert[concertIndex].nom);
}

void menuConcerts() {
    int choix;
    do {
        printf("\n--- Menu Concerts ---\n");
        printf("1. Créer un concert\n");
        printf("2. Afficher les concerts\n");
        printf("3. Modifier un concert\n");
        printf("4. Assigner une salle à un concert\n");
        printf("5. Retour au menu principal\n");
        printf("Entrez votre choix: ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                creationConcert();
                break;
            case 2:
                afficherConcerts();
                break;
            case 3:
                modifierConcert();
                break;
            case 4:
                assignSalleToConcert();
                break;
            case 5:
                printf("Retour au menu principal...\n");
                break;
            default:
                printf("Choix invalide, veuillez réessayer.\n");
        }
    } while (choix != 5);
}

void creerSalle() {
    if (nbSalles >= MAX_SALLES) {
        printf("Nombre maximal de salles atteint.\n");
        return;
    }

    printf("Saisissez le nom de la salle: ");
    scanf("%s", salles[nbSalles].nom);

    printf("Saisissez le nombre de rangées: ");
    scanf("%d", &salles[nbSalles].nbRanges);

    for (int i = 0; i < salles[nbSalles].nbRanges; i++) {
        printf("Saisissez le nombre de chaises pour la rangée %d: ", i + 1);
        scanf("%d", &salles[nbSalles].chaiseparRanges[i]);

        printf("Saisissez la catégorie pour la rangée %d: ", i + 1);
        scanf(" %c", &salles[nbSalles].categories[i]);

        printf("Saisissez le prix pour la rangée %d: ", i + 1);
        scanf("%f", &salles[nbSalles].prix[i]);

        for (int j = 0; j < salles[nbSalles].chaiseparRanges[i]; j++) {
            salles[nbSalles].reserve[i][j] = 0; // Initialiser toutes les chaises à non réservées
        }
    }

    nbSalles++;
}

void afficherSalles() {
    for (int i = 0; i < nbSalles; i++) {
        printf("Salle %s:\n", salles[i].nom);
        printf("Nombre de rangées: %d\n", salles[i].nbRanges);
        for (int j = 0; j < salles[i].nbRanges; j++) {
            printf("  Rangée %d: %d chaises, catégorie %c, prix %.2f\n", j + 1, salles[i].chaiseparRanges[j], salles[i].categories[j], salles[i].prix[j]);
        }
    }
}

void modifierSalle() {
    int choix;
    printf("Saisissez le numéro de la salle à modifier (0 à %d): ", nbSalles - 1);
    scanf("%d", &choix);

    if (choix >= 0 && choix < nbSalles) {
        printf("Saisissez le nouveau nom de la salle: ");
        scanf("%s", salles[choix].nom);

        printf("Saisissez le nouveau nombre de rangées: ");
        scanf("%d", &salles[choix].nbRanges);

        for (int i = 0; i < salles[choix].nbRanges; i++) {
            printf("Saisissez le nouveau nombre de chaises pour la rangée %d: ", i + 1);
            scanf("%d", &salles[choix].chaiseparRanges[i]);

            printf("Saisissez la nouvelle catégorie pour la rangée %d: ", i + 1);
            scanf(" %c", &salles[choix].categories[i]);

            printf("Saisissez le nouveau prix pour la rangée %d: ", i + 1);
            scanf("%f", &salles[choix].prix[i]);

            for (int j = 0; j < salles[choix].chaiseparRanges[i]; j++) {
                salles[choix].reserve[i][j] = 0; // Initialiser toutes les chaises à non réservées
            }
        }
    } else {
        printf("Salle invalide.\n");
    }
}

void modeManager() {
    int choix;
    do {
        printf("\n--- Mode Manager ---\n");
        printf("1. Gestion des concerts\n");
        printf("2. Gestion des salles\n");
        printf("3. Sauvegarder\n");
        printf("4. Charger\n");
        printf("5. Retour au menu principal\n");
        printf("Entrez votre choix: ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                menuConcerts();
                break;
            case 2:
                int choixSalle;
                do {
                    printf("\n--- Menu Salles ---\n");
                    printf("1. Créer une salle\n");
                    printf("2. Afficher les salles\n");
                    printf("3. Modifier une salle\n");
                    printf("4. Retour au menu Manager\n");
                    printf("Entrez votre choix: ");
                    scanf("%d", &choixSalle);

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
                        case 4:
                            printf("Retour au menu Manager...\n");
                            break;
                        default:
                            printf("Choix invalide, veuillez réessayer.\n");
                    }
                } while (choixSalle != 4);
                break;
            case 3:
                saveToFile();
                break;
            case 4:
                loadFromFile();
                break;
            case 5:
                printf("Retour au menu principal...\n");
                break;
            default:
                printf("Choix invalide, veuillez réessayer.\n");
        }
    } while (choix != 5);
}

void menuPrincipal() {
    int choix;
    Utilisateur utilisateurs[MAX_USERS];
    int nbUtilisateurs = 0;

    do {
        printf("\n--- Menu Principal ---\n");
        printf("1. Mode Festivalier\n");
        printf("2. Mode Manager\n");
        printf("3. Quitter\n");
        printf("Entrez votre choix: ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                modeFestivalier(concert, nbConcerts, utilisateurs, &nbUtilisateurs);
                break;
            case 2:
                modeManager();
                break;
            case 3:
                printf("Au revoir !\n");
                libererMemoire();
                break;
            default:
                printf("Choix invalide, veuillez réessayer.\n");
        }
    } while (choix != 3);
}

int main() {
    menuPrincipal();
    return 0;
}
