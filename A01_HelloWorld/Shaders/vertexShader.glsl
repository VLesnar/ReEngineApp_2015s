#version 430

layout (location = 0) in vec2 position;
layout (location = 1) in vec3 color;

uniform vec3 offset;
uniform vec3 scale;
uniform mat4 worldMatrix;
out vec4 vertColor;

void main() {
	gl_Position = worldMatrix * vec4(position, 0, 1);
	vertColor = vec4(color, 1);
}