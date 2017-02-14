#pragma once

#include "Position.h"

#include <cstdlib>
#include <iostream>

class Point
{
public:

	Point();
	Point(int x, int y, bool w);

	

	void setParent(Point *p);
	void computeScores(Point *end);
	int getGScore(Point *p);
	int getHScore(Point *p);
	int getGScore();
	int getHScore();
	int getFScore();



	bool hasParent();

	bool walkable;
	bool closed;
	bool opened;
	

	Position position;
	Point *parent;
private:

	

	unsigned int f;
	unsigned int g;
	unsigned int h;

	
};

