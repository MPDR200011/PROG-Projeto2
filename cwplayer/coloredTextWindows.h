#ifndef PROG_PROJETO_2_COLOREDTEXTWINDOWS_H
#define PROG_PROJETO_2_COLOREDTEXTWINDOWS_H

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <windows.h>

#define BLACK 0
#define BLUE 1
#define GREEN 2
#define CYAN 3
#define RED 4
#define MAGENTA 5
#define BROWN 6
#define LIGHTGRAY 7
#define DARKGRAY 8
#define LIGHTBLUE 9
#define LIGHTGREEN 10
#define LIGHTCYAN 11
#define LIGHTRED 12
#define LIGHTMAGENTA 13
#define YELLOW 14
#define WHITE 15

#define BLACK_B 0
#define RED_B 4
#define GREEN_B 2
#define YELLOW_B 14
#define BLUE_B 1
#define MAGENTA_B 5
#define CYAN_B 3
#define WHITE_B 15

void clrscr(void);
void gotoxy(int x, int y);
void setcolor(unsigned int color);
void setcolor(unsigned int color, unsigned int background_color);

#endif //PROG_PROJETO_2_COLOREDTEXTWINDOWS_H
