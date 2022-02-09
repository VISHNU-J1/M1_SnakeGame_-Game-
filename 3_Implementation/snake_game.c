#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>

// #include "snake_game.h"
// #include "load.c"
// #include "functiond.c"
void gotoxy(int x, int y)
{
    COORD p;
    p.X = x;
    p.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}
void load();
int main(){
    load();
    gotoxy(1,1);
    Print();

    return 0;

}