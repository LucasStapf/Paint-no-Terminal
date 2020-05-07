#include <stdio.h>
#include <string.h>
#include "pgm.h"
#include "draw.h"
#include "constants.h"

int chooseCommand(pgm_t* pgm, int* controller);
void create_pgm(pgm_t* pgm);
void export_pgm(pgm_t* pgm);
void draw_line(pgm_t* pgm);
void draw_circle(pgm_t* pgm);
void draw_disk(pgm_t* pgm);
void draw_rect(pgm_t* pgm);

int main(){

    pgm_t pgm;
    int controller = 0;
    
    printf("Paint no Terminal\n\n");
    printf("Comandos disponiveis:\n");
    printf("-> CREATE <width> <heigth>\n");
    printf("-> EXPORT <name>\n");
    printf("-> LINE <x1> <y1> <x2> <y2> <color>\n");
    printf("-> CIRCLE <x> <y> <radius> <color>\n");
    printf("-> DISK <x> <y> <radius> <color>\n");
    printf("-> RECT <x> <y> <width> <heigth> <color>\n");
    printf("-> EXIT\n");
    
    
    while(!controller){
        chooseCommand(&pgm, &controller);   
    }
    
    freePGM(&pgm);
    
    return 0;
}

int chooseCommand(pgm_t* pgm, int* controller){
    
    char cmds[][20] = {"CREATE", "EXPORT", "LINE", "CIRCLE", "DISK", "RECT", "EXIT"}; // 7 comandos
    int n_cmd = -1;
    
    char cmd[20];
    scanf("%s", cmd);
    
    for(int i = 0; i < 7; i++){
        if(!stricmp(cmd, cmds[i])){
            n_cmd = i;
            break;        
        }
    }
    
    switch(n_cmd){
    
        case 0: // CREATE
            create_pgm(pgm);
            break;
                
        case 1: // EXPORT
            export_pgm(pgm);
            break;
    
        case 2: // LINE
            draw_line(pgm);
            break;
            
        case 3: // CIRCLE
            draw_circle(pgm);
            break;
            
        case 4: // DISK
            draw_disk(pgm);
            break;
        
        case 5: // RECT
            draw_rect(pgm);
            break;
            
        case 6: // EXIT
            *controller = 1;
            break;
        
        default:
            printf("COMANDO INVALIDO");
            return ERROR_PGM;
            break;       
    }
    
    return SUCCESS_PGM;
}

void create_pgm(pgm_t* pgm){
    
    int width, height;
    scanf("%d %d", &width, &height);
    
    createPGM(pgm, width, height);
}

void export_pgm(pgm_t* pgm){
    
    scanf("%s", pgm->name);
    exportPGM(pgm);
}

void draw_line(pgm_t* pgm){

    int x_i, y_i;
    int x_f, y_f;
    int color;
    
    scanf("%d %d %d %d %d", &x_i, &y_i, &x_f, &y_f, &color);
    drawLine(pgm, x_i, y_i, x_f, y_f, color);
}

void draw_circle(pgm_t* pgm){

    int x, y;
    int r;
    int color;
    
    scanf("%d %d %d %d", &x, &y, &r, &color);
    drawCircle(pgm, x, y, r, color);
}

void draw_disk(pgm_t* pgm){

    int x, y;
    int r;
    int color;
    
    scanf("%d %d %d %d", &x, &y, &r, &color);
    drawDisk(pgm, x, y, r, color);
}

void draw_rect(pgm_t* pgm){

    int x, y;
    int width, height;
    int color;
    
    scanf("%d %d %d %d %d", &x, &y, &width, &height, &color);
    drawRect(pgm, x, y, width, height, color);
}