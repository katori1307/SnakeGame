#include <iostream>
#include <vector>
#include <conio.h>
#include <windows.h>
#include <locale>
#include <string>
#include <fstream>

#define BLACK		 0
#define BLUE		 1
#define GREEN		 2
#define AQUA		 3
#define RED			 4
#define PURPLE		 5
#define YELLOW		 6
#define WHITE		 7
#define GRAY		 8
#define LIGHT_BLUE	 9
#define LIGHT_GREEN	 10
#define LIGHT_AQUA	 11
#define LIGHT_RED	 12
#define LIGHT_PURPLE 13
#define LIGHT_YELLOW 14
#define BRIGHT_WHITE 15
#define DEFAULT		 11

using namespace std;

const int initialSize = 3;
const int Speed = 100;
const int consoleWidth = 120;
const int consoleHeight = 30;
const int easyMode = 300;
const int normalMode = 100;
const int extremeMode = 50;

const int left_board = 0;
const int right_board = 80;
const int top_board = 0;
const int bottom_board = 29;
const int left_score_board = right_board + 1;
const int right_score_board = 119;
const int left_score_cell = left_score_board + 10;
const int right_score_cell = right_score_board - 10;


//const char* SnakeHead = u8"\u2593";
//const char* SnakeBody = u8"\u2588";
//const char* FoodSegment = u8"\u25BC";




enum class Direction
{
	None, Up, Down, Left, Right
};




class SnakeSegment
{
protected:
	int x, y;
public:
	int getX();
	int getY();
	void setX(int x);
	void setY(int y);
	SnakeSegment();
	SnakeSegment(int xPos, int yPos);
};

class Food : public SnakeSegment
{
public:
	void generateFood();
};


class Game
{
private:
	std::vector<SnakeSegment> snake;
	Food food;
	Direction currentDirection;
	Direction nextDirection;
	bool isOver;
	bool endGame;
	bool isPause;
	int score;
	int speed;
	
	std::vector<string> title;
	std::vector<string> choice;
	std::vector<string> high_score;
	std::vector<string> playing_choice;
	std::vector<string> settings;
	int line;
public:
	Game();
	void drawBoard();
	void run();
	void processInput();
	void update();
	void updateDirection();
	void moveSnake();
	void checkCollision();
	void generateFood();
	void gotoXY(int x, int y);
	void textColor(int color);
	void render();
	void drawObject();
	void eraseObject();
	void hideCursor();
	void launch();
	void drawMenu();
	void initializeObject();
	void game_pause();
	void handleSettings();
	void handleLeaderboard();
};

