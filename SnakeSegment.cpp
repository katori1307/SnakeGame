
#include "SnakeSegment.h"

SnakeSegment::SnakeSegment()
{
	x = y = 0;
}

SnakeSegment::SnakeSegment(int xPos, int yPos)
{
	x = xPos;
	y = yPos;
}


void Food::generateFood()
{
	this->x = rand() % GameWidth;
	this->y = rand() % GameHeight;
}


Game::Game()
{
	// initialize snake size
	snake.reserve(initialSize);
	// create snake;
	for (int i = 0; i < initialSize; i++)
		snake.emplace_back(SnakeSegment(right_board / 2, (bottom_board / 2) + i));

	// create food;
	Food f;
	f.generateFood();



	// initial state of movement.
	currentDirection = Direction::None;
	nextDirection = Direction::None;
}


void Game::run()
{
	while (!endGame)
	{
		// draw menu screen;
		// 
		// 
		// draw game board;

		drawBoard();


		while (!isOver)
		{
			// 1: process input

			// 2: update

			// 3: render

			// 4: sleep (game's speed)

		}
	}
}

void Game::drawBoard()
{
	for (int i = left_board - 1; i < right_board; i++)
	{
		gotoXY(i, top_board);
		cout << "-";
		gotoXY(i, bottom_board);
		cout << "-";
	}
	for (int i = top_board; i < bottom_board; i++)
	{
		gotoXY(left_board, i);
		cout << "|";
		gotoXY(right_board, i);
		cout << "|";
	}
	for (int i = left_score_board; i < right_score_board; i++)
	{
		gotoXY(i, top_board);
		cout << "-";
		gotoXY(i, bottom_board);
		cout << "-";
	}
	for (int i = top_board; i < bottom_board; i++)
	{
		gotoXY(left_score_board, i);
		cout << "|";
		gotoXY(right_score_board, i);
		cout << "|";
	}	
}

void Game::gotoXY(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void Game::textColor(int color)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}



void Food::generateFood()
{
	this->x = rand() % right_board;
	this->y = rand() % bottom_board;
}

void Game::processInput()
{
	int input = toupper(_getch());
	switch (input)
	{
	case 'W':
		nextDirection = Direction::Up;
		break;
	case 'A':
		nextDirection = Direction::Left;
		break;
	case 'S':
		nextDirection = Direction::Down;
		break;
	case 'D':
		nextDirection = Direction::Right;
		break;
	}
}

