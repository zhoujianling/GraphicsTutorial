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
	Vertex *vertices_;

	int vertex_count_;

	GLuint vbo_;

public:

	Vertex *GetVertex() 
	{
		return this->vertices_;
	}

	int GetVerticesCount() const
	{
		return this->vertex_count_;
	}

	void SetVertexCount(int c);

	void SetPosition(int index, float x, float y, float z, float w = 1.0f);

	void SetColor(int index, float r, float g, float b, float a = 1.0f);

	void SetNormal(int index, float x, float y, float z, float a = 1.0f);

	void SetTexcoord(int index, float u, float v);

	void Bind();

	void UnBind();

	Vertex& Get(int index);
};

class ElementBuffer
{
private:

	unsigned int *indices_buffer_;

	int length_;

	GLuint ebo;
public:

	ElementBuffer();

	void SetBufferLength(int len);

	unsigned int *GetBuffer()
	{
		return indices_buffer_;
	}

	void Bind();

	void UnBind();

	int GetLength() const { return length_; }
};