#ifndef PGM_H_INCLUDED
#define PGM_H_INCLUDED

typedef struct PGM {
    
    char magic_number[3];
    char name[50];
    int width;
    int height;
    int tones;
    int **pixels;
    
} pgm_t;

int createPGM(pgm_t* pgm, int widht, int height);
int freePGM(pgm_t* pgm);

int exportPGM(pgm_t* pgm);
int setPixelPGM(pgm_t* pgm, int x, int y, int color);




#endif // PGM_H_INCLUDED
