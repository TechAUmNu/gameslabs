#include "Point.h"

using namespace std;

Point::Point()
{
	parent = NULL;
	closed = false;
	opened = false;
	position = Position(0, 0);
	f = g = h = 0;
}

Point::Point(int x, int y, bool w)
{
	Point();

	this->walkable = w;
	position = Position(x, y);
}





void Point::setParent(Point *p)
{
	parent = p;
}

int Point::getGScore(Point *p)
{
	return p->g + ((position.x == p->position.x || position.y == p->position.y) ? 10 : 14);
}

int Point::getHScore(Point *p)
{
	return (abs(p->position.x - position.x) + abs(p->position.y - position.y)) * 10;
}

int Point::getGScore()
{
	return g;
}

int Point::getHScore()
{
	return h;
}

int Point::getFScore()
{
	return f;
}

void Point::computeScores(Point *end)
{
	g = getGScore(parent);
	h = getHScore(end);
	f = g + h;
}

bool Point::hasParent()
{
	return parent != NULL;
}