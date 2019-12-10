#pragma once
#include "utils.h"
#include "vertex.h"
#include "shader.h"
#include "Include/glm/glm.hpp"
#include "Include/glm/ext.hpp"

struct BoundingBox {
	/* the center of bounding box */
	glm::fvec3 center_;

	/* the length of three sides */
	glm::fvec3 extent_;

public:
	BoundingBox(): center_(0.0, 0.0, 0.0), extent_(0.0, 0.0, 0.0) {}

	BoundingBox(const glm::vec3& c, const glm::vec3& e) :
		center_(c), extent_(e) {}

#define CEB(index, a, b, c) \
	vertex_buffer.GetVertex()[(index)].position[0] = center_.x a extent_.x; \
	vertex_buffer.GetVertex()[(index)].position[1] = center_.y b extent_.y; \
	vertex_buffer.GetVertex()[(index)].position[2] = center_.z c extent_.z; \
	vertex_buffer.GetVertex()[(index)].position[3] = 1.0f; \
	vertex_buffer.SetColor((index), 1.0, 0.0, 0.0, 1.0)

#define VVB(index, a, b) \
	element_buffer.GetBuffer()[(index * 2 + 0)] = a; \
	element_buffer.GetBuffer()[(index * 2 + 1)] = b 

	void ToWireframe(VertexBuffer& vertex_buffer, ElementBuffer& element_buffer) const {
		vertex_buffer.SetVertexCount(8);
		element_buffer.SetBufferLength(12 * 2);
		CEB(0, +, +, +);
		CEB(1, +, +, -);
		CEB(2, +, -, +);
		CEB(3, +, -, -);
		CEB(4, -, -, -);
		CEB(5, -, -, +);
		CEB(6, -, +, -);
		CEB(7, -, +, +);
		VVB(0, 0, 1);  VVB(1, 0, 2); VVB(2, 1, 3); VVB(3, 2, 3);
		VVB(4, 4, 5);  VVB(5, 4, 6); VVB(6, 5, 7); VVB(7, 6, 7);
		VVB(8, 0, 7);  VVB(9, 1, 6); VVB(10, 2, 5); VVB(11, 3, 4);
		//for (int i = 0; i < 8; i++) {
		//	std::cout << "(" << vertex_buffer.GetVertex()[i].position[0] << ", "
		//		<< vertex_buffer.GetVertex()[i].position[1] << ", "
		//		<< vertex_buffer.GetVertex()[i].position[2] << ") " << std::endl;
		//}
	}
#undef VVB
#undef CEB
};

namespace zjl {
class TriMesh// : public Sprite
{
private:
	bool is_transparent_;
private:

	VertexBuffer vertex_buffer_;

	ElementBuffer element_buffer_;

	std::string	texture_color_name_;

	Shader shader;

	Shader shadow_shader_;

public:
	TriMesh();

	~TriMesh();

	void InitShader();

	void InitGeometry(const VertexBuffer& vb, const ElementBuffer& eb);

	void InitGeometry(std::string model_path);

	void DrawShadow(glm::mat4 view_matrix, glm::mat4 projection_matrix, glm::mat4 model_matrix);

	void Draw(glm::mat4 view_matrix, glm::mat4 projection_matrix, glm::mat4 model_matrix);

	void SetAmbientMaterial(float r, float g, float b, float a);

	void SetDiffuseMaterial(float r, float g, float b, float a);

	void SetSpecularMaterial(float r, float g, float b, float a);

	VertexBuffer& GetVertexBuffer() { return this->vertex_buffer_; }

	ElementBuffer& GetElementBuffer() { return this->element_buffer_; }

	// void SetTexture(const std::string & texture_image_path);

	void SetTextureColorFile(const std::string& texture_color) { this->texture_color_name_ = texture_color; }

	void SetTransparent(bool is_t) { this->is_transparent_ = is_t; }

	//void Translate(float x, float y, float z);
};

};
