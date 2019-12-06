#version 330 core
#ifdef GL_ES
precision mediump float;
#endif

// position of directional light
uniform vec4 U_LightPosition;
uniform vec4 U_LightDiffuse;
uniform vec4 U_LightDiffuseMaterial;
uniform vec4 U_LightAmbient;
uniform vec4 U_LightAmbientMaterial;
uniform vec4 U_LightSpecular;
uniform vec4 U_LightSpecularMaterial;
uniform vec4 U_CameraPosition;
uniform vec4 U_LightOpt;
uniform sampler2D U_Texture;

//varying vec4 V_Color;
varying vec4 V_Normal;
varying vec4 V_WorldPosition;
varying vec4 V_TexCoord;

void main() {
	vec4 color = vec4(0.1, 0.1, 0.1, 0.5);
	gl_FragColor = color;
	//gl_FragColor = V_Color;
}
