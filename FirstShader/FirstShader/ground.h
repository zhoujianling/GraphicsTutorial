#pragma once

#include "utils.h"
#include "vertex.h"
#include "shader.h"
#include "Include/glm/glm.hpp"
#include "Include/glm/ext.hpp"

class Ground {
private:

	VertexBuffer buffer_;

	Shader shader_;

	glm::mat4 model_matrix_;

	std::string texture_color_name_;

public:

	Ground();

	// 设置数据，
	void InitGeometry();

	//编译链接 Shader
	void InitShader();

	void Draw(glm::mat4 view_matrix, glm::mat4 projection_matrix);

	float GetGroundHeight() const { return model_matrix_[1][3]; }
};

