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

