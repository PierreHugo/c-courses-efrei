/* mes_entrees_sorties.h */
#ifndef MES_ENTREES_SORTIES_H
#define MES_ENTREES_SORTIES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrice_float.h"

char* lire_fichier(const char* nom_fichier);
int ecrire_fichier(const char* nom_fichier, const char* contenu);
int copier_fichier(const char* fichier_source, const char* fichier_dest);
matrice_t* lire_matrice_fichier(const char* nom_fichier);

#endif /* MES_ENTREES_SORTIES_H */
