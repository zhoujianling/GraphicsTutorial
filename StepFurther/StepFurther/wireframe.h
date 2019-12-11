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

	Shader shader;

	//void ComputeBoundingBox();

public:
	WireFrame();

	~WireFrame();

	/** 
	 * @param buffer: ¶¥µãbuffer
	 * @param edge_buffer: ±ß buffer
	**/
	void InitShader();

	void Draw(glm::mat4 view_matrix, glm::mat4 projection_matrix, glm::mat4 model_matrix);

	void SetAmbientMaterial(float r, float g, float b, float a);

	void SetDiffuseMaterial(float r, float g, float b, float a);

	void SetSpecularMaterial(float r, float g, float b, float a);

	void SetTexture(const std::string & texture_image_path);

	VertexBuffer& GetVertexBuffer() { return this->vertex_buffer_; }

	ElementBuffer& GetElementBuffer() { return this->element_buffer_; }

	Shader& GetShader() { return this->shader; }

};
