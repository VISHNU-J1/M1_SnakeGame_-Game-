#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>

#include "snake_game.h"
#include "load.c"
#include "functiond.c"
void gotoxy(int x, int y)
{
    COORD p;
    p.X = x;
    p.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}

void boundary()
{
    printf("%c", 218);
    for (int i = 1; i < 119; i++)
    {
        printf("%c", 196);
    }
    printf("%c", 191);
    for (int i = 1; i < 29; i++)
    {
        gotoxy(119, i);
        printf("%c", 179);
        gotoxy(0, i);
        printf("%c", 179);
    }
    printf("\n%c", 192);
    for (int i = 1; i < 119; i++)
    {
        printf("%c", 196);
    }
    printf("%c", 217);
    gotoxy(0, 0);
}

void move(int *x, int *y, char *l, char c, int len)
{
    gotoxy(x[len - 1], y[len - 1]);
    printf(" ");
    for (int i = len; i > 0; i--)
    {
        x[i] = x[i - 1];
        y[i] = y[i - 1];
    }
    *l = c;
    if (len > 1)
    {
        gotoxy(x[1], y[1]);
        printf("o");
    }
}

int check(int px, int py, int *x, int *y, int len)
{
    for (int i = 0; i < len; i++)
    {
        if (px == x[i] && py == y[i])
        {
            return 1;
        }
    }
    return 0;
}

void over(int x, int y, int len)
{
    gotoxy(x, y);
    printf("%c", 254);
    gotoxy(1, 1);
    printf("Game Over!!!\n");
    printf("%cScore : %d   ", 179, len - 1);
    while (getch() != 13)
        ;
    exit(0);
}  

void load();


int main()
{

    load();
    boundary();
    gotoxy(1, 1);

    Print();
  



    getch();
    system("cls");
    boundary();

    srand(time(NULL));
    int *x, *y, px = ((rand() % 58) * 2) + 3, py = (rand() % 28) + 1, len = 1;
    char c, l;
    clock_t t;

    x = (int *)malloc(sizeof(int) * (len + 1));
    y = (int *)malloc(sizeof(int) * (len + 1));
    x[0] = 25;
    y[0] = 20;

    gotoxy(px, py);
    printf("%c", 15);

    gotoxy(x[0], y[0]);
    printf("o");

    while (1)
    {
        do
        {
            t = clock();
            while (clock() < t + 250 && !kbhit())
                ;
            if (clock() < t + 250)
            {
                c = getch();
                if (c == 75 && l == 77)
                    c = 77;
                else if (c == 77 && l == 75)
                    c = 75;
                else if (c == 80 && l == 72)
                    c = 72;
                else if (c == 72 && l == 80)
                    c = 80;
            }

            switch (c)
            {
            case 0:
                break;

            case 224:
                break;

            case 80:
                move(x, y, &l, c, len);
                gotoxy(x[0], ++y[0]);
                printf("%c", 31);

                if (y[0] == 29)
                    over(x[0], y[0], len);
                break;

            case 72:
                move(x, y, &l, c, len);
                gotoxy(x[0], --y[0]);
                printf("%c", 30);

                if (y[0] == 0)
                    over(x[0], y[0], len);
                break;

            case 75:
                move(x, y, &l, c, len);
                gotoxy(x[0] = x[0] - 2, y[0]);
                printf("%c", 17);

                if (x[0] == 1)
                    over(x[0], y[0], len);
                break;

            case 77:
                move(x, y, &l, c, len);
                gotoxy(x[0] = x[0] + 2, y[0]);
                printf("%c", 16);

                if (x[0] == 119)
                    over(x[0], y[0], len);
                break;

            default:
                break;
            }
            for (int i = 4; i < len; i++)
            {
                if (x[0] == x[i] && y[0] == y[i])
                    over(x[0], y[0], len);
            }
        } while (x[0] != px || y[0] != py);

        gotoxy(x[len], y[len]);
        printf("o");
        len++;

        x = (int *)realloc(x, sizeof(int) * (len + 1));
        y = (int *)realloc(y, sizeof(int) * (len + 1));

        do
        {
            py = (rand() % 28) + 1;
            px = ((rand() % 58) * 2) + 3;
        } while (check(px, py, x, y, len));

        gotoxy(px, py);
        printf("%c", 15);
    }
    return 0;
}