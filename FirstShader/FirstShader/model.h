#pragma once

#include "ggl.h"
#include <iostream>

//#include "sprite.h"

/**
 * 一个网格顶点
 */
struct Vertex
{
	/** x,y,z坐标 **/
	GLfloat position[4];

	/** r,g,b,a **/
	GLfloat color[4];

	/** UV 纹理坐标 **/
	GLfloat texcoord[4];

	/** 法线信息 **/
	GLfloat normal[4];
};

class VertexBuffer
{
private:
	Vertex *mVertices;

	int mVertexCount;

public:

	Vertex *getVertex() 
	{
		return this->mVertices;
	}

	int getVerticesCount() const
	{
		return this->mVertexCount;
	}


	void SetVertexCount(int c)
	{
		if (c <= 0) {
			std::cerr << "count <= 0" << std::endl;
			return;
		}
		this->mVertexCount = c;
		this->mVertices = new Vertex[c];
	}

	void SetPosition(int index, float x, float y, float z, float w = 1.0f);

	void SetColor(int index, float r, float g, float b, float a = 1.0f);

	void SetNormal(int index, float x, float y, float z, float a = 1.0f);

	void SetTexcoord(int index, float u, float v);
};

class Model// : public Sprite
{
private:
	std::vector<Vertex> vertices;

	std::vector<int> faceIndices;


public:

	Model();

	//void Init(const char *modelPath);

	//void Draw() override;

	std::vector<Vertex>& GetVertices()
	{
		return this->vertices;
	}

	std::vector<int>& GetFaces()
	{
		return this->faceIndices;
	}
};
