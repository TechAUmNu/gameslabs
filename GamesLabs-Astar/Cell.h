#pragma once

class Cell{
public:

	Cell(int x, int y, int g, int h, int f, bool walkable, int parentX, int parentY);


	int x, y, g, h, f, parentX, parentY;
	bool walkable;

	
protected:	

};