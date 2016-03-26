/*	Veronica Lesnar
HW 01 - Hello World!
Entity - Handles complex Shape movement */
#pragma once

#include "Shape.h"

class Entity
{
public:
	// Constructors
	Entity(void);
	Entity(Shape* shape);

	// Destructor
	~Entity(void);

	// Variable
	Shape* ent;

	// Methods
	void draw();
	void shine();
	void follow(float xpos, float ypos);
};