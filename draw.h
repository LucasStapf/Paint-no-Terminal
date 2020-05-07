#ifndef DRAW_H_INCLUDED
#define DRAW_H_INCLUDED

#include "pgm.h"

int drawLine(pgm_t* pgm, int x_i, int y_i, int x, int y, int color);
int drawRect(pgm_t* pgm, int x, int y, int width, int height, int color);
int drawCircle(pgm_t* pgm, int x_i, int y_i, int r, int color);
int drawDisk(pgm_t* pgm, int x, int y, int r, int color);

#endif // DRAW_H_INCLUDED
