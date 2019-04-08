#pragma once
#include "utils.h"
#include "vertex.h"
#include "shader.h"
#include "Include/glm/glm.hpp"
#include "Include/glm/ext.hpp"


class TriMesh// : public Sprite
{
private:

	VertexBuffer *vertex_buffer_;

	ElementBuffer *element_buffer_;

	Shader *shader;

	glm::mat4 model_matrix_;

public:
	TriMesh();

	void Init(std::string model_path);

	void Draw(glm::mat4 view_matrix, glm::mat4 projection_matrix);
	//TriMesh();

	//void Translate(float x, float y, float z);
};
