#pragma once

#include "utils.h"
#include "vertex.h"
#include "shader.h"
#include "Include/glm/glm.hpp"
#include "Include/glm/ext.hpp"

class Ground
{
private:
	//GLuint vbo;
	VertexBuffer *buffer_;
	Shader *shader;
	glm::mat4 model_matrix_;

public:
	// 设置数据，编译链接 Shader
	void Init();

	void Draw(glm::mat4 view_matrix, glm::mat4 projection_matrix);
};

