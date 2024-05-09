#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "image.c"

struct s_image;

typedef struct s_image Image;

uint8_t getPix(Image* img, int i, int j);

void setPix(Image* img, int i, int j, uint8_t v);

Image* creerImage(int haut, int larg);

void detruireImage(Image* img);

void printImage(Image* img);

Image* imageTest(int n, int p);

Image* importerImage(char* filename);

bool exporterImage(Image* img, char* filename);

void miroir(Image* img);

Image* redim(Image* img, int haut, int larg);

Image* cacher(Image* support, Image* secret);

Image* reveler(Image* img);