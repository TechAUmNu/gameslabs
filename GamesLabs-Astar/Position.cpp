#include "Position.h"

Position::Position()
{
	set(0.f, 0.f);
}

Position::Position(float x, float y)
{
	set(x, y);
}

void Position::set(float x, float y)
{
	this->x = x;
	this->y = y;
}

float Position::getDistanceTo(Position *p)
{
	return sqrt(pow((x - p->x), 2) + pow((y - p->y), 2));
}
