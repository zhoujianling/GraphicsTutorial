#version 330 core
attribute vec4 position;
attribute vec4 color;
attribute vec4 normal;
attribute vec4 texcoord;

uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;
out vec4 V_Color;
out vec4 V_TexCoord;

void main() {
	V_Color = color;
	V_TexCoord = texcoord;
	gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * position;
	//gl_Position =  position;
}