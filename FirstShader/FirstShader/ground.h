#pragma once

#include "utils.h"
#include "vertex.h"
#include "shader.h"
#include "Include/glm/glm.hpp"
#include "Include/glm/ext.hpp"

class Camera;
class Ground {
private:

	VertexBuffer buffer_;

	Shader shader_;

	glm::mat4 model_matrix_;

	const float cell_size;

	const int cell_num;

	std::string texture_color_name_;

	std::string texture_normal_name_;

public:

	Ground();

	// 设置数据，
	void InitGeometry();

	//编译链接 Shader
	void InitShader();

	void Draw(const Camera&);

	float GetGroundHeight() const { return model_matrix_[1][3]; }
};

