#include "stdafx.h"
#include <iostream>
#include <ctime>
#include <conio.h>
#include <Windows.h>
#include <vector>

using namespace std;

const unsigned short int width = 40;
const unsigned short int height = 20;
unsigned short int  fruitX, fruitY;
unsigned short int  score = 0;
bool GameOver;

vector<unsigned short  int> TailX;
vector<unsigned short  int> TailY;

enum eDirection { pause = 0, LEFT, RIGHT, UP, DOWN };
eDirection state;

inline void change_fruit_the_coordinates()
{	
	for (unsigned short int i=0; i<size(TailX); i++)
	{
				fruitX = rand() % 36 + 2;
				fruitY = rand() % 16 + 2;

			 if (fruitX != TailX[i] || fruitY != TailY[i]) break;
	}
}

void Setup()
{
	GameOver = false;
	state = pause;
	srand((unsigned int)time(NULL));

	TailX.push_back(rand() % 36 + 2);
	TailY.push_back(rand() % 16 + 2);

	change_fruit_the_coordinates();
}

void Draw()
{

	system("cls");
	register unsigned int i;
	register unsigned int j;
	register unsigned short int k;
	for ( i = 0; i < height; i++)
	{
		for ( j = 0; j < width; j++)
		{
			bool print = false;
			if (i == 0 || i == height - 1)			
				cout << "#";			
			else if (j == 0 || j == width - 1)			
				cout << "#";			
			else if (i == fruitY && j == fruitX)
				cout << "@";
			else if (TailX[0] == j && TailY[0] == i)			
				cout << "O";			
			else
			{
				for ( k = 1; k < TailX.size(); k++)
				{
					if (TailX[k] == j && TailY[k] == i)
					{
						print = true;
						cout << "o";
					}
				}
				if (!print)
					cout << " ";
			}
		}
		cout << endl;
	}
	cout << "Score: " << score << endl;
	cout << "Use SPACE to end the game!" << endl;
}

void Input()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a':
			state = LEFT;
			break;
		case 'w':
			state = UP;
			break;
		case 'd':
			state = RIGHT;
			break;
		case 's':
			state = DOWN;
			break;

		case (char)32:
			GameOver = true;
			break;
		}
	}
}


void Logic()
{
	unsigned short int prevX = *(TailX.cend() - 1);
	unsigned short int prevY = *(TailY.cend() - 1);
	register unsigned short int i;

	for (i = TailX.size() - 1; i != 0; i--)	
		TailX[i] = TailX[i - 1];
	
	for (i = TailY.size() - 1; i != 0; i--)	
		TailY[i] = TailY[i - 1];	

	switch (state)
	{
	case LEFT:
		--TailX[0];
		break;

	case RIGHT:
		++TailX[0];
		break;

	case UP:
		--TailY[0];
		break;

	case DOWN:
		++TailY[0];
		break;

	default:
		break;
	}

	if (TailX[0] > width || TailX[0] < 0 || TailY[0]<0 || TailY[0]>height)
	{
		Sleep(200);
		system("cls");
		cout << "GameOver" << endl;
		cout << "Your score: " << score << endl;
		GameOver = true;
	}

	for ( i = 1; i < TailX.size(); i++)	
		if (TailX[0] == TailX[i] && TailY[0] == TailY[i])
		{
			Sleep(200);
			system("cls");
			cout << "GameOver" << endl;
			cout << "Your score: " << score << endl;
			GameOver = true;
		}
	

	if (TailX[0] == fruitX && TailY[0] == fruitY)
	{
		score += 10;
		change_fruit_the_coordinates();

		TailX.push_back(prevX);
		TailY.push_back(prevY);
	}
}


int main()
{
	Setup();
	while (!GameOver)
	{
		Draw();
		Input();
		Logic();
		Sleep(100);
	}
	system("pause");
	return 0;
}