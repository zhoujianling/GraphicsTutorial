#version 330 core
#ifdef GL_ES
precision mediump float;
#endif

uniform vec4 U_LightAmient;
uniform vec4 U_LightAmientMaterial;
varying vec4 V_Color;

void main() {
	vec4 color = vec4(0.0, 0.0, 0.0, 0.0);
	vec4 ambien_color  = U_LightAmient * U_LightAmientMaterial;
	color = ambien_color;
	gl_FragColor = color;
	//gl_FragColor = V_Color;
}
