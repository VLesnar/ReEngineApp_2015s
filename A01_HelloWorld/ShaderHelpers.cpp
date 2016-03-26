/*	Veronica Lesnar
HW 01 - Hello World!
ShaderHelpers.h - Holds methods to load and use shaders */
#include "ShaderHelpers.h"

// Constructor
ShaderHelpers::ShaderHelpers(void)
{
}

// Destructor
ShaderHelpers::~ShaderHelpers(void)
{
}

// loadTextFile Method - Loads a text file and returns it for use as a shader
char* ShaderHelpers::loadTextFile(const char* file) {
	// Get the file
	ifstream inFile(file, ios::binary);

	// Reads in the file contents and returns it
	if (inFile.is_open()) {
		inFile.seekg(0, ios::end);
		int length = (int)inFile.tellg();
		inFile.seekg(0, ios::beg);

		char* fileContents = new char[length + 1];
		inFile.read(fileContents, length);
		fileContents[length] = 0;
		cout << fileContents;
		inFile.close();

		return fileContents;
	}
	// If there is no valid file
	else {
		return 0;
	}
}

// loadShader Method - Creates and loads a shader from a text file
GLuint ShaderHelpers::loadShader(const char* file, GLenum shaderType) {
	// Loads the text file in
	const char* source = loadTextFile(file);

	// If there is no valid file
	if (source == 0) {
		cout << "Error. Text file is invalid." << endl;
		return 0;
	}
	else {
		// Create a shader
		GLuint vertexShader = glCreateShader(shaderType);

		glShaderSource(vertexShader, 1, &source, 0);
		glCompileShader(vertexShader);
		delete[] source;

		GLint isCompiled = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
		// Return the shader if it successfully compiles
		if (isCompiled == GL_TRUE) {
			return vertexShader;
		}
		// Get the log if the shader doesn't compile successfully
		else {
			GLint maxLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);
			char* infoLog = new char[maxLength];
			glGetShaderInfoLog(vertexShader, maxLength, 0, infoLog);
			glDeleteShader(vertexShader);
			delete infoLog;
			return 0;
		}
	}
}

// loadShaderProgram Method - Creates a program and loads shaders into it
GLuint ShaderHelpers::loadShaderProgram(const char* vertexFile, const char* fragmentFile) {
	// Loads in a vertex shader
	GLuint vertexShader = loadShader(vertexFile, GL_VERTEX_SHADER);
	if (vertexShader == 0) {
		return 0;
	}

	// Loads in a fragment shader
	GLuint fragmentShader = loadShader(fragmentFile, GL_FRAGMENT_SHADER);
	if (fragmentShader == 0) {
		return 0;
	}

	// Attaches the shaders to a created program
	GLuint program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);

	// Links the program and returns it if it is succesful
	glLinkProgram(program);

	GLint isLinked = 0;
	glGetProgramiv(program, GL_LINK_STATUS, (int *)&isLinked);
	if (isLinked == GL_TRUE) {
		return program;
	}
	// Get the log if the program doesn't link successfully
	else {
		GLint maxLength = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);
		char* infoLog = new char[maxLength];
		glGetProgramInfoLog(program, maxLength, 0, &infoLog[0]);
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		delete infoLog;
		return 0;
	}
}

// setShaderColor Method - Sets the color of the shader
void ShaderHelpers::setShaderColor(GLuint program, const char* uniVar, float r, float g, float b) {
	GLuint location = glGetUniformLocation(program, uniVar);
	glProgramUniform4f(program, location, r, g, b, 1.0f);
}