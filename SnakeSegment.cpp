
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

int SnakeSegment::getX()
{
	return this->x;
}

int SnakeSegment::getY()
{
	return this->y;
}

void SnakeSegment::setX(int x)
{
	this->x = x;
}

void SnakeSegment::setY(int y)
{
	this->y = y;
}

void Food::generateFood()
{
	this->x = rand() % right_board;
	this->y = rand() % bottom_board;
}













