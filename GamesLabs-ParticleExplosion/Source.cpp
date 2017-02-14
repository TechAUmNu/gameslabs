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

//Cube		myCube;
Sphere		mySphere;
//Sphere		mySphere2;
//Arrow		arrowX;
//Arrow		arrowY;
//Arrow		arrowZ;


//Material materialRubber(0.8f, 0.6f, 0.98f);
//Material materialSteel(0.4f, 0.1f, 0.5f);
//SphereCollider sphere(vec3(-2.0f, 8.0f, -20.0f), vec3::zero(), vec3::zero(), materialRubber, 0.001f, true, 1.0f, 2.0f);
//SphereCollider sphere2(vec3(2.0f, 8.0f, -20.0f), vec3::zero(), vec3::zero(), materialSteel, 0.2f, true, 1.0f, 2.0f);
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

	// Load Geometry
	//myCube.Load();
	
	mySphere.Load();
	mySphere.fillColor = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);	// You can change the shape fill colour, line colour or linewidth 
	
	//mySphere2.Load();
	//mySphere2.fillColor = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);	// You can change the shape fill colour, line colour or linewidth 



	//arrowX.Load(); arrowY.Load(); arrowZ.Load();
	//arrowX.fillColor = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f); arrowX.lineColor = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
	//arrowY.fillColor = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f); arrowY.lineColor = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
	//arrowZ.fillColor = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f); arrowZ.lineColor = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);

	myGraphics.SetOptimisations();		// Cull and depth testing


}

void update(double deltaTime) {
	//sphere.update(deltaTime);
	//particleEmitter.position = sphere.position;
	particleEmitter.update(deltaTime);
	

	
	//sphere2.update(deltaTime);
	// calculate Sphere movement
	

	/*glm::mat4 mv_matrix_sphere2 =
		glm::translate(glm::vec3(sphere2.position.x, sphere2.position.y, sphere2.position.z)) *
		glm::scale(glm::vec3(sphere2.radius, sphere2.radius, sphere2.radius)) *
		glm::mat4(1.0f);

	mySphere2.mv_matrix = mv_matrix_sphere2;
	mySphere2.proj_matrix = myGraphics.proj_matrix;
	*/
	//Calculate Arrows translations (note: arrow model points up)
	/*glm::mat4 mv_matrix_x =
		glm::translate(glm::vec3(0.0f, 0.0f, -6.0f)) *
		glm::rotate(glm::radians(-90.0f), glm::vec3(0.0f, 0.0f, 1.0f)) *
		glm::scale(glm::vec3(0.2f, 0.5f, 0.2f)) *
		glm::mat4(1.0f);
	arrowX.mv_matrix = mv_matrix_x; 
	arrowX.proj_matrix = myGraphics.proj_matrix;

	glm::mat4 mv_matrix_y =
		glm::translate(glm::vec3(0.0f, 0.0f, -6.0f)) *
		//glm::rotate(glm::radians(-90.0f), glm::vec3(0.0f, 0.0f, 1.0f)) *	// already model pointing up
		glm::scale(glm::vec3(0.2f, 0.5f, 0.2f)) *
		glm::mat4(1.0f);
	arrowY.mv_matrix = mv_matrix_y;
	arrowY.proj_matrix = myGraphics.proj_matrix;

	glm::mat4 mv_matrix_z =
		glm::translate(glm::vec3(0.0f, 0.0f, -6.0f)) *
		glm::rotate(glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f)) *
		glm::scale(glm::vec3(0.2f, 0.5f, 0.2f)) *
		glm::mat4(1.0f);	
	arrowZ.mv_matrix = mv_matrix_z;
	arrowZ.proj_matrix = myGraphics.proj_matrix;
	*/
	t += 0.01f; // increment movement variable
}

void render(double deltaTime) {
	// Clear viewport - start a new frame.
	myGraphics.ClearViewport();

	// Draw
	//myCube.Draw();
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
/*
	glm::mat4 mv_matrix_sphere =
		glm::translate(glm::vec3(sphere.position.x, sphere.position.y, sphere.position.z)) *
		glm::scale(glm::vec3(sphere.mass, sphere.mass, sphere.mass)) *
		glm::mat4(1.0f);

	mySphere.mv_matrix = mv_matrix_sphere;
	mySphere.proj_matrix = myGraphics.proj_matrix;

	mySphere.fillColor = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
	mySphere.lineColor = glm::vec4(0.5f, 1.0f, 0.5f, 1.0f);

	
	mySphere.Draw();
	*/
	//mySphere2.Draw();
	
	//arrowX.Draw(); 
	//arrowY.Draw(); 
	//arrowZ.Draw();
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
	/*if (key == GLFW_KEY_R && action == GLFW_PRESS) {
		sphere.position = vec3(-2.0f, 10.0f, -20.0f);
		sphere.velocity = vec3::zero();
		sphere.isKinematic = false;

		//sphere2.position = vec3(2.0f, 10.0f, -20.0f);
		//sphere2.velocity = vec3::zero();
		//sphere2.isKinematic = false;
	}
	if (key == GLFW_KEY_I && action == GLFW_PRESS) {
		sphere.isKinematic = false;
		//sphere2.isKinematic = false;

		sphere.applyImpulse(vec3(50.0f, 30.0f, 0.0f), 1);
		//sphere2.applyImpulse(vec3(50.0f, 30.0f, 0.0f), 1);
		

	}
	*/
	
	//if (key == GLFW_KEY_LEFT) angleY += 0.05f;
}