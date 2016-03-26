/*	Veronica Lesnar
HW 01
Entity - Handles complex Shape movement */
#include "Entity.h"

// Constructors
Entity::Entity(void)
{
}

Entity::Entity(Shape* shape) {
	ent = shape;
}

// Destructor
Entity::~Entity(void)
{
}

// draw Method - Draws the entity
void Entity::draw() {
	ent->Draw(ent->position.x, ent->position.y, ent->scaling.x, ent->scaling.x);
}

// shine Method - Rotates a shape
void Entity::shine() {
	ent->angle += 0.001f;
}

// follow Method - Makes the entity follow the cursor
void Entity::follow(float xpos, float ypos) {
	ent->position.x = xpos;
	ent->position.y = ypos;
}