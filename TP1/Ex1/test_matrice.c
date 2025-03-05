/* test_matrice.c */
#include "matrice_float.h"
#include <stdio.h>

int main() {
    int n1, m1, n2, m2;
    
    printf("Entrez les dimensions de la première matrice (n m) : ");
    scanf("%d %d", &n1, &m1);
    matrice_t* mat1 = allouer_matrice(n1, m1);
    if (!mat1) {
        printf("Échec d'allocation de la première matrice.\n");
        return 1;
    }
    saisir_coeffs_matrice(mat1);
    
    printf("Entrez les dimensions de la deuxième matrice (n m) : ");
    scanf("%d %d", &n2, &m2);
    matrice_t* mat2 = allouer_matrice(n2, m2);
    if (!mat2) {
        printf("Échec d'allocation de la deuxième matrice.\n");
        desalouer_matrice(mat1);
        return 1;
    }
    saisir_coeffs_matrice(mat2);
    
    printf("------------------------------------------\n");
    printf("Première matrice :\n");
    affiche_matrice(mat1);
    printf("------------------------------------------\n");
    printf("Deuxième matrice :\n");
    affiche_matrice(mat2);
    printf("------------------------------------------\n");
    
    matrice_t* resultat = produit_matrices(mat1, mat2);
    if (resultat) {
        printf("Produit des matrices :\n");
        affiche_matrice(resultat);
        desalouer_matrice(resultat);
    } else {
        printf("Multiplication impossible (dimensions incompatibles).\n");
    }
    
    desalouer_matrice(mat1);
    desalouer_matrice(mat2);
    
    return 0;
}
