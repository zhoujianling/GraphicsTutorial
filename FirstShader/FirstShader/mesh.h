#pragma once
#include "utils.h"
#include "vertex.h"
#include "shader.h"
#include "Include/glm/glm.hpp"
#include "Include/glm/ext.hpp"

struct BoundingBox {
	/* the center of bounding box */
	glm::fvec3 m_center;

	/* the length of three sides */
	glm::fvec3 m_extent;

public:
	BoundingBox(): m_center(0.0, 0.0, 0.0), m_extent(0.0, 0.0, 0.0) {}

	BoundingBox(const glm::vec3& c, const glm::vec3& e) :
		m_center(c), m_extent(e) {}
};


class TriMesh// : public Sprite
{
private:

	VertexBuffer *vertex_buffer_;

	ElementBuffer *element_buffer_;

	Shader *shader;

	Shader* m_bbox_shader;

	glm::mat4 model_matrix_;

	BoundingBox bbox_;

	void ComputeBoundingBox();

public:
	TriMesh();

	~TriMesh();

	void Init(std::string model_path);

	void Draw(glm::mat4 view_matrix, glm::mat4 projection_matrix);

	void SetAmbientMaterial(float r, float g, float b, float a);

	void SetDiffuseMaterial(float r, float g, float b, float a);

	void SetSpecularMaterial(float r, float g, float b, float a);

	void SetTexture(const std::string & texture_image_path);

	const BoundingBox& GetBoundingBox() const { return this->bbox_; }

	//void Translate(float x, float y, float z);
};
