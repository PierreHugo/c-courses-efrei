/* matrice_float.h */
#ifndef MATRICE_FLOAT_H
#define MATRICE_FLOAT_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int rows;
    int cols;
    float* data;
} matrice_t;

matrice_t* allouer_matrice(int n, int m);
void saisir_coeffs_matrice(matrice_t* mat);
void affiche_matrice(const matrice_t* mat);
matrice_t* produit_matrices(const matrice_t* mat1, const matrice_t* mat2);
void desalouer_matrice(matrice_t* mat);

#endif /* MATRICE_FLOAT_H */
