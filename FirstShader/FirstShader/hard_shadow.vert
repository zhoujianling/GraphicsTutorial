#version 330 core
attribute vec4 position;
attribute vec4 color;
attribute vec4 normal;
attribute vec4 texcoord;

uniform vec4 U_LightPosition;
uniform vec4 U_PlaneOpt;
uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;
uniform mat4 IT_ModelMatrix;
varying vec4 V_Normal;
varying vec4 V_WorldPosition;
varying vec4 V_TexCoord;

void main() {
	// V_Color = color;
	V_TexCoord = texcoord;
	V_Normal = IT_ModelMatrix * normal;
	V_WorldPosition = ModelMatrix * position;
	vec3 planeNormal = U_PlaneOpt.xyz;
	vec3 lightDirection = V_WorldPosition.xyz - U_LightPosition.xyz;
	vec3 projectionPosition = U_LightPosition.xyz - (U_PlaneOpt[3] + dot(U_PlaneOpt.xyz, U_LightPosition.xyz)) / (dot(U_PlaneOpt.xyz, lightDirection)) * lightDirection;
	vec4 projectionPositionHomo;
	projectionPositionHomo.xyz = projectionPosition;
	projectionPositionHomo[3] = 1.0;
	gl_Position = ProjectionMatrix * ViewMatrix * projectionPositionHomo;
}
