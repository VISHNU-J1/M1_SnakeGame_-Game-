#include <stdio.h>
#include "snake_game.h"
int mainMenu(void)
{
	int x = 10, y = 5;
	int yStart = y;
	
	int selected;
	
	system("cls||clear"); 
	
	gotoxy(x,y++);
	printf("New Game\n");
	gotoxy(x,y++);
	printf("High Scores\n");
	gotoxy(x,y++);
	printf("Exit\n");
	gotoxy(x,y++);


	selected = menuSelector(x, y, yStart);

	return(selected);
}
