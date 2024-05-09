#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

struct s_image {
    int haut;
    int larg;
    uint8_t* pixels;
};

typedef struct s_image Image;

/**
 * Manipulation d'images
 **/

uint8_t getPix(Image* img, int i, int j){
    assert(img != NULL && i >= 0 && i < img->haut && j >=0 && j < img->larg);
    return img->pixels[i*img->larg+j];
}

void setPix(Image* img, int i, int j, uint8_t v){
    assert(img != NULL && i >= 0 && i < img->haut && j >=0 && j < img->larg);
    img->pixels[i*img->larg+j] = v;
}

Image* creerImage(int haut, int larg) {
    Image* image = malloc(sizeof(Image));
    image->haut = haut;
    image->larg = larg;
    uint8_t* tab = malloc(haut*larg*sizeof(uint8_t));
    image->pixels = tab;
    return image;
}

void detruireImage(Image* img) {
    free(img->pixels);
    free(img);
}

void printImage(Image* img){
    int n = img->haut;
    int p = img->larg;
    int ind = 0;
    printf("-------IMAGE-------\n");
    for (int i = 0; i < n; i+=1){
        for (int j = 0; j < p; j += 1){
            printf("%d ", img->pixels[ind]);
            ind += 1;
        }
        printf("\n");
    }
    printf("-------FIN-------\n");
}

/**
 * Image test
 **/
Image* imageTest(int n, int p){
    Image* image = creerImage(n, p);
    image->haut = n;
    image->larg = p;
    for (int i=0; i<n; i+=1) {
        for (int j=0; j<p; j+=1) {
            if (i==j) {
                setPix(image, i, j, 255);
            } else {
                setPix(image, i, j, 0);
            }
        }
    }
    return image;
}

/**
 *   Import / Export
 **/
// renvoie NULL en cas d'erreur
Image* importerImage(char* filename){
    FILE* f = fopen(filename, "r");
    if(f == NULL) return NULL;
    char txt[2048];
    char txt_largeur[2048];
    char txt_hauteur[2048];
    fscanf(f, "%s", txt);
    fscanf(f, "%s %s", txt_largeur, txt_hauteur);
    int largeur = atoi(txt_largeur);
    int hauteur = atoi(txt_hauteur);
    Image* image = creerImage(hauteur, largeur);
    int ind = 0;
    fscanf(f, "%s", txt);
    while (ind < largeur*hauteur) {
        fscanf(f, "%s", txt);
        setPix(image, ind/largeur, ind%largeur, atoi(txt));
        ind += 1;
    }
    fclose(f);
    return image;
}

// renvoie false en cas d'erreur
bool exporterImage(Image* img, char* filename){
    FILE* f = fopen(filename, "w");
    if (f == NULL) return false;
    fprintf(f, "P2\n%d %d\n", img->larg, img->haut);
    int maximum = 0;
    for (int i=0; i<img->haut; i+=1) {
        for (int j=0; j<img->larg; j+=1) {
            if (getPix(img, i, j) > maximum) maximum = getPix(img, i, j);
        }
    }
    fprintf(f, "%d\n", maximum);
    for (int i=0; i<img->haut; i+=1) {
        for (int j=0; j<img->larg; j+=1) {
            fprintf(f, "%d\n", getPix(img, i, j));
        }
    }
    fclose(f);
    return true;
}


/**
 * Traitement d'image 
 **/

void miroir(Image* img) {
    Image* newimg = creerImage(img->haut, img->larg);
    for (int i=0; i<img->haut; i+=1) {
        for (int j=0; j<img->larg; j+=1) {
            setPix(newimg, i, j, getPix(img, i, img->larg-1-j));
        }
    }
    img->pixels = newimg->pixels;
}

Image* redim(Image* img, int haut, int larg) {
    Image* newimg = creerImage(haut, larg);
    float ratio_verti = haut*1.0/img->haut*1.0;
    float ratio_horiz = larg*1.0/img->larg*1.0;
    printf("rh: %f, rv: %f\n", ratio_horiz, ratio_verti);
    for (int i=0; i<haut; i+=1) {
        for (int j=0; j<larg; j+=1) {

            int new_i = i/ratio_verti;
            int new_j = j/ratio_horiz;
            setPix(newimg, i, j, getPix(img, new_i, new_j));

        }
    }
    return newimg;
}

/**
 * Steganographie
 **/

Image* cacher(Image* support, Image* secret) {
    Image* r_sec = redim(secret, support->haut, support->larg);
    Image* newimg = creerImage(support->haut, support->larg);
    for (int i=0; i<support->haut; i+=1) {
        for (int j=0; j<support->larg; j+=1) {

            setPix(newimg, i, j, (getPix(support, i, j) & 0b11111100) | ((getPix(r_sec, i, j) >> 6) & 0b00000011));

        }
    }
    return newimg;
}

Image* reveler(Image* img) {
    Image* newimg = creerImage(img->haut, img->larg);
    for (int i=0; i<img->haut; i+=1) {
        for (int j=0; j<img->larg; j+=1) {

            setPix(newimg, i, j, (getPix(img, i, j) << 6) & 0b11000000);

        }
    }
    return newimg;
}