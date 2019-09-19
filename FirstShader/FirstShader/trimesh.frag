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
uniform vec4 U_LightSpecular;
uniform vec4 U_LightSpecularMaterial;
uniform vec4 U_CameraPosition;
uniform vec4 U_LightOpt;

varying vec4 V_Color;
varying vec4 V_Normal;
varying vec4 V_WorldPosition;

void main() {
	vec4 color = vec4(0.0, 0.0, 0.0, 0.0);
	vec4 ambien_color  = U_LightAmient * U_LightAmientMaterial;
	// compute diffuse color 
	vec3 light_position = U_LightPosition.xyz;
	vec3 light_position_copy = light_position;
	light_position_copy = normalize(light_position_copy);
	vec3 n = normalize(V_Normal.xyz);
	float diffuse_intensity = max(0.0, dot(light_position_copy, n));
	vec4 diffuse_color = U_LightDiffuse * U_LightDiffuseMaterial * diffuse_intensity;
	// compute specular color
	vec4 specular_color = vec4(0.0, 0.0, 0.0, 0.0);
	if (diffuse_intensity > 0.0) {
		vec3 refect_direction = normalize(reflect(- light_position_copy, n));
		vec3 view_direction = normalize(U_CameraPosition.xyz - V_WorldPosition.xyz);
		specular_color = U_LightSpecular * U_LightSpecularMaterial * 
			pow(max(0.0, dot(view_direction, refect_direction)), U_LightOpt.x);
			
	}
	// compute final color 
	color = ambien_color + diffuse_color + specular_color;
	gl_FragColor = color;
	//gl_FragColor = V_Color;
}
