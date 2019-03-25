attribute vec4 position;
attribute vec4 color;
attribute vec2 texcoord;

uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;
varying vec4 V_Color;
varying vec2 V_Texcoord;

void 
main() 
{
	V_Color = color;
	V_Texcoord = texcoord;
    gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * position;    
}