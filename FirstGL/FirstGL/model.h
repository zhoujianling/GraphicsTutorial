#pragma once

#include "ggl.h"
#include "sprite.h"

/**
 * 一个网格顶点
 */
struct Vertex
{
	/** x,y,z坐标 **/
	GLfloat position[3];

	/** UV 纹理坐标 **/
	GLfloat texcoord[2];

	/** 法线信息 **/
	GLfloat normal[3];
};

class Model : public Sprite
{
private:
	std::vector<Vertex> vertices;

	std::vector<int> faceIndices;


public:

	Model();

	void Init(const char *modelPath);

	void Draw() override;

	std::vector<Vertex>& GetVertices()
	{
		return this->vertices;
	}

	std::vector<int>& GetFaces()
	{
		return this->faceIndices;
	}
};
