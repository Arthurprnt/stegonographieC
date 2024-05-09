#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "image.h"

void main(int argc, char* argv[]) {

    if (argc < 4 || argc > 4) {
        printf("Il n'y a pas le bon nombre d'arguments, voici comment utiliser l'outil:\n./cache support secret image\n");
    } else {
        Image* supp = importerImage(argv[1]);
        Image* secr = importerImage(argv[2]);
        Image* renvoie = cacher(supp, secr);
        exporterImage(renvoie, argv[3]);
        printf("Image exportée avec succés !\n");
    }

}