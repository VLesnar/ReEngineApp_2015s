#version 430

//Our matrices
uniform mat4 proj;
uniform mat4 model;
uniform mat4 view;
uniform int collision;

//outgoing color
out vec4 col;

//incoming vector
layout (location = 0) in vec3 vertex_in;

void main()
{
	if( collision == 1 )
		col = vec4(1.0,0.0,0.0,0.0);
	else	
		col = vec4(vertex_in, 1.0);

	gl_Position = proj * ( view * ( model * vec4(vertex_in,1.0)));
}

