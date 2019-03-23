attribute vec4 position;

uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;

// vertex shader 的入口函数
void main() {
    gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * position;    
}