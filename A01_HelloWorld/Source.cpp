/*	Veronica Lesnar
HW 01 - Hello World!
Source.cpp - TODO */
#include "ShaderHelpers.h"
#include "Shape.h"
#include "Entity.h"
#include <glfw3.h>
#include <math.h>

using namespace::std;

// Global variables
GLuint program; // The index of the shader program
ShaderHelpers sh; // Allows the use of the ShaderHelpers class
int prevTime; // Holds the last time calculated
int width; // Holds the width in the GetWindowSize method
int height;  // Holds the height in the GetWindowSize method

Shape* square; // Square
GLfloat squareVerts[] = // Square vertices
{
	-0.25f, -0.25f, 1.0f, 1.0f, 1.0f, // Bottom-left pt
	-0.25f, 0.25f, 1.0f, 1.0f, 1.0f, // Top-left pt
	0.25f, 0.25f, 1.0f, 1.0f, 1.0f, // Top-right pt

	-0.25f, -0.25f, 1.0f, 1.0f, 1.0f, // Bottom-left pt
	0.25f, -0.25f, 1.0f, 1.0f, 1.0f, // Bottom-right pt
	0.25f, 0.25f, 1.0f, 1.0f, 1.0f // Top-right pt
};

Shape* isoTriangle; // Isoceles triangle
GLfloat isoTriangleVerts[] = // Isoceles triangle vertices
{
	-0.25f, 0.0f, 1.0f, 1.0f, 1.0f, // Bottom-left pt
	0.25f, 0.0f, 1.0f, 1.0f, 1.0f, // Bottom-right pt
	0.0, 0.5f, 1.0f, 1.0f, 1.0f, // Top pt
};

Shape* sun; // Sun shape
GLfloat sunVerts[] = // Sun vertices
{
	// Main body
	0.0f, -0.25f, 1.0f, 1.0f, 1.0f, // Bottom pt
	0.25f, 0.0f, 1.0f, 1.0f, 1.0f, // Right pt
	0.0f, 0.25f, 1.0f, 1.0f, 1.0f, // Top pt
	0.0f, -0.25f, 1.0f, 1.0f, 1.0f, // Bottom pt
	0.0f, 0.25f, 1.0f, 1.0f, 1.0f, // Top pt
	-0.25f, 0.0f, 1.0f, 1.0f, 1.0f, // Left pt

									// Top right sun
	0.04f, 0.27f, 1.0f, 1.0f, 1.0f, // Top left pt
	0.2f, 0.35f, 1.0f, 1.0f, 1.0f, // Top right pt
	0.14f, 0.17f, 1.0f, 1.0f, 1.0f, // Bottom pt

	0.17f, 0.14f, 1.0f, 1.0f, 1.0f, // Top left pt
	0.33f, 0.23f, 1.0f, 1.0f, 1.0f, // Top right pt
	0.27f, 0.04f, 1.0f, 1.0f, 1.0f, // Bottom pt

									// Bottom right sun
	0.04f, -0.27f, 1.0f, 1.0f, 1.0f, // Top left pt
	0.2f, -0.35f, 1.0f, 1.0f, 1.0f, // Top right pt
	0.14f, -0.17f, 1.0f, 1.0f, 1.0f, // Bottom pt

	0.17f, -0.14f, 1.0f, 1.0f, 1.0f, // Top left pt
	0.33f, -0.23f, 1.0f, 1.0f, 1.0f, // Top right pt
	0.27f, -0.04f, 1.0f, 1.0f, 1.0f, // Bottom pt

									 // Top left sun
	-0.04f, 0.27f, 1.0f, 1.0f, 1.0f, // Top left pt
	-0.2f, 0.35f, 1.0f, 1.0f, 1.0f, // Top right pt
	-0.14f, 0.17f, 1.0f, 1.0f, 1.0f, // Bottom pt

	-0.17f, 0.14f, 1.0f, 1.0f, 1.0f, // Top left pt
	-0.33f, 0.23f, 1.0f, 1.0f, 1.0f, // Top right pt
	-0.27f, 0.04f, 1.0f, 1.0f, 1.0f, // Bottom pt

									 // Bottom left sun
	-0.04f, -0.27f, 1.0f, 1.0f, 1.0f, // Top left pt
	-0.2f, -0.35f, 1.0f, 1.0f, 1.0f, // Top right pt
	-0.14f, -0.17f, 1.0f, 1.0f, 1.0f, // Bottom pt

	-0.17f, -0.14f, 1.0f, 1.0f, 1.0f, // Top left pt
	-0.33f, -0.23f, 1.0f, 1.0f, 1.0f, // Top right pt
	-0.27f, -0.04f, 1.0f, 1.0f, 1.0f, // Bottom pt
};

Entity* sunEnt; // Entity for the sun

static void cursorPosCallback(GLFWwindow* window, double xpos, double ypos); // Callback function for cursor entering the window

																			 // init Method - Initializes the ShaderHelpers class to set up the shaders
void init() {
	// Loads the shaders using the ShaderHelpers class
	program = sh.loadShaderProgram("Shaders/vertexShader.glsl", "Shaders/fragmentShader.glsl");

	// Checks to make sure the programs loaded correctly
	if (program != 0) {
		glUseProgram(program);
	}

	// Sets the background color to a sky blue
	glClearColor((GLclampf)0.678, (GLclampf)0.847, (GLclampf)0.902, (GLclampf)1);

	// Creates the shapes to be used
	square = new Shape(squareVerts, (GLsizei)6, program);
	isoTriangle = new Shape(isoTriangleVerts, (GLsizei)3, program);
	sun = new Shape(sunVerts, (GLsizei)30, program);

	// Create the sun entity
	sunEnt = new Entity(sun);

	// Sets prevTime to 0
	prevTime = 0;
	glEnable(GL_DEPTH);
}

// update Method - Updates the time for animation
void update() {
	// Calculate time between calls for animation
	int currentTime = (int)glfwGetTime() * 1000;
	int deltaTime = currentTime - prevTime;
	prevTime = currentTime;
}

// draw Method - Draws all shapes to the screen
void draw() {
	// Clears the color buffer before use
	glClear(GL_COLOR_BUFFER_BIT);

	// Draw the globe
	sh.setShaderColor(program, "color", 1.0f, 0.843f, 0.0f); // Gold
	sun->Draw(sun->position.x, sun->position.y, 0.5f, 0.5f);
	sunEnt->shine();
	if (sun->position.y < -0.45) {
		glClearColor((GLclampf)0.0, (GLclampf)0.0, (GLclampf)0.5, (GLclampf)1);
	}
	else {
		glClearColor((GLclampf)0.678, (GLclampf)0.847, (GLclampf)0.902, (GLclampf)1);
	}

	// Draw the ground
	sh.setShaderColor(program, "color", 0.239f, 0.569f, 0.251f); // Cobaltgreen
	square->Draw(0.0f, -0.7f, 4.0f, 1.5f);

	// Draw Hello World!
	sh.setShaderColor(program, "color", 1.0f, 1.0f, 1.0f); // White
														   // H
	square->Draw(-0.97f, -0.175f, 0.08f, 0.6f);
	square->Draw(-0.895f, -0.15f, 0.25f, 0.1f);
	square->Draw(-0.85f, -0.175f, 0.08f, 0.6f);
	// E
	square->Draw(-0.77f, -0.175f, 0.08f, 0.6f);
	square->Draw(-0.725f, -0.3f, 0.25f, 0.1f);
	square->Draw(-0.725f, -0.15f, 0.25f, 0.1f);
	square->Draw(-0.725f, -0.05f, 0.25f, 0.1f);
	// L
	square->Draw(-0.6f, -0.175f, 0.08f, 0.6f);
	square->Draw(-0.55f, -0.3f, 0.25f, 0.1f);
	// L
	square->Draw(-0.425f, -0.175f, 0.08f, 0.6f);
	square->Draw(-0.38f, -0.3f, 0.25f, 0.1f);
	// O
	square->Draw(-0.26f, -0.175f, 0.08f, 0.5f);
	square->Draw(-0.205f, -0.05f, 0.2f, 0.1f);
	square->Draw(-0.15f, -0.175f, 0.08f, 0.5f);
	square->Draw(-0.205f, -0.3f, 0.2f, 0.1f);

	// W
	square->Draw(0.07f, -0.175f, 0.08f, 0.6f);
	square->Draw(0.1f, -0.3f, 0.2f, 0.1f);
	square->Draw(0.15f, -0.225f, 0.08f, 0.4f);
	square->Draw(0.17f, -0.3f, 0.2f, 0.1f);
	square->Draw(0.23f, -0.175f, 0.08f, 0.6f);
	// O
	square->Draw(0.31f, -0.175f, 0.08f, 0.5f);
	square->Draw(0.365f, -0.05f, 0.2f, 0.1f);
	square->Draw(0.42f, -0.175f, 0.08f, 0.5f);
	square->Draw(0.368f, -0.3f, 0.2f, 0.1f);
	// R
	square->Draw(0.5f, -0.175f, 0.08f, 0.6f);
	square->Draw(0.545f, -0.05f, 0.2f, 0.1f);
	square->Draw(0.6f, -0.105f, 0.08f, 0.2f);
	square->Draw(0.55f, -0.17f, 0.2f, 0.1f);
	square->Draw(0.6f, -0.255f, 0.08f, 0.27f);
	// L
	square->Draw(0.68f, -0.175f, 0.08f, 0.6f);
	square->Draw(0.73f, -0.3f, 0.25f, 0.1f);
	// D
	square->Draw(0.85f, -0.175f, 0.08f, 0.6f);
	square->Draw(0.9f, -0.05f, 0.25f, 0.1f);
	square->Draw(0.97f, -0.175f, 0.08f, 0.5f);
	square->Draw(0.9f, -0.3f, 0.25f, 0.1f);

	// Draw the grass
	sh.setShaderColor(program, "color", 0.239f, 0.569f, 0.251f); // Cobaltgreen
	isoTriangle->Draw(-1.0f, -0.35f, 0.05f, 0.15f);
	isoTriangle->Draw(-0.95f, -0.35f, 0.05f, 0.15f);
	isoTriangle->Draw(-0.97f, -0.35f, 0.05f, 0.15f);
	isoTriangle->Draw(-0.93f, -0.35f, 0.05f, 0.15f);
	isoTriangle->Draw(-0.75f, -0.35f, 0.05f, 0.15f);
	isoTriangle->Draw(-0.73f, -0.35f, 0.05f, 0.15f);
	isoTriangle->Draw(-0.55f, -0.35f, 0.05f, 0.15f);
	isoTriangle->Draw(-0.53f, -0.35f, 0.05f, 0.15f);
	isoTriangle->Draw(-0.26f, -0.35f, 0.05f, 0.15f);
	isoTriangle->Draw(-0.28f, -0.35f, 0.05f, 0.15f);
	isoTriangle->Draw(-0.24f, -0.35f, 0.05f, 0.15f);
	isoTriangle->Draw(-0.11f, -0.35f, 0.05f, 0.15f);
	isoTriangle->Draw(0.0f, -0.35f, 0.05f, 0.15f);
	isoTriangle->Draw(0.1f, -0.35f, 0.05f, 0.15f);
	isoTriangle->Draw(0.3f, -0.35f, 0.05f, 0.15f);
	isoTriangle->Draw(0.5f, -0.35f, 0.05f, 0.15f);
	isoTriangle->Draw(0.6f, -0.35f, 0.05f, 0.15f);
	isoTriangle->Draw(0.34f, -0.35f, 0.05f, 0.15f);
	isoTriangle->Draw(0.36f, -0.35f, 0.05f, 0.15f);
	isoTriangle->Draw(0.39f, -0.35f, 0.05f, 0.15f);
	isoTriangle->Draw(0.41f, -0.35f, 0.05f, 0.15f);
	isoTriangle->Draw(0.69f, -0.35f, 0.05f, 0.15f);
	isoTriangle->Draw(0.71f, -0.35f, 0.05f, 0.15f);
	isoTriangle->Draw(0.89f, -0.35f, 0.05f, 0.15f);
	isoTriangle->Draw(0.97f, -0.35f, 0.05f, 0.15f);
	isoTriangle->Draw(1.0f, -0.35f, 0.05f, 0.15f);

	// Executes any OpenGL commands
	glFlush();
}

// Runs the program
int main(int argc, char** argv) {
	GLFWwindow* window;

	// Initialize the library
	if (!glfwInit()) {
		return -1;
	}

	// Create a windowed mode window and OpenGL
	window = glfwCreateWindow(800, 600, "Hello World - HW 01", NULL, NULL);
	if (!window) {
		glfwTerminate();
		return -1;
	}

	// Make the window's context current
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) { return -1; }
	init();

	// Loop until the window is closed
	while (!glfwWindowShouldClose(window)) {
		// Update and draw 
		update();
		draw();

		// Swap front and back buffers
		glfwSwapBuffers(window);

		// Check for the cursor position
		glfwSetCursorPosCallback(window, cursorPosCallback);

		// Poll for and process events
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

// cursorPosCallback Method - Moves the entity to the cursor position
static void cursorPosCallback(GLFWwindow* window, double xpos, double ypos) {
	glfwGetCursorPos(window, &xpos, &ypos); // Gets the position of the cursor click
	glfwGetWindowSize(window, &width, &height); // Gets the window size

												// Translate coordinate systems
	xpos = xpos * (2.0 / 800.0) - 1.0;
	ypos = (ypos * (2.0 / 600.0) - 1.0) * -1.0;

	sunEnt->follow((float)xpos, (float)ypos);
}