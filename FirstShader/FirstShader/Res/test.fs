// 如果是 OpenGL ES 的运行环境
#ifdef GL_ES
precision mediump float;
#endif

void main {
    gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);
}