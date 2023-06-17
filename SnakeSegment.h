#include <iostream>
#include <vector>
#include <conio.h>
#include <windows.h>
#include <locale>

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

using namespace std;

const int initialSize = 3;
const int GameWidth = 40;
const int GameHeight = 20;
const int Speed = 100;

const int left_board = 0;
const int right_board = 80;
const int top_board = 0;
const int bottom_board = 29;
const int left_score_board = right_board + 1;
const int right_score_board = 119;


//const char* SnakeHead = "\xE2\x98\x85";
//const char* SnakeBody = "\xE2\x96\x88";
//const char* Food = "\xE2\x98\xBC";


enum class Direction
{
	None, Up, Down, Left, Right
};




class SnakeSegment
{
protected:
	int x, y;
public:
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
	//SnakeSegment food;
	Direction currentDirection;
	Direction nextDirection;
	bool isOver;
	bool endGame;
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


};