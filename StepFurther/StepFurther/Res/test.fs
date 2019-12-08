#ifdef GL_ES
precision mediump float;
#endif
uniform sampler2D U_Texture;
varying vec4 V_Color;
varying vec2 V_Texcoord;

void 
main()
{
    gl_FragColor = V_Color * texture2D(U_Texture, V_Texcoord);

}