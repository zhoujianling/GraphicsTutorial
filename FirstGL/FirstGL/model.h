#pragma once

#include "ggl.h"
#include "sprite.h"

/**
 * 一个网格顶点
 */
struct Vertex
{
	/** x,y,z坐标 **/
	GLfloat position_[3];

	/** UV 纹理坐标 **/
	GLfloat tex_coord_[2];

	/** 法线信息 **/
	GLfloat normal_[3];
};

class Model : public Sprite
{
private:
	std::vector<Vertex> vertices_;

	std::vector<int> face_indices_;


public:

	Model();

	void Init(const char *model_path);

	void Draw() override;

	std::vector<Vertex>& GetVertices()
	{
		return this->vertices_;
	}

	std::vector<int>& GetFaces()
	{
		return this->face_indices_;
	}
};
