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

	void addStaticObject(int x, int y, bool walkable);

	std::vector<Position*> getPath(float x1, float y1, float x2, float y2, float s);
	std::vector<Position*> aStar(float x1, float y1, float x2, float y2);

private:

	
	std::list<Point*> getTraversingPoints(float x1, float y1, float x2, float y2);

	Point* getPoint(int x, int y);
	Point* getPointFromCoord(float x, float y);

	bool pointExists(int x, int y);
	bool pointIsWalkable(int x, int y);

	

	std::map<int, std::map<int, Point*> > grid;
};