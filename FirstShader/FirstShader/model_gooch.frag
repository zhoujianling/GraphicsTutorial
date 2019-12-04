#version 330 core
#ifdef GL_ES
precision mediump float;
#endif

uniform sampler2D U_Texture;
// position of directional light
uniform vec4 U_LightPosition;
uniform vec4 U_LightDiffuse;
uniform vec4 U_LightDiffuseMaterial;
uniform vec4 U_LightAmient;
uniform vec4 U_LightAmientMaterial;
uniform vec4 U_LightSpecular;
uniform vec4 U_LightSpecularMaterial;
uniform vec4 U_CameraPosition;
uniform vec4 U_LightOpt;

varying vec4 V_Color;
varying vec4 V_Normal;
varying vec4 V_WorldPosition;
varying vec4 V_TexCoord;

void main() {
	vec4 color = vec4(0.0, 0.0, 0.0, 0.0);
	vec4 cool_color = vec4(0.0, 0.0, 0.55, 1.0);
	vec4 warm_color = vec4(0.3, 0.3, 0.05, 1.0);
	vec4 highlight_color = vec4(1.0, 1.0, 1.0, 1.0);

	vec4 ambien_color  = U_LightAmient * U_LightAmientMaterial;
	// compute diffuse color 
	vec3 light_direction = U_LightPosition.xyz - V_WorldPosition.xyz;
	vec3 light_direction_copy = light_direction;
	light_direction_copy = normalize(light_direction_copy);
	vec3 n = normalize(V_Normal.xyz);
	float diffuse_intensity = max(0.0, dot(light_direction_copy, n));
	vec4 diffuse_color = U_LightDiffuse * U_LightDiffuseMaterial * diffuse_intensity;
	// compute gooch color
	vec3 refect_direction = normalize(reflect(- light_direction_copy, n));
	vec3 view_direction = normalize(U_CameraPosition.xyz - V_WorldPosition.xyz);
	float t = (dot(n, light_direction_copy) + 1.0) * 0.5;
	float s = clamp(100 * (dot(refect_direction, view_direction)) - 97, 0.0, 1.0);
	color = s * highlight_color + (1.0 - s) * (t * warm_color + (1.0 - t) * cool_color);

	// compute final color 
	// color = ambien_color + diffuse_color + specular_color;
	color[3] = 0.3;
	gl_FragColor = color;
	//gl_FragColor = V_Color;
}
