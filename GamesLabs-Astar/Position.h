#pragma once
#include <math.h>

class Position
{
public:

	Position();
	Position(float x, float y);	

	void set(float x, float y);

	float getDistanceTo(Position *p);
	
	float x;
	float y;

	unsigned int f;
	unsigned int g;
	unsigned int h;
};

