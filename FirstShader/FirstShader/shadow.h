#pragma once
#include "Include/glm/glm.hpp"
#include "Include/glm/ext.hpp"
#include "shader.h"
#include "utils.h"
#include "vertex.h"
#include <unordered_set>

class Shadow {
private:

	VertexBuffer vertex_buffer_;

	ElementBuffer element_buffer_;

	Shader shader;

	glm::mat4 model_matrix_;

	//void ComputeBoundingBox();

public:
	Shadow(const VertexBuffer buffer, const ElementBuffer edge_buffer);

	~Shadow();

	void Draw(glm::mat4 view_matrix, glm::mat4 projection_matrix);

};
