/* mes_entrees_sorties.c */
#include "mes_entrees_sorties.h"
#include "matrice_float.h"

char* lire_fichier(const char* nom_fichier) {
    FILE* fichier = fopen(nom_fichier, "r");
    if (!fichier) return NULL;
    
    fseek(fichier, 0, SEEK_END);
    long taille = ftell(fichier);
    rewind(fichier);
    
    char* contenu = (char*)malloc((taille + 1) * sizeof(char));
    if (!contenu) {
        fclose(fichier);
        return NULL;
    }
    
    fread(contenu, sizeof(char), taille, fichier);
    contenu[taille] = '\0';
    fclose(fichier);
    return contenu;
}

int ecrire_fichier(const char* nom_fichier, const char* contenu) {
    FILE* fichier = fopen(nom_fichier, "w");
    if (!fichier) return -1;
    
    fprintf(fichier, "%s", contenu);
    fclose(fichier);
    return 0;
}

int copier_fichier(const char* fichier_source, const char* fichier_dest) {
    char* contenu = lire_fichier(fichier_source);
    if (!contenu) return -1;
    
    int resultat = ecrire_fichier(fichier_dest, contenu);
    free(contenu);
    return resultat;
}

matrice_t* lire_matrice_fichier(const char* nom_fichier) {
    char* contenu = lire_fichier(nom_fichier);
    if (!contenu) return NULL;
    
    int n, m;
    char* ptr = contenu;
    sscanf(ptr, "%d %d", &n, &m);
    while (*ptr && *ptr != '\n') ptr++;
    if (*ptr) ptr++;
    
    matrice_t* mat = allouer_matrice(n, m);
    if (!mat) {
        free(contenu);
        return NULL;
    }
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            sscanf(ptr, "%f", &mat->data[i * m + j]);
            while (*ptr && *ptr != ' ' && *ptr != '\n') ptr++;
            if (*ptr) ptr++;
        }
    }
    
    free(contenu);
    return mat;
}
