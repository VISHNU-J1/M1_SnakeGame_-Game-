#include "snake_game.h"
void Print()
{
    // gotoxy(5,2);

    printf("\tWelcome To The Snake Game.\n\n (Press Any Key To Continue...)\n");
    // getch();
    // system("cls");
    printf("\t\nGame Instructions:\n");
    printf("\t\n -> Dont Maximize the window\n");
    printf("\t\n -> Use Arrow Keys To Move The Snake.\n\n-> You Will Be Provided Foods at The random Coordinates Of The Screen Which You Have To Eat, To Make Score.\n");
	printf("\tEverytime You Eat A Food The Length Of The Snake Will Be Increased By 1 Element indicating the score.");
	printf("\t\n\n -> You Can Pause The Game While Playing By Pressing Any Key, To Continue The Paused Game Press Any Key Once Again.");
	printf("\t\n\n -> If You Want To Exit Press ESC.\n");
    printf("\t\n\n\nPress Any Key To continue...");
 
    gotoxy(49,10);
    printf("");
    gotoxy(56,14);
    printf("");
    gotoxy(48,16);
    printf("");

       getch();
    system("cls");
    printf("\n \t Press Any Key to PlayGame");
    // if(getch()==27)
    //     exit(0);
}