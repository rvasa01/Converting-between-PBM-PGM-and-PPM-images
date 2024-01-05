#include "pbm.h"
#include <stdio.h>
#include <stdlib.h>

PPMImage * new_ppmimage( unsigned int w, unsigned int h, unsigned int m )
{
    PPMImage* PPM = malloc(sizeof(PPMImage));
    PPM->height = h;
    PPM->width = w;
    PPM->max = m;
    //Is a double pointer that stores the addresses of the other pointers. (pixmap underneath)
    PPM->pixmap[0] = malloc(sizeof(unsigned int *)*h);//Allocates memory for the red array (columns)
    PPM->pixmap[1] = malloc(sizeof(unsigned int *)*h);//Allocates memory for the green array 
    PPM->pixmap[2] = malloc(sizeof(unsigned int *)*h);//Allocates memory for the blue array 
    for(int i = 0; i < h; i++){
        PPM->pixmap[0][i] = (int*) malloc(w*sizeof(unsigned int));//Allocates memory for the columns of R, G, B pixmaps. Pointers to data that will be stored in it. 
        PPM->pixmap[1][i] = (int*) malloc(w*sizeof(unsigned int));
        PPM->pixmap[2][i] = (int*) malloc(w*sizeof(unsigned int));
    }
    return PPM;
}

PBMImage * new_pbmimage( unsigned int w, unsigned int h )
{
    PBMImage* PBM = malloc(sizeof(PBMImage));
    PBM->height = h;
    PBM->width = w;
    PBM->pixmap = malloc(sizeof(unsigned int *)*h);
    for(int i = 0; i < h; i++){
        PBM->pixmap[i] = (int*) malloc(w*sizeof(int));
    }
    return PBM;

}
PGMImage * new_pgmimage( unsigned int w, unsigned int h, unsigned int m )
{
    PGMImage* PGM = malloc(sizeof(PGMImage));
    PGM->height = h;
    PGM->width = w;
    PGM->pixmap = malloc(sizeof(unsigned int *)*h);//Is a double pointer that stores the addresses of the other pointers. 
    for(int i = 0; i < h; i++){
        PGM->pixmap[i] = (int*) malloc(w*sizeof(int));
    }
    return PGM;
}

void del_ppmimage( PPMImage * p )
{
    for(int i = 0; i < p->height; i++){
        free(p->pixmap[0][i]);//Frees up all of the columns allocated
        free(p->pixmap[1][i]);
        free(p->pixmap[2][i]);
    }
    free(p->pixmap[0]);//Frees up all of the rows allocated
    free(p->pixmap[1]);
    free(p->pixmap[2]);
    free(p);

}

void del_pgmimage( PGMImage * p )
{
    for(int i = 0; i < p->height; i++){
        free(p->pixmap[i]);//Frees up all of the rows. 
    }
    free(p->pixmap);//Frees up the double pointer pixmap when called. 
    free(p);
}

void del_pbmimage( PBMImage * p )
{
    for(int i = 0; i < p->height; i++){
        free(p->pixmap[i]);
    }
    free(p->pixmap);
    free(p);    
}


