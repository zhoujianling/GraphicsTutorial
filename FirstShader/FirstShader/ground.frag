#version 330 core
#ifdef GL_ES
precision mediump float;
#endif

uniform sampler2D U_Texture;
in vec4 V_Color;
in vec4 V_TexCoord;

void main() {
	vec4 color = texture2D(U_Texture, V_TexCoord.xy);
	gl_FragColor = color;
}