// Simplified Renderer application for GP course
// Code is similar to the one in lab 1 but all the graphics sections were refactored into the Graphics Class.
// Extra improvements:
// Reduced OpenGL version from 4.5 to 3.3 to allow it to render in older laptops.
// Added Shapes library for rendering cubes, spheres and vectors.
// Added examples of matrix multiplication on Update.
// Added resize screen and keyboard callbacks.
// 
// Suggestions or extra help please do email me S.Padilla@hw.ac.uk
//
// Note: Do not forget to link the libraries correctly and add the GLEW DLL in your debug/release folder.

#include <iostream>
#include <vector>
using namespace std;

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GLM/glm.hpp>
#include <GLM/gtx/transform.hpp>

#include "graphics.h"
#include "shapes.h"

#include "Pathfinder.h"


// FUNCTIONS
void render(double currentTime);
void update(double currentTime);
void startup();
void onResizeCallback(GLFWwindow* window, int w, int h);
void onKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

// VARIABL
bool		running = true;

Graphics	myGraphics;		// Runing all the graphics in this object

Pathfinder pathfinder;
Sphere		sphere;


float t = 0.001f;			// Global variable for animation
float deltaTime = 0.0f;


int main()
{
	
	int errorGraphics = myGraphics.Init();		// Launch window and graphics context
	if (errorGraphics) return 0;				//Close if something went wrong...

	startup();									// Setup all necessary information for startup (aka. load texture, shaders, models, etc).
	
	// Mixed graphics and update functions - declared in main for simplicity.
	glfwSetWindowSizeCallback(myGraphics.window, onResizeCallback);			// Set callback for resize
	glfwSetKeyCallback(myGraphics.window, onKeyCallback);					// Set Callback for keys

	
	double currentTime = 0;
	// MAIN LOOP run until the window is closed
	do {										
		currentTime = glfwGetTime();		// retrieve timelapse		
		
		glfwPollEvents();						// poll callbacks
		update(deltaTime);					// update (physics, animation, structures, etc)
		render(deltaTime);					// call render function.

		glfwSwapBuffers(myGraphics.window);		// swap buffers (avoid flickering and tearing)

		running &= (glfwGetKey(myGraphics.window, GLFW_KEY_ESCAPE) == GLFW_RELEASE);	// exit if escape key pressed
		running &= (glfwWindowShouldClose(myGraphics.window) != GL_TRUE);
		deltaTime = glfwGetTime() - currentTime;
		
	} while (running);

	myGraphics.endProgram();			// Close and clean everything up...

	cout << "\nPress any key to continue...\n";
	cin.ignore(); cin.get(); // delay closing console to read debugging errors.

	return 0;
}

void startup() {
	
	//pathfinder.addStaticObject()
	for (int x = 0; x < 10; x++) {
		for (int y = 0; y < 10; y++) {
			pathfinder.addStaticObject(x, y, true);
		}
	}
	pathfinder.addStaticObject(2, 0, false);
	pathfinder.addStaticObject(2, 1, false);
	pathfinder.addStaticObject(2, 2, false);
	pathfinder.addStaticObject(2, 3, false);
	pathfinder.addStaticObject(2, 4, false);
	pathfinder.addStaticObject(2, 5, false);
	pathfinder.addStaticObject(2, 6, false);
	

	vector<Position*> path = pathfinder.aStar(0, 0, 6, 6);
	for (int i = 0; i < path.size(); i++) {
		cout << "(" << path[i]->getGridX() << "," << path[i]->getGridY() << ")" << endl;
	}

}

void update(double deltaTime) {
		

	
	
	
		
	


	
	
}

void render(double deltaTime) {
	// Clear viewport - start a new frame.
	myGraphics.ClearViewport();
		

	
	
}

void onResizeCallback(GLFWwindow* window, int w, int h) {	// call everytime the window is resized
	myGraphics.windowWidth = w;
	myGraphics.windowHeight = h;

	myGraphics.aspect = (float)w / (float)h;
	myGraphics.proj_matrix = glm::perspective(glm::radians(50.0f), myGraphics.aspect, 0.1f, 1000.0f);
}

void onKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) { // called everytime a key is pressed
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	
	

}