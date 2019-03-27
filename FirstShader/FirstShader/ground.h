#pragma once

#include "utils.h"
#include "model.h"
#include "shader.h"
#include "Include/glm/glm.hpp"

class Ground
{
private:
	GLuint vbo;
	VertexBuffer *buffer;
	Shader *shader;
	glm::mat4 modelMatrix;

public:
	// 设置数据，编译链接 Shader
	void Init();

	void Draw(glm::mat4 &viewMatrix, glm::mat4 &projectionMatrix);
};

