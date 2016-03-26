/*	Veronica Lesnar
HW 01 - Hello World!
Shape - Holds a buffer of vertices to represent a single shape and draws the
shape to the screen at a specified position and scale */
#pragma once

#define _USE_MATH_DEFINES

#include <glew.h>
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <math.h>

using namespace glm;

class Shape
{
public:
	// Constructors
	Shape(void);
	Shape(GLfloat vertArray[], GLsizei numVert, GLuint programIndex);

	// Destructor
	~Shape(void);

	// Variables
	GLuint VBO; // Vertex Buffer Object - Uploads vertex data to the graphics card
	GLuint VAO;	// Vertex Array Object - References the VBOs created
	GLint index; // Holds the shader program's index
	GLsizei vertices; // Holds the total number of vertices
	GLint offset; // Places the shape on the screen
	GLint scalei; // Scales the shape
	GLint wm; // Location of the wold matrix
	vec3 position; // Holds the position of the shape
	vec3 scaling; // Holds the scale of the shape
	vec3 rotation; // Holds the rotation axis
	float angle; // Holds the amount to rotate

				 // Methods
	void Draw(float x, float y, float xScale, float yScale);
	void DrawCircle(float x, float y, float radius);
};