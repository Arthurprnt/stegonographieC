#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "image.h"

void main(int argc, char* argv[]) {

    if (argc < 3 || argc > 3) {
        printf("Il n'y a pas le bon nombre d'arguments, voici comment utiliser l'outil:\n./revele image secret\n");
    } else {
        Image* img = importerImage(argv[1]);
        exporterImage(reveler(img), argv[2]);
        printf("Image révélée avec succès !");
    }

}