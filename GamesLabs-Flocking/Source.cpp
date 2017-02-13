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

#include "Boid.h"

extern "C"
{
	__declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
}
// FUNCTIONS
void render(double currentTime);
void update(double currentTime);
void startup();
void onResizeCallback(GLFWwindow* window, int w, int h);
void onKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

// VARIABLES
bool		running = true;

Graphics	myGraphics;		// Runing all the graphics in this object

Arrow		arrow;
Sphere		sphere;

const int numberOfBoids = 10;
Boid boids[numberOfBoids];


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
	
	// Calculate proj_matrix for the first time.
	myGraphics.aspect = (float)myGraphics.windowWidth / (float)myGraphics.windowHeight;
	myGraphics.proj_matrix = glm::perspective(glm::radians(50.0f), myGraphics.aspect, 0.1f, 1000.0f);

	// Load Geometry

	sphere.Load();
	sphere.fillColor = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);	// You can change the shape fill colour, line colour or linewidth 

	arrow.Load();
	arrow.fillColor = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f); arrow.lineColor = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
	
	myGraphics.SetOptimisations();		// Cull and depth testing


}

void update(double deltaTime) {
		

	for (int i = 0; i < numberOfBoids; i++) {
		boids[i].update(deltaTime, boids, numberOfBoids);
	}

	//Calculate Arrows translations (note: arrow model points up)
	
		
	


	
	
}

void render(double deltaTime) {
	// Clear viewport - start a new frame.
	myGraphics.ClearViewport();
		

	for (int i = 0; i < numberOfBoids; i++) {
		glm::mat4 mv_matrix =
			glm::translate(glm::vec3(boids[i].position.x, boids[i].position.y, boids[i].position.z)) *
			glm::scale(glm::vec3(boids[i].mass, boids[i].mass, boids[i].mass)) *
			glm::mat4(1.0f);

		sphere.mv_matrix = mv_matrix;
		sphere.proj_matrix = myGraphics.proj_matrix;

		sphere.Draw();
	}
	
	
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