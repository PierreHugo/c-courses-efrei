#include "matrice_generique.h"

// Fonction pour obtenir la taille en octets d'un type de coefficient
size_t coeff_matrice_gen_size(coeff_type type) {
    switch (type) {
        case TYPE_UINT8: return sizeof(uint8_t);
        case TYPE_INT8: return sizeof(int8_t);
        case TYPE_INT: return sizeof(int);
        case TYPE_FLOAT: return sizeof(float);
        default: return 0;
    }
}

// Fonction d'allocation d'une matrice générique
matrice_gen_t* allouer_matrice_gen(size_t n, size_t m, coeff_type type) {
    matrice_gen_t *mat = (matrice_gen_t*)malloc(sizeof(matrice_gen_t));
    if (!mat) return NULL;

    mat->lignes = n;
    mat->colonnes = m;
    mat->type = type;
    
    size_t coeff_size = coeff_matrice_gen_size(type);
    mat->coeffs = (void**)malloc(n * sizeof(void*));

    if (!mat->coeffs) {
        free(mat);
        return NULL;
    }

    for (size_t i = 0; i < n; i++) {
        mat->coeffs[i] = malloc(m * coeff_size);
        if (!mat->coeffs[i]) {
            for (size_t j = 0; j < i; j++) free(mat->coeffs[j]);
            free(mat->coeffs);
            free(mat);
            return NULL;
        }
    }
    
    return mat;
}

// Fonction de saisie des coefficients d'une matrice
void saisir_coeffs_matrice_gen(matrice_gen_t *mat) {
    if (!mat) return;

    printf("Saisie des coefficients (%zu x %zu):\n", mat->lignes, mat->colonnes);
    
    for (size_t i = 0; i < mat->lignes; i++) {
        for (size_t j = 0; j < mat->colonnes; j++) {
            printf("Élément [%zu][%zu] : ", i, j);
            switch (mat->type) {
                case TYPE_UINT8:
                    scanf("%hhu", (uint8_t*)&(((uint8_t*)mat->coeffs[i])[j]));
                    break;
                case TYPE_INT8:
                    scanf("%hhd", (int8_t*)&(((int8_t*)mat->coeffs[i])[j]));
                    break;
                case TYPE_INT:
                    scanf("%d", (int*)&(((int*)mat->coeffs[i])[j]));
                    break;
                case TYPE_FLOAT:
                    scanf("%f", (float*)&(((float*)mat->coeffs[i])[j]));
                    break;
            }
        }
    }
}

// Fonction d'affichage d'une matrice
void affiche_matrice_gen(matrice_gen_t *mat) {
    if (!mat) return;

    printf("Matrice (%zu x %zu) :\n", mat->lignes, mat->colonnes);
    
    for (size_t i = 0; i < mat->lignes; i++) {
        for (size_t j = 0; j < mat->colonnes; j++) {
            switch (mat->type) {
                case TYPE_UINT8:
                    printf("%3hhu ", ((uint8_t*)mat->coeffs[i])[j]);
                    break;
                case TYPE_INT8:
                    printf("%3hhd ", ((int8_t*)mat->coeffs[i])[j]);
                    break;
                case TYPE_INT:
                    printf("%3d ", ((int*)mat->coeffs[i])[j]);
                    break;
                case TYPE_FLOAT:
                    printf("%6.2f ", ((float*)mat->coeffs[i])[j]);
                    break;
            }
        }
        printf("\n");
    }
}

// Fonction pour multiplier deux matrices génériques
matrice_gen_t* produit_matrices_gen(matrice_gen_t *mat1, matrice_gen_t *mat2) {
    if (!mat1 || !mat2 || mat1->colonnes != mat2->lignes || mat1->type != mat2->type)
        return NULL;

    matrice_gen_t *resultat = allouer_matrice_gen(mat1->lignes, mat2->colonnes, mat1->type);
    if (!resultat) return NULL;

    size_t coeff_size = coeff_matrice_gen_size(mat1->type);

    for (size_t i = 0; i < mat1->lignes; i++) {
        for (size_t j = 0; j < mat2->colonnes; j++) {
            switch (mat1->type) {
                case TYPE_UINT8:
                    ((uint8_t*)resultat->coeffs[i])[j] = 0;
                    for (size_t k = 0; k < mat1->colonnes; k++) {
                        ((uint8_t*)resultat->coeffs[i])[j] += 
                            ((uint8_t*)mat1->coeffs[i])[k] * ((uint8_t*)mat2->coeffs[k])[j];
                    }
                    break;
                case TYPE_INT8:
                    ((int8_t*)resultat->coeffs[i])[j] = 0;
                    for (size_t k = 0; k < mat1->colonnes; k++) {
                        ((int8_t*)resultat->coeffs[i])[j] += 
                            ((int8_t*)mat1->coeffs[i])[k] * ((int8_t*)mat2->coeffs[k])[j];
                    }
                    break;
                case TYPE_INT:
                    ((int*)resultat->coeffs[i])[j] = 0;
                    for (size_t k = 0; k < mat1->colonnes; k++) {
                        ((int*)resultat->coeffs[i])[j] += 
                            ((int*)mat1->coeffs[i])[k] * ((int*)mat2->coeffs[k])[j];
                    }
                    break;
                case TYPE_FLOAT:
                    ((float*)resultat->coeffs[i])[j] = 0.0f;
                    for (size_t k = 0; k < mat1->colonnes; k++) {
                        ((float*)resultat->coeffs[i])[j] += 
                            ((float*)mat1->coeffs[i])[k] * ((float*)mat2->coeffs[k])[j];
                    }
                    break;
            }
        }
    }
    return resultat;
}

// Fonction de désallocation d'une matrice générique
void desallouer_matrice_gen(matrice_gen_t *mat) {
    if (!mat) return;

    for (size_t i = 0; i < mat->lignes; i++) {
        free(mat->coeffs[i]);
    }
    free(mat->coeffs);
    free(mat);
}
