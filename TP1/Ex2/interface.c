#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interface.h"

// Fonction d'affichage du menu utilisateur
void afficher_menu() {
    printf("\n=== Menu ===\n");
    printf("1. Charger deux matrices (saisie ou fichier)\n");
    printf("2. Afficher les matrices chargées\n");
    printf("3. Effectuer le produit matriciel\n");
    printf("4. Afficher le résultat\n");
    printf("5. Sauvegarder le résultat dans un fichier\n");
    printf("6. Afficher l'aide\n");
    printf("7. Quitter\n");
    printf("Choix : ");
}

// Gestion du menu utilisateur
void menu_utilisateur() {
    matrice_t *mat1 = NULL, *mat2 = NULL, *resultat = NULL;
    char fichier1[50], fichier2[50], fichier_sortie[50];
    int choix;

    while (1) {
        afficher_menu();
        scanf("%d", &choix);
        getchar(); // Évite les erreurs de saisie

        switch (choix) {
            case 1:
                printf("Entrez '1' pour une saisie utilisateur, '2' pour charger depuis un fichier : ");
                int mode;
                scanf("%d", &mode);
                getchar();

                if (mode == 1) {
                    mat1 = allouer_matrice(2, 2); // Exemple de taille par défaut
                    saisir_coeffs_matrice(mat1);
                    mat2 = allouer_matrice(2, 2);
                    saisir_coeffs_matrice(mat2);
                } else {
                    printf("Nom du fichier 1 : ");
                    scanf("%s", fichier1);
                    printf("Nom du fichier 2 : ");
                    scanf("%s", fichier2);

                    mat1 = lire_matrice_fichier(fichier1);
                    mat2 = lire_matrice_fichier(fichier2);

                    if (!mat1 || !mat2) {
                        printf("Erreur lors du chargement des matrices.\n");
                        continue;
                    }
                }
                printf("Matrices chargées avec succès !\n");
                break;

            case 2:
                if (mat1 && mat2) {
                    printf("Matrice 1 :\n");
                    affiche_matrice(mat1);
                    printf("Matrice 2 :\n");
                    affiche_matrice(mat2);
                } else {
                    printf("Aucune matrice chargée.\n");
                }
                break;

            case 3:
                if (mat1 && mat2) {
                    resultat = produit_matrices(mat1, mat2);
                    if (resultat) {
                        printf("Produit matriciel effectué avec succès.\n");
                    } else {
                        printf("Erreur dans le produit matriciel.\n");
                    }
                } else {
                    printf("Veuillez charger deux matrices avant de multiplier.\n");
                }
                break;

            case 4:
                if (resultat) {
                    printf("Résultat du produit matriciel :\n");
                    affiche_matrice(resultat);
                } else {
                    printf("Aucun résultat disponible.\n");
                }
                break;

            case 5:
                if (resultat) {
                    printf("Nom du fichier de sortie : ");
                    scanf("%s", fichier_sortie);
                    ecrire_matrice_fichier(fichier_sortie, resultat);
                    printf("Résultat sauvegardé dans %s\n", fichier_sortie);
                } else {
                    printf("Aucun résultat à sauvegarder.\n");
                }
                break;

            case 6:
                printf("Utilisez les options de menu pour manipuler les matrices.\n");
                break;

            case 7:
                printf("Quitter le programme.\n");
                desallouer_matrices(mat1);
                desallouer_matrices(mat2);
                desallouer_matrices(resultat);
                return;

            default:
                printf("Choix invalide. Réessayez.\n");
        }
    }
}

// Gestion des arguments de ligne de commande
void gestion_arguments(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Utilisation: %s fichier1 fichier2 [-o fichier_sortie]\n", argv[0]);
        return;
    }

    char *fichier1 = argv[1];
    char *fichier2 = argv[2];
    char *fichier_sortie = "out.txt";

    if (argc == 5 && strcmp(argv[3], "-o") == 0) {
        fichier_sortie = argv[4];
    }

    matrice_t *mat1 = lire_matrice_fichier(fichier1);
    matrice_t *mat2 = lire_matrice_fichier(fichier2);

    if (!mat1 || !mat2) {
        printf("Erreur lors du chargement des fichiers.\n");
        return;
    }

    matrice_t *resultat = produit_matrices(mat1, mat2);

    if (resultat) {
        ecrire_matrice_fichier(fichier_sortie, resultat);
        printf("Résultat sauvegardé dans %s\n", fichier_sortie);
    } else {
        printf("Erreur dans le produit matriciel.\n");
    }

    desallouer_matrices(mat1);
    desallouer_matrices(mat2);
    desallouer_matrices(resultat);
}
