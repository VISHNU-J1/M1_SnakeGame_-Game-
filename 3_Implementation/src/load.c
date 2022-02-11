#include <stdio.h>

#include "snake_game.h"


int load(void)
{
    int row,col,r,c,q;
    
    gotoxy(49,10);
    printf("Don't maximize the window");
    gotoxy(56,14);
    printf("Loading...");
    gotoxy(50,15);
    for(r=1; r<=20; r++)
    {
        for(q=0; q<=100000000; q++); 
        printf("%c",177);
    }
    gotoxy(48,16);
    printf("Press Enter key to continue..");
    
    getch();
    // waitForAnyKey();
    
    // gotoxy(60,50); 
    
    system("cls||clear");
   
	
    
    // if(getch()==27)
    //     exit(0);
}