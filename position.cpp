#include "position.h"

int Position::get_x()
{
	return coord_x;
}

int Position::get_y()
{
	return coord_y;
}

void Position::set_x(int pX=0)
{
	if(pX >= MIN_X && pX <= MAX_X)
	{	
		coord_x = pX;
	}
}

void Position::set_y(int pY=0)
{
	if(pY >= MIN_Y && pY <= MAX_Y)
	{
		coord_y = pY;
	}
}

const int Position::MIN_X;
const int Position::MAX_X;
const int Position::MIN_Y;
const int Position::MAX_Y;
