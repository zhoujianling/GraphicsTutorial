#include "vertex.h"
#include "utils.h"
// #include "happly.h"
#include "io.h"
#include "iostream"

void VertexBuffer::SetVertexCount(int c)
{
	if (c <= 0) {
		std::cerr << "count <= 0" << std::endl;
		return;
	}
	this->mVertexCount = c;
	this->mVertices = new Vertex[c];
	memset(mVertices, 0, c * sizeof(Vertex));
	mVBO = CreateBufferObject(GL_ARRAY_BUFFER, sizeof(Vertex) * mVertexCount, GL_STATIC_DRAW, nullptr);
}

void VertexBuffer::SetPosition(int index, float x, float y, float z, float w)
{
	this->mVertices[index].position[0] = x;
	this->mVertices[index].position[1] = y;
	this->mVertices[index].position[2] = z;
	this->mVertices[index].position[3] = w;
}

void VertexBuffer::SetColor(int index, float r, float g, float b, float a)
{
	this->mVertices[index].color[0] = r;
	this->mVertices[index].color[1] = g;
	this->mVertices[index].color[2] = b;
	this->mVertices[index].color[3] = a;
}

void VertexBuffer::SetNormal(int index, float x, float y, float z, float a)
{
	this->mVertices[index].normal[0] = x;
	this->mVertices[index].normal[1] = y;
	this->mVertices[index].normal[2] = z;
	this->mVertices[index].normal[3] = 1.0;
}

void VertexBuffer::SetTexcoord(int index, float u, float v)
{
	this->mVertices[index].texcoord[0] = u;
	this->mVertices[index].texcoord[1] = v;
}

void VertexBuffer::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	// 这玩意有啥用？
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vertex) * mVertexCount, mVertices);
}

void VertexBuffer::UnBind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Vertex& VertexBuffer::Get(int index)
{
	return mVertices[index];
}

ElementBuffer::ElementBuffer():indices_buffer_(nullptr), length_(0)
{
}

void ElementBuffer::SetBufferLength(int len)
{
	length_ = len;
	indices_buffer_ = new unsigned int[len];
	memset(indices_buffer_, 0, len * sizeof(unsigned int));
	ebo = CreateBufferObject(GL_ELEMENT_ARRAY_BUFFER, len * sizeof(unsigned int), GL_STATIC_DRAW, nullptr);
}

void ElementBuffer::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
}

void ElementBuffer::UnBind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

