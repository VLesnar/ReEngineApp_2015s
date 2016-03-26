/*	Veronica Lesnar
HW 01 - Hello World!
Shape - Holds a buffer of vertices to represent a single shape and draws the
shape to the screen at a specified position and scale */
#include "Shape.h"

// Default constructor
Shape::Shape(void)
{
}

// Parameterized constructor
Shape::Shape(GLfloat vertArray[], GLsizei numVert, GLuint programIndex)
{
	vertices = numVert;	// Saves the vertices
	index = programIndex; // Saves the program index

						  // Creates and binds the VAO
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// Creates and binds the VBO
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	int arrayLength = vertices * 5; // Calculate the length of the array
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * arrayLength, vertArray, GL_STATIC_DRAW); // CHECK TO MAKE SURE IT'S FLOAT NOT GLFLOAT

																						   // Setup and enable the vertex arrays
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, (sizeof(GL_FLOAT) * 5), 0); // Position
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, (sizeof(GL_FLOAT) * 5), (void*)(sizeof(GL_FLOAT) * 2)); // Color
	glEnableVertexAttribArray(0); // Position
	glEnableVertexAttribArray(1); // Color

								  // Get variables from vertexShader.glsl
	offset = glGetUniformLocation(index, "offset"); // Gets the offset
	scalei = glGetUniformLocation(index, "scale"); // Gets the scale
	wm = glGetUniformLocation(index, "worldMatrix"); // Gets the worldMatrix

													 // Initialize vectors
	position = vec3(0, 0, 0);
	scaling = vec3(1, 1, 1);
	rotation = vec3(0, 0, 1);
	angle = 0;
}

// Destructor
Shape::~Shape(void)
{
	// Deletes the vertex arrays and the buffers for the VAO and VBO
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VAO);
	glDeleteVertexArrays(1, &VBO);
	glDeleteBuffers(1, &VBO);
}

// Draw Method - Binds the shape's VAO and draws it
void Shape::Draw(float x, float y, float xScale, float yScale) {
	// Set uniform variables in vertexShaders.glsl
	position = vec3(x, y, 0);
	scaling = vec3(xScale, yScale, 1);
	mat4 t = translate(position);
	mat4 s = scale(scaling);
	mat4 r = rotate(angle, rotation);
	mat4 worldMatrix = t * s * r;
	glProgramUniformMatrix4fv(index, wm, 1, GL_FALSE, &worldMatrix[0][0]); // Sets the worldMatrix variable

																		   // Binds the VAO and draws it to the screen
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, vertices);
}