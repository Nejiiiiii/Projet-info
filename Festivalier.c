#include <stdio.h>
#inlcude <stdlib.h>
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define ANSI_COLOR_WHITE "\x1b[37m"
typedef struct {
    int estReserve;      // 0 = non réservé, 1 = réservé
    double prix;         // Prix du siège
    int categorie;       // Catégorie du siège (A, B, C)
    int idUtilisateur;   // Identifiant de l'utilisateur qui a réservé le siège
} Siege;
typedef struct {
    int estReserve;
    double prix;
    int categorie;
} Siege;

typedef struct {
    char nom[100];
    int nbRanges;
    int siegesParRange;
    Siege **sieges;  
} Salle;

typedef struct {
    char nomConcert[100];
    Salle *salle;
    char heureDebut[6]; //par exemple le concert commence a 6h
    char heureFin[6];
    int aFosse;
} Concert;
void reserverSiege();
void voirConcertsDisponibles();
void voirMesReservations();

void menuFestivalier() {
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
                reserverSiege();
                break;
            case 2:
                voirConcertsDisponibles();
                break;
            case 3:
                voirMesReservations();
                break;
            case 4:
                printf("Retour au menu principal...\n");
                break;
            default:
                printf("Choix invalide, veuillez réessayer.\n");
        }
    } while (choix != 4);
}
void afficherSiegesDisponibles(Salle salle);

void reserverSiege(Concert concerts[], int nbConcerts) {
    int choixConcert, rangee, siegeNum;
    printf("Liste des concerts disponibles:\n");
    for (int i = 0; i < nbConcerts; i++) {
        printf("%d. %s\n", i + 1, concerts[i].nomConcert);
    }
    printf("Choisissez un concert pour réserver un siège (1-%d): ", nbConcerts);
    scanf("%d", &choixConcert);

    if (choixConcert < 1 || choixConcert > nbConcerts) {
        printf("Choix invalide.\n");
        return;
    }

    afficherSiegesDisponibles(*concerts[choixConcert - 1].salle);

    printf("Entrez la rangée et le numéro du siège à réserver: ");
    scanf("%d %d", &rangee, &siegeNum);

   
    Siege *siege = &concerts[choixConcert - 1].salle->sieges[rangee - 1][siegeNum - 1];
    if (!siege->estReserve) {
        siege->estReserve = 1;
        printf("Siège R%dS%d réservé avec succès pour %s.\n", rangee, siegeNum, concerts[choixConcert - 1].nomConcert);
    } else {
        printf("Ce siège est déjà réservé.\n");
    }
}

void afficherSiegesDisponibles(Salle salle) {
    printf("Sièges disponibles pour %s:\n", salle.nom);
    for (int i = 0; i < salle.nbRanges; i++) {
        for (int j = 0; j < salle.siegesParRange; j++) {
            printf("%c", salle.sieges[i][j].estReserve ? 'X' : 'O');
        }
        printf("\n");
    }
}
void voirConcertsDisponibles(Concert concerts[], int nbConcerts) {
    printf("Concerts disponibles avec sièges libres:\n");
    for (int i = 0; i < nbConcerts; i++) {
        int nbSiegesDisponibles = 0;
        for (int j = 0; j < concerts[i].salle->nbRanges; j++) {
            for (int k = 0; k < concerts[i].salle->siegesParRange; k++) {
                if (!concerts[i].salle->sieges[j][k].estReserve) {
                    nbSiegesDisponibles++;
                }
            }
        }

        if (nbSiegesDisponibles > 0) {
            printf("%d. %s - %s to %s\n", i + 1, concerts[i].nomConcert, concerts[i].heureDebut, concerts[i].heureFin);
            printf("   Sièges disponibles: %d\n", nbSiegesDisponibles);
        }
    }
}
void VoirMesReservations(Utilisateur ) {
    printf("\n🎺 Vos Réservations 🎺\n\n");
    for (int i = 0; i < user.nombreReservations; i++) {
        Reservation res = user.reservations[i];
        printf("Concert: %s - Date: %s\n", res.nomConcert, res.date);
        printf("Siège: R%dS%d - Catégorie ", res.rangee, res.siege);
        switch (res.categorie) {
            case 'A':
                printf(ANSI_COLOR_GREEN "A (%d euros)" ANSI_COLOR_RESET);
                break;
            case 'B':
                printf(ANSI_COLOR_YELLOW "B (%d euros)" ANSI_COLOR_RESET);
                break;
            case 'C':
                printf("ANSI_COLOR_WHITE "C (%d euros)" ANSI_COLOR_RESET);
                break;
            default:
                printf("Reservé");
               printRedX();
              printf("\n");
        }
        printf("\n\n");
    }
}
int main() {
    menuFestivalier();
    return 0;}


2ème exemple



#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define ANSI_COLOR_WHITE   "\x1b[37m"

#define MAX_USERS 10
#define MAX_RESERVATIONS 10

typedef struct {
    int estReserve;      // 0 = non réservé, 1 = réservé
    double prix;         // Prix du siège
    char categorie;      // Catégorie du siège (A, B, C)
    int idUtilisateur;   // Identifiant de l'utilisateur qui a réservé le siège
} Siege;

typedef struct {
    char nom[100];
    int nbRanges;    
    int siegesParRange;
    Siege **sieges;  
} Salle;

typedef struct {
    char nomConcert[100];
    Salle *salle;
    char heureDebut[6]; // par exemple le concert commence à 6h
    char heureFin[6];
    int aFosse;
} Concert;

typedef struct {
    char nomConcert[100];
    char date[11]; // Date format YYYY-MM-DD
    int rangee;
    int siege;
    char categorie;
    double prix;
} Reservation;

typedef struct {
    int id;
    char nom[100];
    int nombreReservations;
    Reservation reservations[MAX_RESERVATIONS];
} Utilisateur;

void reserverSiege(Concert concerts[], int nbConcerts, Utilisateur *utilisateur);
void voirConcertsDisponibles(Concert concerts[], int nbConcerts);
void voirMesReservations(Utilisateur utilisateur);
void afficherSiegesDisponibles(Salle salle);
Utilisateur* trouverOuCreerUtilisateur(Utilisateur utilisateurs[], int *nbUtilisateurs, const char *nom);

void menuFestivalier(Concert concerts[], int nbConcerts, Utilisateur utilisateurs[], int *nbUtilisateurs) {
    char nomUtilisateur[100];
    printf("Entrez votre nom: ");
    scanf("%s", nomUtilisateur);

    Utilisateur *utilisateur = trouverOuCreerUtilisateur(utilisateurs, nbUtilisateurs, nomUtilisateur);

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
    if (utilisateur == NULL) {
        return;
    }

    int choixConcert, rangee, siegeNum, nombreDeSieges;
    printf("Liste des concerts disponibles:\n");
    for (int i = 0; i < nbConcerts; i++) {
        printf("%d. %s\n", i + 1, concerts[i].nomConcert);
    }
    printf("Choisissez un concert pour réserver un siège (1-%d): ", nbConcerts);
    scanf("%d", &choixConcert);

    if (choixConcert < 1 || choixConcert > nbConcerts) {
        printf("Choix invalide.\n");
        return;
    }

    afficherSiegesDisponibles(*concerts[choixConcert - 1].salle);

    printf("Combien de sièges souhaitez-vous réserver? ");
    scanf("%d", &nombreDeSieges);

    for (int i = 0; i < nombreDeSieges; i++) {
        printf("Entrez la rangée et le numéro du siège à réserver (format: rangée numéro): ");
        scanf("%d %d", &rangee, &siegeNum);

        Siege *siege = &concerts[choixConcert - 1].salle->sieges[rangee - 1][siegeNum - 1];
        if (!siege->estReserve) {
            siege->estReserve = 1;
            siege->idUtilisateur = utilisateur->id;

            Reservation reservation;
            strcpy(reservation.nomConcert, concerts[choixConcert - 1].nomConcert);
            strcpy(reservation.date, "2024-05-21"); // Example date, should be set appropriately
            reservation.rangee = rangee;
            reservation.siege = siegeNum;
            reservation.categorie = siege->categorie;
            reservation.prix = siege->prix;

            utilisateur->reservations[utilisateur->nombreReservations++] = reservation;

            printf("Siège R%dS%d réservé avec succès pour %s.\n", rangee, siegeNum, concerts[choixConcert - 1].nomConcert);
        } else {
            printf("Ce siège est déjà réservé.\n");
        }
    }
}

void afficherSiegesDisponibles(Salle salle) {
    printf("Sièges disponibles pour %s:\n", salle.nom);
    for (int i = 0; i < salle.nbRanges; i++) {
        for (int j = 0; j < salle.siegesParRange; j++) {
            printf("%c", salle.sieges[i][j].estReserve ? 'X' : 'O');
        }
        printf("\n");
    }
}

void voirConcertsDisponibles(Concert concerts[], int nbConcerts) {
    printf("Concerts disponibles avec sièges libres:\n");
    for (int i = 0; i < nbConcerts; i++) {
        int nbSiegesDisponibles = 0;
        for (int j = 0; j < concerts[i].salle->nbRanges; j++) {
            for (int k = 0; k < concerts[i].salle->siegesParRange; k++) {
                if (!concerts[i].salle->sieges[j][k].estReserve) {
                    nbSiegesDisponibles++;
                }
            }
        }

        if (nbSiegesDisponibles > 0) {
            printf("%d. %s - %s to %s\n", i + 1, concerts[i].nomConcert, concerts[i].heureDebut, concerts[i].heureFin);
            printf("   Sièges disponibles: %d\n", nbSiegesDisponibles);
        }
    }
}

void voirMesReservations(Utilisateur utilisateur) {
    printf("\n🎺 Vos Réservations 🎺\n\n");
    for (int i = 0; i < utilisateur.nombreReservations; i++) {
        Reservation res = utilisateur.reservations[i];
        printf("Concert: %s - Date: %s\n", res.nomConcert, res.date);
        printf("Siège: R%dS%d - Catégorie ", res.rangee, res.siege);
        switch (res.categorie) {
            case 'A':
                printf(ANSI_COLOR_GREEN "A (%.2f euros)" ANSI_COLOR_RESET, res.prix);
                break;
            case 'B':
                printf(ANSI_COLOR_YELLOW "B (%.2f euros)" ANSI_COLOR_RESET, res.prix);
                break;
            case 'C':
                printf(ANSI_COLOR_WHITE "C (%.2f euros)" ANSI_COLOR_RESET, res.prix);
                break;
            default:
                printf("Inconnue");
        }
        printf("\n\n");
    }
}

int main() {
    // Exemple de création de concerts
    Salle salle1 = {"Salle 1", 5, 5, NULL};
    salle1.sieges = malloc(salle1.nbRanges * sizeof(Siege *));
    for (int i = 0; i < salle1.nbRanges; i++) {
        salle1.sieges[i] = malloc(salle1.siegesParRange * sizeof(Siege));
        for (int j = 0; j < salle1.siegesParRange; j++) {
            salle1.sieges[i][j].estReserve = 0;
            salle1.sieges[i][j].prix = 50.0; // Prix par défaut, à remplacer par le prix réel
            
            salle1.sieges[i][j].categorie = (j < 2) ? 'A' : ((j < 4) ? 'B' : 'C'); // Juste un exemple de répartition des catégories
            salle1.sieges[i][j].idUtilisateur = -1;
        }
    }

    Salle salle2 = {"Salle 2", 4, 6, NULL};
    salle2.sieges = malloc(salle2.nbRanges * sizeof(Siege *));
    for (int i = 0; i < salle2.nbRanges; i++) {
        salle2.sieges[i] = malloc(salle2.siegesParRange * sizeof(Siege));
        for (int j = 0; j < salle2.siegesParRange; j++) {
            salle2.sieges[i][j].estReserve = 0;
            salle2.sieges[i][j].prix = 40.0; // Prix par défaut, à remplacer par le prix réel
            salle2.sieges[i][j].categorie = (j < 2) ? 'A' : ((j < 4) ? 'B' : 'C'); // Juste un exemple de répartition des catégories
            salle2.sieges[i][j].idUtilisateur = -1;
        }
    }

    Concert concerts[] = {
        {"Concert 1", &salle1, "18:00", "20:00", 1},
        {"Concert 2", &salle2, "20:30", "22:30", 0}
    };
    int nbConcerts = sizeof(concerts) / sizeof(concerts[0]);

    Utilisateur utilisateurs[MAX_USERS];
    int nbUtilisateurs = 0;

    while (1) {
        menuFestivalier(concerts, nbConcerts, utilisateurs, &nbUtilisateurs);
    }

    // Libérer la mémoire allouée pour les sièges
    for (int i = 0; i < salle1.nbRanges; i++) {
        free(salle1.sieges[i]);
    }
    free(salle1.sieges);

    for (int i = 0; i < salle2.nbRanges; i++) {
        free(salle2.sieges[i]);
    }
    free(salle2.sieges);

    return 0;
}

