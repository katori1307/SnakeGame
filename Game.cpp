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
	this->isPause = false;
	// create food;
	this->food.generateFood();
	//// draw object
	//drawObject();
	// initial state of movement.
	currentDirection = Direction::Up;
	nextDirection = Direction::Up;
	// score
	this->score = 0;
	//speed
	this->speed = Speed;
	// initial title and choices
	title.push_back(",------.   ,---.  ,--.  ,--.     ,---.    ,---.  ,--.  ,--.    ,--.   ,--. ,-----. ,--. ");
	title.push_back("|  .--. ' /  O  \\ |  ,'.|  |    '   .-'  /  O  \\ |  ,'.|  |    |   `.'   |'  .-.  '|  | ");
	title.push_back("|  '--'.'|  .-.  ||  |' '  |    `.  `-. |  .-.  ||  |' '  |    |  |'.'|  ||  | |  ||  | ");
	title.push_back("|  |\\  \\ |  | |  ||  | `   |    .-'    ||  | |  ||  | `   |    |  |   |  |'  '-'  '|  | ");
	title.push_back("`--' '--'`--' `--'`--'  `--'    `-----' `--' `--'`--'  `--'    `--'   `--' `-----' `--' ");

	choice.push_back("1. New game");
	choice.push_back("2. Leader board");
	choice.push_back("3. Settings");
	choice.push_back("4. About me");
	choice.push_back("5. Exit");

	high_score.push_back("  ____   ____ ___  ____  _____ ");
	high_score.push_back(" / ___| / ___/ _ \\|  _ \\| ____|");
	high_score.push_back(" \\___ \\| |  | | | | |_) |  _|  ");
	high_score.push_back("  ___) | |__| |_| |  _ <| |___ ");
	high_score.push_back(" |____/ \\____\\___/|_| \\_\\_____|");

	playing_choice.push_back("P to pause/unpause");
	playing_choice.push_back("Esc to exit");
	//playing_choice.push_back("S to save");
	playing_choice.push_back("M to turn on/off the music");

	settings.push_back(" ,---.           ,--.    ,--.  ,--.                       ");
	settings.push_back("'   .-'  ,---. ,-'  '-.,-'  '-.`--',--,--,  ,---.  ,---.  ");
	settings.push_back("`.  `-. | .-._:'-.  .-''-.  .-',--.|      \\| .-. |(  .-'  ");
	settings.push_back(".-'    |\\   --.  |  |    |  |  |  ||  ||  |' '-' '.-'  `) ");
	settings.push_back("`-----'  `----'  `--'    `--'  `--'`--''--'.`-  / `----'  ");
	settings.push_back("                                           `---'          ");




	line = 0;
}

void Game::run()
{
	system("cls");
	drawObject();
	drawBoard();
	while (!isOver)
	{
		// handle game pause;
		game_pause();
		// process input
		processInput();
		// update direction, move snake, check collision
		update();
		// draw objects in game
		render();
		// sleep (game's speed)
		Sleep(this->speed);
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
	for (int i = left_score_cell; i < right_score_cell; i++)
	{
		gotoXY(i, 10);
		cout << "-";
		gotoXY(i, 12);
		cout << "-";
	}

	
	
	x = left_score_board + ((right_score_board - left_score_board - playing_choice[playing_choice.size() - 1].size()) / 2);
	for (int i = 0; i < playing_choice.size(); i++)
	{
		gotoXY(x, 18 + i);
		cout << playing_choice[i];
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
		case 'P':
			if (isPause == false) isPause = true;
			break;
		case 27:
			isOver = true;
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
	// draw snake, food
	drawObject();
	eraseObject();
	// print score
	string s = to_string(this->score);
	gotoXY(left_score_cell + ((right_score_cell - left_score_cell - s.size()) / 2), 11);
	cout << s;
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

			case 2: // settings
				system("cls");
				handleSettings();
				system("cls");
				initializeObject();
				continue;
				break;
			case 4: // exit
				endGame = true;
				break;
			
			}
		}
		if (isOver)
		{
			while (1)
			{
				string str = "Enter name: ";
				string name;
				int x = left_score_board + 3;
				gotoXY(x, 25);
				cout << "Save the highscore ? (Y/N)";
				char input = toupper(_getch());
				if (input == 'Y')
				{
					fstream file;
					file.open("leaderboard.txt", ios::app);
					gotoXY(x, 25);
					cout << "                          ";
					gotoXY(x, 25);
					cout << str;
					cin >> name;
					file << name << " ";
					file << this->score << endl;
					break;
				}
				if (input == 'N')
					break;
			}
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
	gotoXY((consoleWidth - choice[0].size()) / 2, 27);
	cout << "Go to settings to adjust speed and music";
	
}

void Game::initializeObject()
{
	isOver = false;
	isPause = false;
	line = 0;
	score = 0;
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
	// speed
	this->speed = normalMode;
}

void Game::game_pause()
{
	while (isPause)
	{
		if (_kbhit())
		{
			char input = toupper(_getch());
			if (input == 'P') isPause = false;
		}
		else continue;
	}
}

void Game::handleSettings()
{
	textColor(DEFAULT);
	// draw "SETTINGS"
	int x = (consoleWidth - settings[0].size()) / 2;
	vector<string> choices;
	choices.push_back("1. Music");
	choices.push_back("2. Game mode");
	for (int i = 0; i < settings.size(); i++)
	{
		gotoXY(x, 3 + i);
		cout << settings[i];
	}
	//draw board;
	for (int i = 30; i < 90; i++)
	{
		gotoXY(i, 9);
		cout << "-";
		gotoXY(i, consoleHeight - 5);
		cout << "-";
	}
	for (int i = 9; i < consoleHeight - 5; i++)
	{
		gotoXY(30, i);
		cout << "|";
		gotoXY(89, i);
		cout << "|";
	}
	gotoXY(35, 11);
	cout << "E to interact";
	gotoXY(35, 12);
	cout << "W, S to move";
	gotoXY(35, 13);
	cout << "Esc to exit";
	for (int i = 0; i < choices.size(); i++)
	{
		gotoXY(35, 15 + i);
		cout << choices[i];
	}
	int line = 0;
	x = 35;
	bool isDone = false;
	gotoXY(35, 15);
	textColor(LIGHT_RED);
	cout << choices[line];
	textColor(DEFAULT);

	string savedChanges = "Saved changes!";
	vector<string> mode;
	int index = 0;
	bool finishChanging = false;

	while (!isDone)
	{
		char input = toupper(_getch());
		switch (input)
		{
		case 'W': case 'S':
			textColor(DEFAULT);
			gotoXY(35, line + 15);
			cout << choices[line];
			if (line == 0) line = 1;
			else if (line == 1) line = 0;
			textColor(LIGHT_RED);
			gotoXY(35, line + 15);
			cout << choices[line];
			break;
		case 'E':
			
			switch (line)
			{
			case 0: // handle music
				mode.clear();
				mode.push_back("==> On");
				mode.push_back("==> Off");
				gotoXY(50, 15);
				index = 0;
				finishChanging = false;
				textColor(LIGHT_GREEN);
				cout << mode[0];
				while (!finishChanging)
				{
					char input2 = toupper(_getch());
					switch (input2)
					{
					case 'W': case 'S':
						gotoXY(50, 15);
						cout << "       ";
						if (index == 0) index = 1;
						else index = 0;
						gotoXY(50, 15);
						cout << mode[index];
						break;
					case 'E':
						switch (index)
						{
						case 0:
							// turn on the music
							break;
						case 1:
							// turn off the music
							break;
						}
						gotoXY(50, 15);
						cout << "       ";
						gotoXY(35, 20);
						cout << "              ";
						gotoXY(35, 20);
						textColor(LIGHT_RED);
						for (int i = 0; i < savedChanges.size(); i++)
						{
							cout << savedChanges[i];
							Sleep(10);
						}
						finishChanging = true;
						break;
					case 27:
						gotoXY(50, 15);
						cout << "       ";
						finishChanging = true;
						break;
					}
				}
				break;
			case 1: // handle game mode
				mode.clear();
				mode.push_back("==> Easy");
				mode.push_back("==> Normal");
				mode.push_back("==> Extreme");
				gotoXY(50, 16);
				index = 0;
				finishChanging = false;
				textColor(LIGHT_GREEN);
				cout << mode[0];
				while (!finishChanging)
				{
					char input2 = toupper(_getch());
					switch (input2)
					{
					case 'W':
						gotoXY(50, 16);
						cout << "           ";
						
						if (index == mode.size() - 1) index = 0;
						else index++;
						textColor(LIGHT_GREEN);
						gotoXY(50, 16);
						cout << mode[index];
						break;
					case 'S':
						gotoXY(50, 16);
						cout << "           ";

						if (index == 0) index = mode.size() - 1;
						else index--;
						textColor(LIGHT_GREEN);
						gotoXY(50, 16);
						cout << mode[index];
						break;
					case 'E':
						if (index == 0) this->speed = easyMode;
						if (index == 1) this->speed = normalMode;
						if (index == 2) this->speed = extremeMode;
						gotoXY(50, 16);
						cout << "           ";
						gotoXY(35, 20);
						cout << "              ";
						gotoXY(35, 20);
						textColor(LIGHT_RED);
						for (int i = 0; i < savedChanges.size(); i++)
						{
							cout << savedChanges[i];
							Sleep(10);
						}
						finishChanging = true;
						break;
					case 27:
						gotoXY(50, 16);
						cout << "           ";
						finishChanging = true;
						break;
					}
				}
			}
			break;
		case 27:
			isDone = true;
			break;

		}
	}

	



}
