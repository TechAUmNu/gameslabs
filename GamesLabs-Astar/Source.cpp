#include <iostream>
#include <vector>
using namespace std;

#include "Pathfinder.h"
#include <random>

Pathfinder pathfinder;

int main()
{
	
	std::default_random_engine engine;
	engine.seed(std::random_device{}());

	/* 30% probability of a wall */
	std::bernoulli_distribution walkable(0.7); 
	
	/* Create a random grid*/
	int sizeX = 20;
	int sizeY = 20;
	for (int x = 0; x < sizeX; x++) {
		for (int y = 0; y < sizeY; y++) {
			pathfinder.addPoint(x, y, walkable(engine));
		}
	}

	/* Blank path to allow display of grid */
	vector<Position*> blankPath;

	/* Loop till a valid path is found*/
	while (true) {
		/* Display the grid */
		pathfinder.displayPath(blankPath, sizeX, sizeY);

		
		int x, y, x1, y1;

		/* Loop till valid start position is entered */
		while (true) {
			cout << "Enter Start Position: " << endl;
			cin >> x >> y;

			if (pathfinder.pointIsWalkable(x, y)) {				
				break;
			}
			else {
				cout << "Start Position not valid!" << endl;
			}
		}
	
		/* Loop till valid end position is entered */
		while (true) {
			cout << "Enter End Position: " << endl;
			cin >> x1 >> y1;

			if (pathfinder.pointIsWalkable(x1, y1)) {				
				break;
			}
			else {
				cout << "End Position not valid!" << endl;
			}
		}

		/* Find the path between the points */
		vector<Position*> path = pathfinder.aStar(x, y, x1, y1);
		
		/* If a path was found */
		if (path.size() != 0) {
			/* Print the points of the path */

			cout << "Path: " << endl;
			for (int i = 0; i < path.size(); i++) {
				cout << "(" << path[i]->x << "," << path[i]->y << ")" ;
			}
			cout << endl;
			/* Display the grid with the path */
			pathfinder.displayPath(path, sizeX, sizeY);
			break;
		}else{
			cout << "No path between points!" << endl;
		}
	}

	/* delay closing console to read debugging errors. */
	cout << "\nPress any key to continue...\n";
	cin.ignore(); cin.get();

	return 0;
}
