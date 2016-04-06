#pragma once

#define _USE_MATH_DEFINES

#include <stdlib.h>
#include <fstream>
#include <math.h>
#include <cstdio>
#include <vector>
#include <iostream>
#include <time.h>

#include <glew\glew.h>
#include "glfw\glfw3.h"

#include <glm\glm.hpp>
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\type_ptr.hpp"

#include "tiny_obj_loader.h"

#define STAGE_WIDTH 12
#define STAGE_HEIGHT 12
#define STAGE_DEPTH 12

#define NUM_BALLS 5
#define MAX_SPEED 0.5

//This struct provided for your convenience
struct Object {
	//other object data
	float vx, vy, vz; //velocities in x and y direction
	int isColliding;// see display() for how this is used
	glm::vec3 pos; // x, y (and z) position for sphere (or top left AABB corner)
	float radius; // Radius for bounding sphere (or width of AABB) 
};

//Our cube model
//Number of indices
const int elements = 36;
//The actual indices
static const GLuint cubeIndices[36] = {
	// front
	0, 1, 2,
	2, 3, 0,
	// top
	3, 2, 6,
	6, 7, 3,
	// back
	7, 6, 5,
	5, 4, 7,
	// bottom
	4, 5, 1,
	1, 0, 4,
	// left
	4, 0, 3,
	3, 7, 4,
	// right
	1, 5, 6,
	6, 2, 1,
};

//Vertices
static const glm::vec3 cube[8] = {
	// front
	glm::vec3(-6.0, -6.0, 6.0),
	glm::vec3(6.0, -6.0, 6.0),
	glm::vec3(6.0, 6.0, 6.0),
	glm::vec3(-6.0, 6.0, 6.0),
	// back
	glm::vec3(-6.0, -6.0, -6.0),
	glm::vec3(6.0, -6.0, -6.0),
	glm::vec3(6.0, 6.0, -6.0),
	glm::vec3(-6.0, 6.0, -6.0)
};

class pe3
{
	
public:
	pe3(int argc, char** argv);
	~pe3(void);

	void update(void);
	void reshape (int w, int h);
	void keyboard(int key, int scancode, int action, int mods);
	void display(void);

private:

    //Our view and perspective matrices
    glm::mat4 viewMatrix;
    glm::mat4 projMatrix;
	glm::mat4 modelMatrix;

    //This stores the "location"
    //of the "model", "view", and proj variables
    //we use in our vertex shader
    GLuint modelLocation;
    GLuint viewLocation;
    GLuint projLocation;
	//This stores to location of the
	//boolean in the vertex shader which
	//controls colour. Check out vertex.glsl for more!
	GLuint boolLocation;
	GLuint vertexAttribLocation;

	//We have two models
	GLuint cubeVAOLocation, cubeVBOLocation, cubeIBOLocation;
	GLuint sphereVAOLocation, sphereVBOLocation, sphereIBOLocation;

	//For handling uppercase character input with GLFW
	//(If anyone knows of a better way to do this, I'm
	//all ears!)
	bool caps = false;

	bool simulationActive = true;

	//The amount of balls on the screen.
	Object balls[NUM_BALLS];

	//Our sphere model
	//(all data included in shape_t)
	std::vector<tinyobj::shape_t> sphere;

    //This variable stores
    //our camera's translation
	glm::vec3 cameraTrans = glm::vec3(0.0f, 0.0f, -15.0f);

	//The time at our current and last frames
	float currentFrame, lastFrame;
	//The amount of time steps to process per frame
	float timeStepsToProcess = 0.0f;
	// 60 fps, in milliseconds, is 16.667
	float deltaT = 16.667f;

	//The location of our OpenGL program
	GLuint program;

	void initPipeline(void);
	void initBuffers(void);
	void init(void);

	bool initShader(GLenum type, std::string file, GLuint program);
	bool checkGLErrors(const char* description);
	bool readFile(std::string filename, std::string* target);

	//Any loaded shaders will be stored here.
	//So we can delete them later!
	std::vector<GLuint> shaders;
};

