/**
 * @file functiond.c
 * @author vishnu j
 * @brief 
 * @version 0.1
 * @date 2022-02-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <stdio.h>

#include "snake_game.h"


int Print(void)
{
    // gotoxy(5,2);
    // system("cls||clear");

    printf("\tWelcome To The Snake Game.\n\n (Press Any Key To Continue...)\n");
   
    printf("\t\nGame Instructions:\n");
    printf("\t\n -> Dont Maximize the window\n");
    printf("\t\n -> Use Arrow Keys To Move The Snake.\n\n-> You Will Be Provided Foods at The random Coordinates Of The Screen Which You Have To Eat, To Make Score.\n");
	printf("\tEverytime You Eat A Food The Length Of The Snake Will Be Increased By 1 Element indicating the score.");
	printf("\t\n\n -> You Can Pause The Game While Playing By Pressing ESC Key, To Continue The Paused Game Press Arrow Key Once Again.");
	printf("\t\n\n -> You need to select speed of the snake by selecting number between *0-9*.\n");
    printf("\t\n\n\nPress Any Key To continue...");
 


       getch();
    // waitForAnyKey();
	// return;
    system("cls||clear");
    printf("\n \t Press Any Key to PlayGame");
    
}