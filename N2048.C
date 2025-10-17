#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAILLE 6

// initialisation du tableau dynamique
int **initTableau() {
    int **tableau = malloc(TAILLE * sizeof(int *));
    for (int i = 0; i < TAILLE; i++)
        tableau[i] = malloc(TAILLE * sizeof(int));

    for (int i = 0; i < TAILLE; i++)
        for (int j = 0; j < TAILLE; j++)
            tableau[i][j] = 0;

    return tableau;
}

// Libération mémoire
void libererTableau(int **tableau) {
    for (int i = 0; i < TAILLE; i++)
        free(tableau[i]);
    free(tableau);
}

//  Ajouter une case (2 ou 4)
void ajouterCase(int **tableau) {
    int x, y;
    do {
        x = rand() % TAILLE;
        y = rand() % TAILLE;
    } while (tableau[x][y] != 0);

    tableau[x][y] = (rand() % 10 == 0) ? 4 : 2;
}

// Afficher le tableau
void afficherTableau(int **tableau, int score) {
    system("cls"); // ou "clear" sous Linux/Mac
    printf("\n  JEU 2048 (%dx%d)  \n", TAILLE, TAILLE);

    for (int i = 0; i < TAILLE; i++) {
        for (int j = 0; j < TAILLE; j++)
            printf("+-----");
        printf("+\n");

        for (int j = 0; j < TAILLE; j++) {
            if (tableau[i][j] == 0)
                printf("|     ");
            else
                printf("|%4d ", tableau[i][j]);
        }
        printf("|\n");
    }

    // pour ligne du bas
    for (int j = 0; j < TAILLE; j++)
        printf("+-----");
    printf("+\n");

    printf("Score : %d\n", score);
    printf("Commandes : Z(haut), S(bas), Q(gauche), D(droite) ou X(quitter) :");
}

// pour Déplacer les cases (à gauche, à droite, en haut, en bas)

int deplacerGauche(int **tableau, int *score) {
    int bouge = 0;
    for (int i = 0; i < TAILLE; i++) {
        int pos = 0;
        for (int j = 1; j < TAILLE; j++) {
            if (tableau[i][j] != 0) {
                int val = tableau[i][j];
                tableau[i][j] = 0;

                if (tableau[i][pos] == 0) {
                    tableau[i][pos] = val;
                    bouge = 1;
                } else if (tableau[i][pos] == val) {
                    tableau[i][pos] *= 2;
                    *score += tableau[i][pos];
                    pos++;
                    bouge = 1;
                } else {
                    pos++;
                    if (pos != j) bouge = 1;
                    tableau[i][pos] = val;
                }
            }
        }
    }
    return bouge;
}

int deplacerDroite(int **tableau, int *score) {
    int bouge = 0;
    for (int i = 0; i < TAILLE; i++) {
        int pos = TAILLE - 1;
        for (int j = TAILLE - 2; j >= 0; j--) {
            if (tableau[i][j] != 0) {
                int val = tableau[i][j];
                tableau[i][j] = 0;

                if (tableau[i][pos] == 0) {
                    tableau[i][pos] = val;
                    bouge = 1;
                } else if (tableau[i][pos] == val) {
                    tableau[i][pos] *= 2;
                    *score += tableau[i][pos];
                    pos--;
                    bouge = 1;
                } else {
                    pos--;
                    if (pos != j) bouge = 1;
                    tableau[i][pos] = val;
                }
            }
        }
    }
    return bouge;
}

int deplacerHaut(int **tableau, int *score) {
    int bouge = 0;
    for (int j = 0; j < TAILLE; j++) {
        int pos = 0;
        for (int i = 1; i < TAILLE; i++) {
            if (tableau[i][j] != 0) {
                int val = tableau[i][j];
                tableau[i][j] = 0;

                if (tableau[pos][j] == 0) {
                    tableau[pos][j] = val;
                    bouge = 1;
                } else if (tableau[pos][j] == val) {
                    tableau[pos][j] *= 2;
                    *score += tableau[pos][j];
                    pos++;
                    bouge = 1;
                } else {
                    pos++;
                    if (pos != i) bouge = 1;
                    tableau[pos][j] = val;
                }
            }
        }
    }
    return bouge;
}

int deplacerBas(int **tableau, int *score) {
    int bouge = 0;
    for (int j = 0; j < TAILLE; j++) {
        int pos = TAILLE - 1;
        for (int i = TAILLE - 2; i >= 0; i--) {
            if (tableau[i][j] != 0) {
                int val = tableau[i][j];
                tableau[i][j] = 0;

                if (tableau[pos][j] == 0) {
                    tableau[pos][j] = val;
                    bouge = 1;
                } else if (tableau[pos][j] == val) {
                    tableau[pos][j] *= 2;
                    *score += tableau[pos][j];
                    pos--;
                    bouge = 1;
                } else {
                    pos--;
                    if (pos != i) bouge = 1;
                    tableau[pos][j] = val;
                }
            }
        }
    }
    return bouge;
}

int mouvementPossible(int **tableau) {
    // S'il reste une case vide
    for (int i = 0; i < TAILLE; i++) {
        for (int j = 0; j < TAILLE; j++) {
            if (tableau[i][j] == 0)
                return 1;
        }
    }

    // Sinon, on vérifie s'il existe 2 cases identiques côte à côte
    for (int i = 0; i < TAILLE; i++) {
        for (int j = 0; j < TAILLE; j++) {
            // on regarde à droite
            if (j < TAILLE - 1 && tableau[i][j] == tableau[i][j + 1])
                return 1;
            // on regarde en bas
            if (i < TAILLE - 1 && tableau[i][j] == tableau[i + 1][j])
                return 1;
        }
    }

    return 0;
}

int aGagne(int **tableau) {
    for (int i = 0; i < TAILLE; i++)
        for (int j = 0; j < TAILLE; j++)
            if (tableau[i][j] == 2048)
                return 1;
    return 0;
}

//  Programme principal (main)
int main() {
    srand(time(NULL));
    int **tableau = initTableau();
    int score = 0;
    char touche;

    ajouterCase(tableau);
    ajouterCase(tableau);

    while (1) {
        afficherTableau(tableau, score);
        scanf(" %c", &touche);

        int deplacement = 0;
        switch (touche) {
            case 'q': deplacement = deplacerGauche(tableau, &score); break;
            case 'd': deplacement = deplacerDroite(tableau, &score); break;
            case 'z': deplacement = deplacerHaut(tableau, &score); break;
            case 's': deplacement = deplacerBas(tableau, &score); break;
            case 'x':
                printf("\n loser t abandonne aussi facilement .\n");
                libererTableau(tableau);
                return 0;
            default:
                continue;
        }

        if (deplacement)
            ajouterCase(tableau);

        if (aGagne(tableau)) {
            afficherTableau(tableau, score);
            printf("\n Bravo ! Vous avez atteint 2048 ! \n");
            break;
        }

        if (!mouvementPossible(tableau)) {
            afficherTableau(tableau, score);
            printf("\n Degage t es nul(le) !!! %d\n", score);
            break;
        }
    }

    libererTableau(tableau);
    return 0;
}
