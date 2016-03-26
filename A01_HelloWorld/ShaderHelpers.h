/*	Veronica Lesnar
HW 01 - Hello World!
ShaderHelpers.h - Holds methods to load and use shaders */
#pragma once

#include <glew.h>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

class ShaderHelpers
{
public:
	ShaderHelpers(void);
	~ShaderHelpers(void);
	char* loadTextFile(const char* file);
	GLuint loadShader(const char* file, GLenum shaderType);
	GLuint loadShaderProgram(const char* vertexFile, const char* fragmentFile);
	void setShaderColor(GLuint program, const char* uniVar, float r, float g, float b);
};