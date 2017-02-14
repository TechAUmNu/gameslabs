#include <iostream>
#include <vector>
using namespace std;
#include <chrono>
#include <thread>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GLM/glm.hpp>
#include <GLM/gtx/transform.hpp>
#include <GLM/gtx/rotate_vector.hpp>

#include "graphics.h"
#include "shapes.h"

#include "Boid.h"
#include <random>


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

const int numberOfBoids = 100;
Boid *boids[numberOfBoids];

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

	/* Cleanup the boids */
	for (int i = 0; i < numberOfBoids; i++) {
		delete boids[i];
	}

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
	arrow.Load();	
	
	myGraphics.SetOptimisations();		// Cull and depth testing

	/* Randomize boids positions and velocities */
	std::default_random_engine engine;
	engine.seed(std::random_device{}());
	std::uniform_real_distribution<float> positionXYGenerator(-5.0f, 5.0f);
	std::uniform_real_distribution<float> positionZGenerator(-100.0f, -30.0f);
	std::uniform_real_distribution<float> velocityGenerator(-100.0f, 100.0f);

	for (int i = 0; i < numberOfBoids; i++) {
		boids[i] = new Boid(vec3(positionXYGenerator(engine), positionXYGenerator(engine), positionZGenerator(engine)));		
		boids[i]->velocity = vec3(velocityGenerator(engine), velocityGenerator(engine), velocityGenerator(engine));
		boids[i]->colour = vec4::random(std::pair<vec3,vec3>(vec3(0.0f, 0.0f, 0.0f), vec3(1.0f, 1.0f, 1.0f)));
	}

}

void update(double deltaTime) {
	/* Update position of boids */
	for (int i = 0; i < numberOfBoids; i++) {
		boids[i]->update(deltaTime, boids, numberOfBoids);
	}
}

void render(double deltaTime) {
	/* Clear viewport - start a new frame. */
	myGraphics.ClearViewport();		
	
	glm::vec4 colour;
	vec3 direction;
	glm::mat4 mv_matrix;

	/* Render the boids using arrows */
	for (int i = 0; i < numberOfBoids; i++) {
		
		/* Normalize velocity to get a direction vector */
		direction = boids[i]->velocity.normalize(1);

		/* Calculate model_view matrix */
		mv_matrix =
			glm::translate(glm::vec3(boids[i]->position.x, boids[i]->position.y, boids[i]->position.z)) *
			glm::orientation(glm::vec3(direction.x, direction.y, direction.z), glm::vec3(vec3::up().x, vec3::up().y, vec3::up().z)) *
			glm::scale(glm::vec3(boids[i]->mass, boids[i]->mass, boids[i]->mass)) *
			glm::mat4(1.0f);
		
		/* Set the colour of the boid */
		colour = boids[i]->colour.toGlmVec4();
		arrow.fillColor = colour; arrow.lineColor = colour;
		
		arrow.mv_matrix = mv_matrix;
		arrow.proj_matrix = myGraphics.proj_matrix;

		arrow.Draw();
	}
	
	
}

/* Called when the window is resized */
void onResizeCallback(GLFWwindow* window, int w, int h) {	
	myGraphics.windowWidth = w;
	myGraphics.windowHeight = h;

	myGraphics.aspect = (float)w / (float)h;
	myGraphics.proj_matrix = glm::perspective(glm::radians(50.0f), myGraphics.aspect, 0.1f, 1000.0f);
}

/* Called when a key is pressed */
void onKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) { 
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}