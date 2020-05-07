#include <stdio.h>
#include <stdlib.h>
#include "pgm.h"
#include "constants.h"

int createPGM(pgm_t* pgm, int width, int height){
    
    if(!pgm){
        return ERROR_PGM;    
    }

    pgm->width = width;
    pgm->height = height;
    
    pgm->magic_number[0] = 'P';
    pgm->magic_number[1] = '2';
    pgm->magic_number[2] = '\0';
    
    pgm->tones = 255;
    
    pgm->pixels = (int**)calloc(height, sizeof(int*));
    for(int i = 0; i < height; i++){
        pgm->pixels[i] = (int*)calloc(width, sizeof(int));
    }
    
    return SUCCESS_PGM;
}

int freePGM(pgm_t* pgm){
    
    if(!pgm){
        return ERROR_PGM;    
    }
    
    for(int i = 0; i < pgm->height; i++){
        free(pgm->pixels[i]);
    }
    
    free(pgm->pixels);
    
    return SUCCESS_PGM;
}

int exportPGM(pgm_t* pgm){

    if(!pgm){
        return ERROR_PGM;
    }
    
    FILE *f;
    f = fopen(pgm->name, "w");
    
    if(f != NULL){
        
        fprintf(f, "%s\n", pgm->magic_number);
        fprintf(f, "%d %d\n", pgm->width, pgm->height);
        fprintf(f, "%d\n", pgm->tones);
        
        for(int i = 0; i < pgm->height; i++){
            
            for(int j = 0; j < pgm->width; j++){
                fprintf(f, "%d ", pgm->pixels[i][j]);            
            }
            
            fprintf(f, "\n");
        }
          
    } else {
        printf("\n*** Erro ao exportar o arquivo ***\n");
        return ERROR_PGM;  
    }
    
    fclose(f);
    return SUCCESS_PGM;
}

int setPixelPGM(pgm_t* pgm, int x, int y, int color){

    if(!pgm){
        return ERROR_PGM;    
    }
    
    if((x >= 0 && x < pgm->width) && (y >= 0 && y < pgm->height)){
        pgm->pixels[y][x] = color;
    }
    
    return SUCCESS_PGM;
}
