
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "load.c"
#include "functiond.c"
#include "menu.c"
#include "snake_game.h"


#define SNAKE_ARRAY_SIZE 310

#ifdef _WIN32
	
	#include <conio.h>
    #include <windows.h>

	
	#define UP_ARROW 72
	#define LEFT_ARROW 75
	#define RIGHT_ARROW 77
	#define DOWN_ARROW 80
	
	#define ENTER_KEY 13
	
	const char SNAKE_HEAD = (char)177;
	const char SNAKE_BODY = (char)178;
	const char WALL = (char)219;	
	const char FOOD = (char)254;
	const char BLANK = ' ';

        void gotoxy(int x, int y)
        {
            COORD p;
            p.X = x;
            p.Y = y;
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
        }

    
#else
	
	#include <stdlib.h>
	#include <termios.h>
	#include <unistd.h>
	#include <fcntl.h>
	
	

	 
	#define UP_ARROW (char)'A' 
	#define LEFT_ARROW (char)'D'
	#define RIGHT_ARROW (char)'C'
	#define DOWN_ARROW (char)'B'

	#define ENTER_KEY 10
	
	const char SNAKE_HEAD = 'X';
	const char SNAKE_BODY = '#';
	const char WALL = '#';	
	const char FOOD = '*';
	const char BLANK = ' ';

	
	void gotoxy(int x,int y)
	{
		printf("%c[%d;%df",0x1B,y,x);
	}

	int kbhit(void)
	{
		struct termios oldt, newt;
		int ch;
		int oldf;

		tcgetattr(STDIN_FILENO, &oldt);
		newt = oldt;
		newt.c_lflag &= ~(ICANON | ECHO);
		tcsetattr(STDIN_FILENO, TCSANOW, &newt);
		oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
		fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

		ch = getchar();

		tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
		fcntl(STDIN_FILENO, F_SETFL, oldf);

		if(ch != EOF)
		{
		ungetc(ch, stdin);
		return 1;
		}

		return 0;
	}

	char getch()
	{
		char ch;
		system("stty raw");
		ch= getchar();
		system("stty sane");
		//printf("%c",c);
		return(ch);
	}

	void clrscr()
	{
		system("clear");
		return;
	}
	
#endif
    // void gotoxy(int x, int y)
    // {
    //     COORD p;
    //     p.X = x;
    //     p.Y = y;
    //     SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
    // }

#define EXIT_BUTTON 27 
#define PAUSE_BUTTON 112 


char waitForAnyKey(void)
{
	int pressed;
	
	while(!kbhit());
	
	pressed = getch();
	//pressed = tolower(pressed);
	return((char)pressed);
}

int getGameSpeed(void)
{
	int speed;
	system("cls||clear");
	
	do
	{
		gotoxy(10,5);
		printf("Select The game speed between 1 and 9.");
		speed = waitForAnyKey()-48;
	} while(speed < 1 || speed > 9);
	return(speed);
}

void pauseMenu(void)
{
	int i;
	
	gotoxy(28,23);
	printf("**Paused**");
	
	waitForAnyKey();
	gotoxy(28,23);
	printf("            ");

	return;
}

int checkKeysPressed(int direction)
{
	int pressed;
	
	if(kbhit()) 
	{
		pressed=getch();
		if (direction != pressed)
		{	
		
			if(pressed == DOWN_ARROW && direction != UP_ARROW)
				direction = pressed;
			else if (pressed == UP_ARROW && direction != DOWN_ARROW)
				direction = pressed;
			else if (pressed == LEFT_ARROW && direction != RIGHT_ARROW)
				direction = pressed;
			else if (pressed == RIGHT_ARROW && direction != LEFT_ARROW)
				direction = pressed;
			else if (pressed == EXIT_BUTTON || pressed == PAUSE_BUTTON)
				pauseMenu();
		}
	}
	return(direction);
}

int collisionSnake (int x, int y, int snakeXY[][SNAKE_ARRAY_SIZE], int snakeLength, int detect)
{
	int i;
	for (i = detect; i < snakeLength; i++) 
	{
		if ( x == snakeXY[0][i] && y == snakeXY[1][i])
			return(1);
	}
	return(0);
}

int generateFood(int foodXY[], int width, int height, int snakeXY[][SNAKE_ARRAY_SIZE], int snakeLength)
{
	int i;
	
	do
	{
		srand ( time(NULL) );
		foodXY[0] = rand() % (width-2) + 2;
		srand ( time(NULL) );
		foodXY[1] = rand() % (height-6) + 2;
	} while (collisionSnake(foodXY[0], foodXY[1], snakeXY, snakeLength, 0)); 

	gotoxy(foodXY[0] ,foodXY[1]);
	printf("%c", FOOD);
	
	return(0);
}

/*
Moves the snake array forward, i.e. 
This:
	x 1 2 3 4 5 6
	y 1 1 1 1 1 1
Becomes This:
	x 1 1 2 3 4 5
	y 1 1 1 1 1 1
	
	Then depending on the direction (in this case west - left) it becomes:
	
	x 0 1 2 3 4 5
	y 1 1 1 1 1 1
	
	snakeXY[0][0]--; <- if direction left, take 1 away from the x coordinate
*/
void moveSnakeArray(int snakeXY[][SNAKE_ARRAY_SIZE], int snakeLength, int direction)
{
	int i;
	for( i = snakeLength-1; i >= 1; i-- )
	{
		snakeXY[0][i] = snakeXY[0][i-1];
		snakeXY[1][i] = snakeXY[1][i-1];
	}	
	

	switch(direction)
	{
		case DOWN_ARROW:
			snakeXY[1][0]++;
			break;
		case RIGHT_ARROW:
			snakeXY[0][0]++;
			break;
		case UP_ARROW:
			snakeXY[1][0]--;
			break;
		case LEFT_ARROW:
			snakeXY[0][0]--;
			break;			
	}
	
	return;
}

void move(int snakeXY[][SNAKE_ARRAY_SIZE], int snakeLength, int direction)
{
	int x;
	int y;

	
	x = snakeXY[0][snakeLength-1];
	y = snakeXY[1][snakeLength-1];
	
	gotoxy(x,y);
	printf("%c",BLANK);	
	
	
	gotoxy(snakeXY[0][0],snakeXY[1][0]);	
	printf("%c", SNAKE_BODY);
	
	moveSnakeArray(snakeXY, snakeLength, direction);
	
	gotoxy(snakeXY[0][0],snakeXY[1][0]);	
	printf("%c",SNAKE_HEAD);
	
	gotoxy(1,1); 
	
	return;
}

int eatFood(int snakeXY[][SNAKE_ARRAY_SIZE], int foodXY[]) 
{
	if (snakeXY[0][0] == foodXY[0] && snakeXY[1][0] == foodXY[1])
	{
		foodXY[0] = 0;
		foodXY[1] = 0; 
		
		printf("\7"); 
		return(1);
	}		
	
	return(0);
}

int collisionDetection(int snakeXY[][SNAKE_ARRAY_SIZE], int consoleWidth, int consoleHeight, int snakeLength ) 
{
	int colision = 0;
	if ((snakeXY[0][0] == 1) || (snakeXY[1][0] == 1) || (snakeXY[0][0] == consoleWidth) || (snakeXY[1][0] == consoleHeight - 4)) 
		colision = 1;
	else
		if (collisionSnake(snakeXY[0][0], snakeXY[1][0], snakeXY, snakeLength, 1)) 
			colision = 1;
			
	return(colision);
}

void refreshInfoBar(int score, int speed)
{
	gotoxy(5,23);
	printf("Score: %d", score);
	
	gotoxy(5,24);
	printf("Speed: %d", speed);

	
	return;
}


void createHighScores(void)
{
	FILE *file; 
	int i;

	file = fopen("highscores.txt","w+");
	
	if(file == NULL)
	{
		printf("FAILED TO CREATE HIGHSCORES!!! EXITING!");
		exit(0);	
	}
	
	for(i = 0; i < 5; i++)
	{
		fprintf(file,"%d",i+1);
		fprintf(file,"%s","\t0\t\t\tEMPTY\n");
	}	
	
	fclose(file);
	return;
}

int getLowestScore()
{
	FILE *fp;
	char str[128];
	int lowestScore = 0;
	int i;
	int intLength;
	
	if((fp = fopen("highscores.txt", "r")) == NULL)
	{
		
		createHighScores(); 
		if((fp = fopen("highscores.txt", "r")) == NULL)
			exit(1);
	}

	while(!feof(fp))
	{
		fgets(str, 126, fp);  
	}
	fclose(fp);	
	
	i=0;
	
	
	while(str[2+i] != '\t')
	{
		i++;
	}
	
	intLength = i;
	
	
	for(i=0;i < intLength; i++)
	{
		lowestScore = lowestScore + ((int)str[2+i] - 48) * pow(10,intLength-i-1);
	}

	return(lowestScore);
}

void inputScore(int score) 
{
	FILE *fp;
	FILE *file; 
	char str[20];
	int fScore;
	int i, s, y;
	int intLength;
	int scores[5];
	int x;
	char highScoreName[20];
	char highScoreNames[5][20];
	
	char name[20];
	
	int entered = 0;
	
	system("cls||clear"); 
	
	if((fp = fopen("highscores.txt", "r")) == NULL)
	{
		
		createHighScores(); 
		if((fp = fopen("highscores.txt", "r")) == NULL)
			exit(1);
	}
	gotoxy(10,5);
	printf("Your Score made it into the top 5!!!");
	gotoxy(10,6);
	printf("Please enter your name: ");
	gets(name);
	
	x = 0;
	while(!feof(fp))
	{
		fgets(str, 126, fp);  
		
		i=0;
		
		
		while(str[2+i] != '\t')
		{
			i++;
		}
		
		s = i;
		intLength = i;
		i=0;
		while(str[5+s] != '\n')
		{
			//printf("%c",str[5+s]);
			highScoreName[i] = str[5+s];
			s++;
			i++;
		}
		
		
		fScore = 0;
		
		for(i=0;i < intLength; i++)
		{
			//printf("%c", str[2+i]);
			fScore = fScore + ((int)str[2+i] - 48) * pow(10,intLength-i-1);
		}
		
		if(score >= fScore && entered != 1)
		{
			scores[x] = score;
			strcpy(highScoreNames[x], name);
				
			x++;
			entered = 1;
		}
		
	
		strcpy(highScoreNames[x], highScoreName);
		scores[x] = fScore;
		
		//highScoreName = "";
		for(y=0;y<20;y++)
		{
			highScoreName[y] = NULL;
		}
		
		x++;
		if(x >= 5)
			break;
	}
	
	fclose(fp);
	
	file = fopen("highscores.txt","w+");
	
	for(i=0;i<5;i++)
	{
		//printf("%d\t%d\t\t\t%s\n", i+1, scores[i], highScoreNames[i]);
		fprintf(file, "%d\t%d\t\t\t%s\n", i+1, scores[i], highScoreNames[i]);	
	}

	fclose(file);
	
	return;
}

void displayHighScores(void) 
{
	FILE *fp;
	char str[128];
	int y = 5;
	
	system("cls||clear"); 
	
	if((fp = fopen("highscores.txt", "r")) == NULL) {
		
		createHighScores();
		if((fp = fopen("highscores.txt", "r")) == NULL)
			exit(1);
	}
	
	gotoxy(10,y++);
	printf("High Scores");	
	gotoxy(10,y++);
	printf("Rank\tScore\t\t\tName");
	while(!feof(fp)) {
		gotoxy(10,y++);
		if(fgets(str, 126, fp)) 
			printf("%s", str);
	}

	fclose(fp);	
	gotoxy(10,y++);
	
	printf("Press any key to continue...");
	waitForAnyKey();	
	return;
}


void youWinScreen(void)
{
	int x = 6, y = 7;

	gotoxy(x,y++);
	printf("\t \t you won");

	
	waitForAnyKey();
	system("cls||clear"); 
	return;
}

void gameOverScreen(void)
{
	int x = 17, y = 3;
	
	
	
	gotoxy(x,y++);
	printf("\t \t Game over\n");
	
	
	waitForAnyKey();
	system("cls||clear"); 
	return;
}


void startGame( int snakeXY[][SNAKE_ARRAY_SIZE], int foodXY[], int consoleWidth, int consoleHeight, int snakeLength, int direction, int score, int speed)
{
	int gameOver = 0;
	clock_t endWait;
	
	
	int waitMili = CLOCKS_PER_SEC-(speed)*(CLOCKS_PER_SEC/10);	
	int tempScore = 10*speed;
	int oldDirection;
	int canChangeDirection = 1;
	

	endWait = clock() + waitMili;

	do
	{
		if(canChangeDirection)
		{
			oldDirection = direction;
			direction = checkKeysPressed(direction);
		}
		
		if(oldDirection != direction)
			canChangeDirection = 0;
			
		if(clock() >= endWait) 
		{
			//gotoxy(1,1);
			//printf("%d - %d",clock() , endWait);
			move(snakeXY, snakeLength, direction);
			canChangeDirection = 1;

				
			if(eatFood(snakeXY, foodXY))
			{
				generateFood( foodXY, consoleWidth, consoleHeight, snakeXY, snakeLength); 
				snakeLength++;
				score+=speed;
				//x++;
				//gotoxy(1,1);
				//printf("%d >= %d", 10*speed+score, tempScore);
				if( score >= 10*speed+tempScore)
				//if( 2 >= 2)
				{
					speed++;
					tempScore = score;

					if(speed <= 9)
						waitMili = waitMili - (CLOCKS_PER_SEC/10);
					else
					{
						if(waitMili >= 40) 
							waitMili = waitMili - (CLOCKS_PER_SEC/200);
						
					}
					
				}
				
				refreshInfoBar(score, speed);
			}
			
			endWait = clock() + waitMili; 
		}
		
		gameOver = collisionDetection(snakeXY, consoleWidth, consoleHeight, snakeLength);

		if(snakeLength >= SNAKE_ARRAY_SIZE-5) 
		{
			gameOver = 2;
			score+=1500; 
		}
		
	} while (!gameOver);
	
	switch(gameOver)
	{
		case 1:
			printf("\7");
			printf("\7");

			gameOverScreen();

			break;
		case 2:
			youWinScreen();
			break;
	}
	
	if(score >= getLowestScore() && score != 0)
	{
		inputScore(score);
		displayHighScores();
	}
	
	return;
}

void loadEnviroment(int consoleWidth, int consoleHeight)
{
	int i;
	int x = 1, y = 1;
	int rectangleHeight = consoleHeight - 4;
	system("cls||clear"); 
	
	gotoxy(x,y); 
	
	for (; y < rectangleHeight; y++)
	{
		gotoxy(x, y); 
		printf("%c",WALL);
		
		gotoxy(consoleWidth, y); 
		printf("%c",WALL);
	}
	
	y = 1;
	for (; x < consoleWidth+1; x++)
	{
		gotoxy(x, y); 
		printf("%c",WALL);
		
		gotoxy(x, rectangleHeight); 
		printf("%c",WALL);
	}
	
	
	return;
}

void loadSnake(int snakeXY[][SNAKE_ARRAY_SIZE], int snakeLength)
{
	int i;
	
	for (i = 0; i < snakeLength; i++)
	{
		gotoxy(snakeXY[0][i], snakeXY[1][i]);
		printf("%c", SNAKE_BODY); 
	}
	
	return;
}

void prepairSnakeArray(int snakeXY[][SNAKE_ARRAY_SIZE], int snakeLength)
{
	int i, x;
	int snakeX = snakeXY[0][0];
	int snakeY = snakeXY[1][0];
	
	
	
	for(i = 1; i <= snakeLength; i++)
	{
		snakeXY[0][i] = snakeX + i;
		snakeXY[1][i] = snakeY;
	}
	
	return;
}


void loadGame(void)
{
	int snakeXY[2][SNAKE_ARRAY_SIZE]; 
	
	int snakeLength = 4; 
	
	int direction = LEFT_ARROW; 
	
	int foodXY[] = {5,5};
	
	int score = 0;
	
	
	int consoleWidth = 80;
	int consoleHeight = 25;
	
	int speed = getGameSpeed();
	
	snakeXY[0][0] = 40; 
	snakeXY[1][0] = 10;
	
	loadEnviroment(consoleWidth, consoleHeight); 
	prepairSnakeArray(snakeXY, snakeLength);
	loadSnake(snakeXY, snakeLength);
	generateFood( foodXY, consoleWidth, consoleHeight, snakeXY, snakeLength);
	refreshInfoBar(score, speed); 
	startGame(snakeXY, foodXY, consoleWidth, consoleHeight, snakeLength, direction, score, speed);

	return;
}



int menuSelector(int x, int y, int yStart)
{
	char key;
	int i = 0;
	x = x - 2;
	gotoxy(x,yStart);
	
	printf(">");
	
	gotoxy(1,1);

	
	do
	{
		key = waitForAnyKey();
		
		if ( key == (char)UP_ARROW )
		{
			gotoxy(x,yStart+i);
			printf(" ");
			
			if (yStart >= yStart+i ) 
				i = y - yStart - 2;
			else
				i--;
			gotoxy(x,yStart+i);
			printf(">");
		}
		else
			if ( key == (char)DOWN_ARROW )
			{
				gotoxy(x,yStart+i);
				printf(" ");
				
				if (i+2 >= y - yStart ) 
					i = 0;
				else
					i++;
				gotoxy(x,yStart+i);
				printf(">");				
			}	
			//gotoxy(1,1);
			//printf("%d", key);
	} while(key != (char)ENTER_KEY); 
	return(i);
}



void exitYN(void)
{
	char pressed;
	gotoxy(9,8);
	printf("Are you sure you want to exit(Y/N)\n");
	
	do
	{
		pressed = waitForAnyKey();
		pressed = tolower(pressed);
	} while (!(pressed == 'y' || pressed == 'n'));
	
	if (pressed == 'y')
	{
		
		exit(1);
	}
	return;
}

int main() 
{

	load();
    Print();
	
	do
	{	
		switch(mainMenu())
		{
			case 0:
				loadGame();
				break;
			case 1:
				displayHighScores();
				break;	
			case 2:
				exitYN();
				break;		
						
		}		
	} while(1);	
	
	return(0);
}

