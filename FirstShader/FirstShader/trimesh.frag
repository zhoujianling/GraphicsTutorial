#version 330 core
#ifdef GL_ES
precision mediump float;
#endif

// position of directional light
uniform vec4 U_LightPosition;
uniform vec4 U_LightDiffuse;
uniform vec4 U_LightDiffuseMaterial;
uniform vec4 U_LightAmient;
uniform vec4 U_LightAmientMaterial;
varying vec4 V_Color;
varying vec4 V_Normal;

void main() {
	vec4 color = vec4(0.0, 0.0, 0.0, 0.0);
	vec4 ambien_color  = U_LightAmient * U_LightAmientMaterial;
	vec3 light_position = U_LightPosition.xyz;
	vec3 L = light_position;
	L = normalize(L);
	vec3 n = normalize(V_Normal.xyz);
	float diffuse_intensity = max(0.0, dot(L, n));
	vec4 diffuse_color = U_LightDiffuse * U_LightDiffuseMaterial * diffuse_intensity;
	color = ambien_color + diffuse_color;
	gl_FragColor = color;
	//gl_FragColor = V_Color;
}
