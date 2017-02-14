#pragma once

#include "Position.h"
#include "Point.h"

#include <iostream>
#include <vector>
#include <list>
#include <map>

class Pathfinder
{
public:

	Pathfinder();

	void addPoint(int x, int y, bool walkable);
	void displayPath(std::vector<Position*> path);
	std::vector<Position*> aStar(float x1, float y1, float x2, float y2);

private:

	
	

	Point* getPoint(int x, int y);
	

	bool pointExists(int x, int y);
	bool pointIsWalkable(int x, int y);

	

	std::map<int, std::map<int, Point*> > grid;
};