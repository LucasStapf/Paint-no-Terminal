#include <stdio.h>
#include <math.h>
#include "pgm.h"
#include "draw.h"
#include "constants.h"

/* Funcao auxiliar */
int menorNumero(int a, int b, int c){

    if(a <= b && a <= c){
        return a;    
    } else {
        
        if(b <= c){
            return b;        
        } else {
            return c;
        }
    }
}

/* Funcoes para os desenhos */

/* Usei a equacao da reta (ax + by + c = 0) para achar o melhor ponto a ser pintado. Quanto mais próximo do zero 
for o resultado da conta axi + byi + c, mais o ponto (xi, yi) se aproxima da real reta*/
int drawLine(pgm_t* pgm, int x_i, int y_i, int x_f, int y_f, int color){
    
    if(!pgm){
        return ERROR_PGM;    
    }
    
    int x = x_i;
    int x_add = 0;
    
    int y = y_i;
    int y_add = 0;
    
    int deltaX = x_f - x_i;
    int deltaY = y_f - y_i;
    
    int c = y*deltaX - x*deltaY;
    
    x_add = deltaX > 0 ? 1 : -1;
    y_add = deltaY > 0 ? 1 : -1;
    
    if(fabs(deltaX) > fabs(deltaY)){
        
        for(int i = 0; i <= fabs(deltaX); i++){
                
            int v1 = y*deltaX - x*deltaY - c;
            int v2 = (y + y_add)*deltaX - x*deltaY - c;
            
            if(fabs(v2) > fabs(v1)){
                pgm->pixels[y][x] = color;
            } else {
                pgm->pixels[y + y_add][x] = color;
                y += y_add;
            }
            
            x += x_add;
        }
        
    } else {
        
        for(int i = 0; i <= fabs(deltaY); i++){
                
            int v1 = y*deltaX - x*deltaY - c;
            int v2 = (y)*deltaX - (x + x_add)*deltaY - c;
            
            if(fabs(v2) > fabs(v1)){
                pgm->pixels[y][x] = color;
            } else {
                pgm->pixels[y][x + x_add] = color;
                x += x_add;
            }
            
            y += y_add;
        }
        
    }
    
    return SUCCESS_PGM;
}

/* Decidi descolar o retangulo quando os lados forem pares, mas nao sei qual seria a melhor abordagem */
int drawRect(pgm_t* pgm, int x, int y, int width, int height, int color){
    
    if(!pgm){
        return ERROR_PGM;    
    }
    
    //setPixelPGM(pgm, x, y, color);
    
    int x1, y1;
    int x2, y2;
    
    int c1, c2;
    
    if(width % 2 != 0){
        c1 = 0;    
    } else {
        c1 = 1;
    }
    
    if(height % 2 != 0){
        c2 = 0;    
    } else {
        c2 = 1;
    }
    
    x1 = x + c1 - width/2;
    x2 = x + width/2;
    
    y1 = y - c2 + height/2;
    y2 = y - height/2;
    
    
    for(int i = 0; i < width; i++){
        setPixelPGM(pgm, x1 + i, y1, color);
        setPixelPGM(pgm, x2 - i, y2, color);    
    }
    
    for(int i = 0; i < height; i++){
        setPixelPGM(pgm, x1, y1 - i, color);
        setPixelPGM(pgm, x2, y2 + i, color);    
    }
    
    return SUCCESS_PGM;
}

/* Usando o mesmo principio para o desenho da reta, aqui quanto mais a expressão (xi - x)^2 + (yi - y) - r^2 for
proxima de zero, mais o ponto (xi, yi) se encontra da real circunferencia */
int drawCircle(pgm_t* pgm, int x_i, int y_i, int r, int color){
    
    if(!pgm){
        return ERROR_PGM;    
    }
    
    //setPixelPGM(pgm, x_i, y_i, color);
    
    int x = x_i;
    int x_add = +1;
    
    int y = y_i + r;
    int y_add = -1;
    
    do {
    
        int v1 = (x + x_add - x_i)*(x + x_add - x_i) + (y - y_i)*(y - y_i) - r*r;
        int v2 = (x + x_add - x_i)*(x + x_add - x_i) + (y + y_add - y_i)*(y + y_add - y_i) - r*r;
        int v3 = (x - x_i)*(x - x_i) + (y + y_add - y_i)*(y + y_add - y_i) - r*r;
        
        v1 *= v1;
        v2 *= v2;
        v3 *= v3;
        
        int m = menorNumero(v1, v2, v3);
        
        if(v1 <= m){
            x = x + x_add;
            setPixelPGM(pgm, x, y, color);
        } else {
            if(v2 <= m){
                x = x + x_add;
                y = y + y_add;
                setPixelPGM(pgm, x, y, color);            
            } else {
                y = y + y_add;
                setPixelPGM(pgm, x, y, color);
            }
        }        
        
        if(y == y_i){
            x_add *= -1;        
        }
        
        if(x == x_i){
            y_add *= -1;        
        }
        
    } while ((x != x_i) || (y != y_i + r));
    
    return SUCCESS_PGM;
}

int drawDisk(pgm_t* pgm, int x, int y, int r, int color){
    
    if(!pgm){
        return ERROR_PGM;    
    }

    for(int i = x - r; i < x + r; i++){
		for(int j = y - r; j < y + r; j++){
			if(((x - i)*(x - i) + (y - j)*(y - j)) < r*r)
				setPixelPGM(pgm, i, j, color);
		}
	}
	
	drawCircle(pgm, x, y, r, color);
	
	return SUCCESS_PGM;
}
