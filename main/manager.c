#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SALLES 100
#define MAX_RANGES 50
#define MAX_CHAISE 100
#define MAX_CONCERTS 100

typedef struct {
    char nom[100];
    int nbRanges;
    int chaiseparRanges[MAX_RANGES];
    char categories[MAX_RANGES];
    float prix[MAX_RANGES];
    int reserve[MAX_RANGES][MAX_CHAISE];
} Salle; // Structure d'information d'une salle

typedef struct {
    char nom[100];
    char **artistes;
    float heuredebut;
    float heurefin;
    int nbArtistes;
} Concert;

Concert concert[MAX_CONCERTS];
int nbConcerts = 0;

Salle salles[MAX_SALLES];
int nbSalles = 0;

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
}

void loadFromFile() {
    FILE *file = fopen("salles.txt", "r");
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    fscanf(file, "%d\n", &nbSalles);
    for (int i = 0; i < nbSalles; i++) {
        fscanf(file, "%s\n", salles[i].nom);
        fscanf(file, "%d\n", &salles[i].nbRanges);
        for (int j = 0; j < salles[i].nbRanges; j++) {
            fscanf(file, "%d %c %f\n", &salles[i].chaiseparRanges[j], &salles[i].categories[j], &salles[i].prix[j]);
            for (int k = 0; k < salles[i].chaiseparRanges[j]; k++) {
                fscanf(file, "%d ", &salles[i].reserve[j][k]);
            }
            fscanf(file, "\n");
        }
    }

    fclose(file);
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
        concert[nbConcerts].artistes[i] = (char *)malloc(200 * sizeof(char));
        printf("Saisissez l'artiste nº %d qui va passer au concert: ", i + 1);
        scanf("%s", concert[nbConcerts].artistes[i]);
    }

    nbConcerts++;
    printf("Concert créé avec succès.\n");
    saveToFile();
}

void afficherConcerts() {
    for (int i = 0; i < nbConcerts; i++) {
        printf("Concert %s:\n", concert[i].nom);
        printf("Heure de début: %.2f\n", concert[i].heuredebut);
        printf("Heure de fin: %.2f\n", concert[i].heurefin);
        for (int j = 0; j < concert[i].nbArtistes; j++) {
            printf("  Artiste nº%d : %s\n", j + 1, concert[i].artistes[j]);
        }
    }
}

void modifierConcert() {
    int concertIndex;
    printf("Entrer l'index du concert à modifier: ");
    scanf("%d", &concertIndex);
    if (concertIndex < 0 || concertIndex >= nbConcerts) {
        printf("Index du concert invalide.\n");
        return;
    }

    printf("Modification du Concert %s.\n", concert[concertIndex].nom);
    printf("Entrer le nouveau nom du concert (actuel: %s): ", concert[concertIndex].nom);
    scanf("%s", concert[concertIndex].nom);
    printf("Entrer la nouvelle heure de début du concert (actuelle: %.2f): ", concert[concertIndex].heuredebut);
    scanf("%f", &concert[concertIndex].heuredebut);
    printf("Entrer la nouvelle heure de fin du concert (actuelle: %.2f): ", concert[concertIndex].heurefin);
    scanf("%f", &concert[concertIndex].heurefin);

    for (int i = 0; i < concert[concertIndex].nbArtistes; i++) {
        free(concert[concertIndex].artistes[i]);
    }
    free(concert[concertIndex].artistes);

    printf("Combien d'artistes vont au concert? ");
    scanf("%d", &concert[concertIndex].nbArtistes);

    concert[concertIndex].artistes = (char **)malloc(concert[concertIndex].nbArtistes * sizeof(char *));
    for (int i = 0; i < concert[concertIndex].nbArtistes; i++) {
        concert[concertIndex].artistes[i] = (char *)malloc(200 * sizeof(char));
        printf("Saisissez l'artiste nº %d qui va passer au concert: ", i + 1);
        scanf("%s", concert[concertIndex].artistes[i]);
    }

    printf("Concert %s modifié avec succès.\n", concert[concertIndex].nom);
    saveToFile();
}

void menuConcerts() {
    int choix;
    printf("Menu Concerts:\n");
    while (1) {
        printf("\nOptions disponibles:\n");
        printf("1. Créer un concert\n");
        printf("2. Afficher tous les concerts\n");
        printf("3. Modifier un concert\n");
        printf("0. Retour au menu principal\n");
        printf("Votre choix: ");
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
            case 0:
                return;
            default:
                printf("Choix invalide. Réessayez.\n");
        }
    }
}

void creerSalle() {
    if (nbSalles >= MAX_SALLES) {
        printf("Nombre maximal de salles atteint.\n");
        return;
    }

    printf("Entrer le nom de la salle: ");
    scanf("%s", salles[nbSalles].nom);

    printf("Entrer le nombre de rangées: ");
    scanf("%d", &salles[nbSalles].nbRanges);

    for (int i = 0; i < salles[nbSalles].nbRanges; i++) {
        printf("Entrer le nombre de sièges pour la rangée %d: ", i + 1);
        scanf("%d", &salles[nbSalles].chaiseparRanges[i]);
        printf("Entrer la catégorie pour la rangée %d (A, B, C): ", i + 1);
        scanf(" %c", &salles[nbSalles].categories[i]);
        printf("Entrer le prix pour la catégorie %c: ", salles[nbSalles].categories[i]);
        scanf("%f", &salles[nbSalles].prix[i]);
        memset(salles[nbSalles].reserve[i], 1, sizeof(int) * salles[nbSalles].chaiseparRanges[i]);
    }

    nbSalles++;
    printf("Salle créée avec succès.\n");
    saveToFile();
}

void afficherSalles() {
    for (int i = 0; i < nbSalles; i++) {
        printf("Salle %s:\n", salles[i].nom);
        for (int j = 0; j < salles[i].nbRanges; j++) {
            printf("  Rangée %d: %d sièges, Catégorie %c, Prix %.2f EUR\n",
                   j + 1, salles[i].chaiseparRanges[j], salles[i].categories[j], salles[i].prix[j]);
        }
    }
}

void modifierSalle() {
    int salleIndex;
    printf("Entrer l'index de la salle à modifier: ");
    scanf("%d", &salleIndex);
    if (salleIndex < 0 || salleIndex >= nbSalles) {
        printf("Index de salle invalide.\n");
        return;
    }

    printf("Modification de la salle %s.\n", salles[salleIndex].nom);
    printf("Entrer le nouveau nombre de rangées (actuel: %d): ", salles[salleIndex].nbRanges);
    scanf("%d", &salles[salleIndex].nbRanges);
    for (int i = 0; i < salles[salleIndex].nbRanges; i++) {
        printf("Rangée %d: entrer le nouveau nombre de sièges (actuel: %d): ", i + 1, salles[salleIndex].chaiseparRanges[i]);
        scanf("%d", &salles[salleIndex].chaiseparRanges[i]);
        printf("Entrer la nouvelle catégorie pour la rangée %d (A, B, C) (actuelle: %c): ", i + 1, salles[salleIndex].categories[i]);
        scanf(" %c", &salles[salleIndex].categories[i]);
        printf("Entrer le nouveau prix pour la catégorie %c (actuel: %.2f EUR): ", salles[salleIndex].categories[i], salles[salleIndex].prix[i]);
        scanf("%f", &salles[salleIndex].prix[i]);
    }

    printf("Salle %s modifiée avec succès.\n", salles[salleIndex].nom);
    saveToFile();
}

void modeManager() {
    int choix;
    printf("Mode Manager:\n");
    while (1) {
        printf("\nOptions disponibles:\n");
        printf("1. Créer une salle\n");
        printf("2. Afficher toutes les salles\n");
        printf("3. Modifier une salle\n");
        printf("4. Menu concerts\n");
        printf("0. Retour au menu principal\n");
        printf("Votre choix: ");
        scanf("%d", &choix);

        switch (choix) {
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
                menuConcerts();
                break;
            case 0:
                return;
            default:
                printf("Choix invalide. Réessayez.\n");
        }
    }
}

int main() {
    int choix;

    loadFromFile();

    while (1) {
        printf("\nMenu Principal:\n");
        printf("1. Mode Manager\n");
        printf("0. Quitter\n");
        printf("Votre choix: ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                modeManager();
                break;
            case 0:
                libererMemoire();
                printf("Au revoir!\n");
                return 0;
            default:
                printf("Choix invalide. Réessayez.\n");
        }
    }
}

