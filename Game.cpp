#include "SnakeSegment.h"


Game::Game()
{
	// hide cursor
	hideCursor();
	// initialize snake size
	snake.reserve(initialSize);
	// create snake;
	for (int i = 0; i < initialSize; i++)
		snake.emplace_back(SnakeSegment(right_board / 2, (bottom_board / 2) + i));
	// Game status;
	this->isOver = false;
	this->endGame = false;
	// create food;
	this->food.generateFood();
	// draw object
	drawObject();
	// initial state of movement.
	currentDirection = Direction::Up;
	nextDirection = Direction::Up;

}

void Game::run()
{
	drawBoard();
	while (!isOver)
	{
		// 1: process input
		processInput();
		// 2: update direction, move snake, check collision
		update();
		// 3: draw objects in game
		render();
		// 4: sleep (game's speed)
		Sleep(200);
	}
}

void Game::drawBoard()
{
	for (int i = left_board; i < right_board; i++)
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
	if (_kbhit())
	{
		char input = toupper(_getch());
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
	else
		nextDirection = currentDirection;
}

void Game::updateDirection()
{
	// assign next direction to current direction to handle.	
	if (this->nextDirection != Direction::None)
		currentDirection = nextDirection;
}


void Game::moveSnake()
{
	SnakeSegment head = this->snake.front();
	SnakeSegment newHead = head;
	int X = newHead.getX();
	int Y = newHead.getY();
	switch (this->currentDirection)
	{
	case Direction::Up:
		newHead.setY(Y - 1);
		break;
	case Direction::Down:
		newHead.setY(Y + 1);
		break;
	case Direction::Right:
		newHead.setX(X + 1);
		break;
	case Direction::Left:
		newHead.setX(X - 1);
		break;
	}
	snake.insert(snake.begin(), newHead);
	//snake.pop_back();
}

void Game::checkCollision()
{
	SnakeSegment head = snake.front();
	int X = head.getX();
	int Y = head.getY();
	if (X == left_board || X == right_board || Y == top_board || Y == bottom_board)
		this->isOver = true;
	for (int i = 1; i < snake.size(); i++)
	{
		if (X == snake[i].getX() && Y == snake[i].getY())
		{
			isOver = true;
			break;
		}

	}
	if (X == this->food.getX() && Y == this->food.getY())
	{
		snake.emplace_back(SnakeSegment(food.getX(), food.getY()));
		this->food.generateFood();
	}
}

void Game::drawObject()
{
	// draw snake's head
	gotoXY(snake[0].getX(), snake[0].getY());
	cout << "Q";
	for (int i = 1; i < snake.size(); i++)
	{
		gotoXY(snake[i].getX(), snake[i].getY());
		cout << "o";
	}
	//draw food;
	gotoXY(this->food.getX(), this->food.getY());
	cout << "x";
}

void Game::render()
{
	// draw game board;
	//drawBoard();
	// draw snake, food
	drawObject();
	eraseObject();
}

void Game::update()
{
	updateDirection();
	moveSnake();
	checkCollision();
}

void Game::eraseObject()
{
	int index = snake.size() - 1;
	gotoXY(snake[index].getX(), snake[index].getY());
	cout << " ";
	snake.pop_back();
}

void Game::hideCursor()
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(consoleHandle, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(consoleHandle, &cursorInfo);
}


void Game::launch()
{
	vector<string> title;
	
	
	// print title
	gotoXY(0, 0);
	for (int i = 0; i < title.size(); i++)
		cout << title[i] << endl;
	
}
