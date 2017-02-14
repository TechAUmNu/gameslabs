#include <iostream>
#include <vector>
#include <random>
using namespace std;

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GLM/glm.hpp>
#include <GLM/gtx/transform.hpp>

#include "graphics.h"
#include "shapes.h"
#include "../PhysicsLibrary/SphereCollider.h"


// FUNCTIONS
void render(double currentTime);
void update(double currentTime);
void startup();
void onResizeCallback(GLFWwindow* window, int w, int h);
void onKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

// VARIABLES
bool		running = true;

Graphics	myGraphics;		// Runing all the graphics in this object

/* Spheres for rendering */
Sphere		mysphere;
Sphere		mySphere2;

/* Create materials and physics object for each ball */
Material materialRubber(0.8f, 0.6f, 0.98f);
Material materialSteel(0.4f, 0.1f, 0.6f);
SphereCollider sphere(vec3(-2.0f, 8.0f, -20.0f), vec3::zero(), vec3::zero(), materialRubber, 0.01f, true, 1.0f, 2.0f);
SphereCollider sphere2(vec3(2.0f, 8.0f, -20.0f), vec3::zero(), vec3::zero(), materialSteel, 0.02f, true, 1.0f, 2.0f);

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
	
	mysphere.Load();
	mysphere.fillColor = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);	// You can change the shape fill colour, line colour or linewidth 
	
	mySphere2.Load();
	mySphere2.fillColor = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);	// You can change the shape fill colour, line colour or linewidth 
	
	myGraphics.SetOptimisations();		// Cull and depth testing

}

void update(double deltaTime) {	

	// Calculate physics for bouncing balls
	sphere.update(deltaTime);
	sphere2.update(deltaTime);	

}

void render(double deltaTime) {

	// Clear viewport - start a new frame.
	myGraphics.ClearViewport();
	
	/* Update model_view matrix for each ball */
	glm::mat4 mv_matrix_sphere =
		glm::translate(glm::vec3(sphere.position.x, sphere.position.y, sphere.position.z)) *
		glm::scale(glm::vec3(sphere.radius, sphere.radius, sphere.radius)) *
		glm::mat4(1.0f);

	mysphere.mv_matrix = mv_matrix_sphere;
	mysphere.proj_matrix = myGraphics.proj_matrix;

	glm::mat4 mv_matrix_sphere2 =
		glm::translate(glm::vec3(sphere2.position.x, sphere2.position.y, sphere2.position.z)) *
		glm::scale(glm::vec3(sphere2.radius, sphere2.radius, sphere2.radius)) *
		glm::mat4(1.0f);

	mySphere2.mv_matrix = mv_matrix_sphere2;
	mySphere2.proj_matrix = myGraphics.proj_matrix;

	mysphere.Draw();
	mySphere2.Draw();

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
	
	/* Reset the balls to their original positions */
	if (key == GLFW_KEY_R && action == GLFW_PRESS) {
		sphere.position = vec3(-2.0f, 10.0f, -20.0f);
		sphere.velocity = vec3::zero();
		sphere.isKinematic = false;

		sphere2.position = vec3(2.0f, 10.0f, -20.0f);
		sphere2.velocity = vec3::zero();
		sphere2.isKinematic = false;
	}

	/* Apply an impulse to the balls */
	if (key == GLFW_KEY_I && action == GLFW_PRESS) {
		sphere.isKinematic = false;
		sphere2.isKinematic = false;

		sphere.applyImpulse(vec3(50.0f, 30.0f, 0.0f), 1);
		sphere2.applyImpulse(vec3(50.0f, 30.0f, 0.0f), 1);
	}	
}