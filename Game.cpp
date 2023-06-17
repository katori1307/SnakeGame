#include "SnakeSegment.h"


Game::Game()
{
	// initialize snake size
	snake.reserve(initialSize);
	// create snake;
	for (int i = 0; i < initialSize; i++)
		snake.emplace_back(SnakeSegment(right_board / 2, (bottom_board / 2) + i));

	// Game status;
	this->isOver = false;

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
			processInput();


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

void Game::updateDirection()
{
	if (this->currentDirection != Direction::None)
		this->nextDirection = currentDirection;
}

void Game::moveSnake()
{
	SnakeSegment head = this->snake.front();
	SnakeSegment newHead = head;
	int X = newHead.getX();
	int Y = newHead.getY();
	switch (this->nextDirection)
	{
	case Direction::Up:
		newHead.setY(Y--);
		break;
	case Direction::Down:
		newHead.setY(Y++);
		break;
	case Direction::Right:
		newHead.setX(X++);
		break;
	case Direction::Left:
		newHead.setX(X--);
		break;
	}
	snake.insert(snake.begin(), newHead);
	snake.pop_back();
	currentDirection = nextDirection;
}

void Game::checkCollision()
{
	SnakeSegment head = snake.front();
	int X = head.getX();
	int Y = head.getY();
	if (X <= left_board || X >= right_board || Y <= top_board || Y >= bottom_board)
		this->isOver = true;
	for (auto v : this->snake)
	{
		if (X == v.getX() && Y == v.getY())
		{
			this->isOver = true;
			break;
		}
	}

	if (X == this->food.getX() && Y == this->food.getY())
	{
		snake.emplace_back(SnakeSegment(food.getX(), food.getY()));
		generateFood();
	}
}

void Game::drawObject()
{
	
}

void Game::render()
{
	drawBoard();


}