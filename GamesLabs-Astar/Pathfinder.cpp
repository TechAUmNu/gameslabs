#include "Pathfinder.h"

using namespace std;

Pathfinder::Pathfinder()
{
}

void Pathfinder::addPoint(int x, int y, bool walkable)
{	
	if (!pointExists(x, y))
	{
		grid[x][y] = new Point(x, y, walkable);
	}
	else if (!walkable)
	{
		grid[x][y]->walkable = false;
	}
}




vector<Position*> Pathfinder::aStar(float x1, float y1, float x2, float y2)
{
	vector<Position*> path;

	// Define points to work with
	Point *start = grid[x1][y1];
	Point *end = grid[x2][y2];
	Point *current = NULL;
	Point *child;

	// Define the open and the close list
	list<Point*> openList;
	list<Point*> closedList;
	list<Point*>::iterator i;

	unsigned int n = 0;

	// Add the start point to the openList
	openList.push_back(start);
	start->opened = true;

	while (n == 0 || (current != end && n < 30))
	{
		// Look for the smallest F value in the openList and make it the current point
		for (i = openList.begin(); i != openList.end(); ++i)
		{
			if (i == openList.begin() || (*i)->getFScore() <= current->getFScore())
			{
				current = (*i);
			}
		}

		// Stop if we reached the end
		if (current == end)
		{
			break;
		}

		// Remove the current point from the openList
		openList.remove(current);
		current->opened = false;

		// Add the current point to the closedList
		closedList.push_back(current);
		current->closed = true;

		// Get all current's adjacent walkable points
		for (int x = -1; x < 2; x++)
		{
			for (int y = -1; y < 2; y++)
			{
				// If it's current point then pass
				if (x == 0 && y == 0)
				{
					continue;
				}

				// Get this point	
				child = getPoint(current->position.x + x, current->position.y + y);
				

				// If it's closed or not walkable then pass
				if (child->closed || !child->walkable)
				{
					continue;
				}

				// If we are at a corner
				if (x != 0 && y != 0)
				{
					// if the next horizontal point is not walkable or in the closed list then pass
					if (!pointIsWalkable(current->position.x, current->position.y + y) || getPoint(x,y)->closed)
					{
						continue;
					}
					// if the next vertical point is not walkable or in the closed list then pass
					if (!pointIsWalkable(current->position.x + x, current->position.y) || getPoint(x, y)->closed)
					{
						continue;
					}
				}

				// If it's already in the openList
				if (child->opened)
				{
					// If it has a wroste g score than the one that pass through the current point
					// then its path is improved when it's parent is the current point
					if (child->getGScore() > child->getGScore(current))
					{
						// Change its parent and g score
						child->setParent(current);
						child->computeScores(end);
					}
				}
				else
				{
					// Add it to the openList with current point as parent
					openList.push_back(child);
					child->opened = true;

					// Compute it's g, h and f score
					child->setParent(current);
					child->computeScores(end);
				}
			}
		}

		n++;
	}

	// Reset
	for (i = openList.begin(); i != openList.end(); ++i)
	{
		(*i)->opened = false;
	}
	for (i = closedList.begin(); i != closedList.end(); ++i)
	{
		(*i)->closed = false;
	}

	// Resolve the path starting from the end point
	while (current->hasParent() && current != start)
	{
		path.push_back(&current->position);
		current = current->parent;
		if (current == start) {
			path.push_back(&current->position);
		}
		n++;
	}

	return path;
}


Point* Pathfinder::getPoint(int x, int y)
{
	if (pointExists(x, y))
	{
		return grid[x][y];
	}
	else
	{
		//cout << "ERROR: failed to gather point " << x << "x" << y << " on grid" << endl;
		return new Point(0, 0, false);
	}
}


bool Pathfinder::pointExists(int x, int y)
{
	return (grid.count(x) != 0 && grid[x].count(y) != 0);
}

bool Pathfinder::pointIsWalkable(int x, int y)
{
	return (pointExists(x, y) && grid[x][y]->walkable);
}

void Pathfinder::displayPath(vector<Position*> path) {
	for (int y = 0; y < 9; y++) 
	{
		for (int x = 0; x < 9; x++)    
		{
			
			if (grid[x][y]->walkable) {
				bool filled = false;
				for (int i = 0; i < path.size(); i++) {
					if (path[i]->x == grid[x][y]->position.x && path[i]->y == grid[x][y]->position.y) {
						cout << "P" << "  ";
						filled = true;
						break;
					}
				}
				if (!filled) {					
					cout << "." << "  ";					
				}
			}
			else {
				cout << "X" << "  ";
			}
		}
		cout << endl;
	}
}


