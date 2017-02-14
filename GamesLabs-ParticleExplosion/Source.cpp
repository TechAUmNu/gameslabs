#include <iostream>
#include <vector>
using namespace std;

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GLM/glm.hpp>
#include <GLM/gtx/transform.hpp>

#include "graphics.h"
#include "shapes.h"
#include "../PhysicsLibrary/SphereCollider.h"
#include "ParticleEmitter.h"

// FUNCTIONS
void render(double currentTime);
void update(double currentTime);
void startup();
void onResizeCallback(GLFWwindow* window, int w, int h);
void onKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

// VARIABLES
bool		running = true;

Graphics	myGraphics;		// Runing all the graphics in this object


Sphere		mySphere;



ParticleEmitter particleEmitter(vec3(0.0f, 2.0f, -20.0f), vec3(0,0,0), std::pair<vec4, vec4>(vec4(1.0f, 0.0f, 0.0f, 1.0f), vec4(1.0f, 1.0f, 0.0f, 1.0f)),std::pair<float, float>(0.001f, 0.03f), std::pair<float, float>(2.0f, 3.0f), 0, std::pair<vec3, vec3>(vec3(-20.0f, -20.0f, -20.0f), vec3(20.0f, 20.0f, 20.0f)),false, std::pair<float, float>(0.01f, 0.2f));


float t = 0.001f;			// Global variable for animation
float deltaTime = 0.0f;


int main()
{
	particleEmitter.emit(1000);
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

	
	
	mySphere.Load();
	mySphere.fillColor = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);	// You can change the shape fill colour, line colour or linewidth 
	
	myGraphics.SetOptimisations();		// Cull and depth testing


}

void update(double deltaTime) {
	
	particleEmitter.update(deltaTime);
	
}

void render(double deltaTime) {
	// Clear viewport - start a new frame.
	myGraphics.ClearViewport();

	// Draw
	
	for(int i = 0; i < particleEmitter.particles.size(); i++){
		glm::mat4 mv_matrix_sphere =
			glm::translate(glm::vec3(particleEmitter.particles[i].position.x, particleEmitter.particles[i].position.y, particleEmitter.particles[i].position.z)) *
			glm::scale(glm::vec3(particleEmitter.particles[i].mass, particleEmitter.particles[i].mass, particleEmitter.particles[i].mass)) *
			glm::mat4(1.0f);

		mySphere.mv_matrix = mv_matrix_sphere;
		mySphere.proj_matrix = myGraphics.proj_matrix;

		mySphere.fillColor = particleEmitter.particles[i].colour.toGlmVec4();
		mySphere.lineColor = particleEmitter.particles[i].colour.toGlmVec4();


		mySphere.Draw();
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