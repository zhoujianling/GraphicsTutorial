#version 330 core
attribute vec4 position;
attribute vec4 color;

uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;
varying vec4 V_Color;

void main() {
	V_Color = color;
	gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * position;
	//gl_Position =  position;
}
