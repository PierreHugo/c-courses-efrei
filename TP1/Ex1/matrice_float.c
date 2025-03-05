/* matrice_float.c */
#include "matrice_float.h"

matrice_t* allouer_matrice(int n, int m) {
    matrice_t* mat = (matrice_t*)malloc(sizeof(matrice_t));
    if (!mat) return NULL;
    mat->rows = n;
    mat->cols = m;
    mat->data = (float*)malloc(n * m * sizeof(float));
    if (!mat->data) {
        free(mat);
        return NULL;
    }
    return mat;
}

void saisir_coeffs_matrice(matrice_t* mat) {
    if (!mat || !mat->data) return;
    for (int i = 0; i < mat->rows; i++) {
        for (int j = 0; j < mat->cols; j++) {
            printf("Entrez l'élément [%d][%d] : ", i, j);
            scanf("%f", &mat->data[i * mat->cols + j]);
        }
    }
}

void affiche_matrice(const matrice_t* mat) {
    if (!mat || !mat->data) return;
    printf("\nMatrice %dx%d :\n", mat->rows, mat->cols);
    printf("+%s+\n", "-------------------------");
    for (int i = 0; i < mat->rows; i++) {
        printf("|");
        for (int j = 0; j < mat->cols; j++) {
            printf(" %6.2f ", mat->data[i * mat->cols + j]);
        }
        printf("|\n");
    }
    printf("+%s+\n", "-------------------------");
}

matrice_t* produit_matrices(const matrice_t* mat1, const matrice_t* mat2) {
    if (!mat1 || !mat2 || mat1->cols != mat2->rows) return NULL;
    
    matrice_t* res = allouer_matrice(mat1->rows, mat2->cols);
    if (!res) return NULL;
    
    for (int i = 0; i < mat1->rows; i++) {
        for (int j = 0; j < mat2->cols; j++) {
            res->data[i * res->cols + j] = 0;
            for (int k = 0; k < mat1->cols; k++) {
                res->data[i * res->cols + j] += mat1->data[i * mat1->cols + k] * mat2->data[k * mat2->cols + j];
            }
        }
    }
    return res;
}

void desalouer_matrice(matrice_t* mat) {
    if (mat) {
        free(mat->data);
        free(mat);
    }
}
