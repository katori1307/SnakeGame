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
	//// draw object
	//drawObject();
	// initial state of movement.
	currentDirection = Direction::Up;
	nextDirection = Direction::Up;
	// score
	score = 0;
	// initial title and choices
	title.push_back(",------.   ,---.  ,--.  ,--.     ,---.    ,---.  ,--.  ,--.    ,--.   ,--. ,-----. ,--. ");
	title.push_back("|  .--. ' /  O  \\ |  ,'.|  |    '   .-'  /  O  \\ |  ,'.|  |    |   `.'   |'  .-.  '|  | ");
	title.push_back("|  '--'.'|  .-.  ||  |' '  |    `.  `-. |  .-.  ||  |' '  |    |  |'.'|  ||  | |  ||  | ");
	title.push_back("|  |\\  \\ |  | |  ||  | `   |    .-'    ||  | |  ||  | `   |    |  |   |  |'  '-'  '|  | ");
	title.push_back("`--' '--'`--' `--'`--'  `--'    `-----' `--' `--'`--'  `--'    `--'   `--' `-----' `--' ");

	choice.push_back("1. New game");
	choice.push_back("2. Load game");
	choice.push_back("3. Settings");
	choice.push_back("4. About me");
	choice.push_back("5. Exit");

	high_score.push_back("  ____   ____ ___  ____  _____ ");
	high_score.push_back(" / ___| / ___/ _ \\|  _ \\| ____|");
	high_score.push_back(" \\___ \\| |  | | | | |_) |  _|  ");
	high_score.push_back("  ___) | |__| |_| |  _ <| |___ ");
	high_score.push_back(" |____/ \\____\\___/|_| \\_\\_____|");


	line = 0;
}

void Game::run()
{
	system("cls");
	drawObject();
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
		Sleep(Speed);
	}
}

void Game::drawBoard()
{
	// draw game board
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

	// draw high score menu
	int x = left_score_board + ((right_score_board - left_score_board - high_score[0].size()) / 2);
	for (int i = 0; i < high_score.size(); i++)
	{
		gotoXY(x, 3 + i);
		cout << high_score[i];
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
		this->score += 100;
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
	initializeObject();
	while (!endGame)
	{
		
		int xChoice = (consoleWidth - choice[0].size()) / 2;
		int input = toupper(_getch());
		switch (input)
		{
		case 'W':
			gotoXY(xChoice, line + 15);
			textColor(DEFAULT);
			cout << choice[line];

			if (line == 0) line = 4;
			else line--;

			gotoXY(xChoice, line + 15);
			textColor(LIGHT_RED);
			cout << choice[line];
			break;

		case 'S':
			gotoXY(xChoice, line + 15);
			textColor(DEFAULT);
			cout << choice[line];

			if (line == 4) line = 0;
			else line++;

			gotoXY(xChoice, line + 15);
			textColor(LIGHT_RED);
			cout << choice[line];
			break;
		case 'E':
			switch (line)
			{
			case 0: // new game
				run();
				break;

			case 4:
				endGame = true;
				break;
			}
		}
		if (isOver)
		{
			system("cls");
			initializeObject();
			continue;
		}	
	}	
}

void Game::drawMenu()
{
	textColor(YELLOW);
	// print title
	for (int i = 0; i < title.size(); i++)
	{
		gotoXY((consoleWidth - title[0].size()) / 2, 5 + i);
		cout << title[i];
	}
	textColor(DEFAULT);
	for (int i = 0; i < choice.size(); i++)
	{
		gotoXY((consoleWidth - choice[0].size()) / 2, 15 + i);
		cout << choice[i];
	}
	gotoXY((consoleWidth - choice[0].size()) / 2, 25);
	cout << "Press E to interact";
	gotoXY((consoleWidth - choice[0].size()) / 2, 26);
	cout << "W, S to move";
	
}

void Game::initializeObject()
{
	isOver = false;
	line = 0;
	drawMenu();
	textColor(LIGHT_RED);
	gotoXY((consoleWidth - choice[0].size()) / 2, 15);
	cout << choice[0];
	snake.clear();
	// initialize snake size
	snake.reserve(initialSize);
	// create snake;
	for (int i = 0; i < initialSize; i++)
		snake.emplace_back(SnakeSegment(right_board / 2, (bottom_board / 2) + i));
	// create food;
	this->food.generateFood();
	// score
	score = 0;
	// initial state of movement.
	currentDirection = Direction::Up;
	nextDirection = Direction::Up;
}
