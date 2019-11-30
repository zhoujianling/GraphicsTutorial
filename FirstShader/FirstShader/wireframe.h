#pragma once
#include "Include/glm/glm.hpp"
#include "Include/glm/ext.hpp"
#include "shader.h"
#include "utils.h"
#include "vertex.h"
#include <unordered_set>


class WireFrame {
private:

	VertexBuffer vertex_buffer_;

	ElementBuffer element_buffer_;

	Shader *shader;

	glm::mat4 model_matrix_;

	//void ComputeBoundingBox();

public:
	WireFrame();

	~WireFrame();

	/** 
	 * @param buffer: ¶¥µãbuffer
	 * @param edge_buffer: ±ß buffer
	**/
	void Init(const VertexBuffer& buffer, const ElementBuffer& edge_buffer);

	void Init(std::string model_path);

	void Draw(glm::mat4 view_matrix, glm::mat4 projection_matrix);

	void SetAmbientMaterial(float r, float g, float b, float a);

	void SetDiffuseMaterial(float r, float g, float b, float a);

	void SetSpecularMaterial(float r, float g, float b, float a);

	void SetTexture(const std::string & texture_image_path);

};
