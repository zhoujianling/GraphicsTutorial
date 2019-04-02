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
	this->vertex_count_ = c;
	this->vertices_ = new Vertex[c];
	memset(vertices_, 0, c * sizeof(Vertex));
	vbo_ = CreateBufferObject(GL_ARRAY_BUFFER, sizeof(Vertex) * vertex_count_, GL_STATIC_DRAW, nullptr);
}

void VertexBuffer::SetPosition(int index, float x, float y, float z, float w)
{
	this->vertices_[index].position[0] = x;
	this->vertices_[index].position[1] = y;
	this->vertices_[index].position[2] = z;
	this->vertices_[index].position[3] = w;
}

void VertexBuffer::SetColor(int index, float r, float g, float b, float a)
{
	this->vertices_[index].color[0] = r;
	this->vertices_[index].color[1] = g;
	this->vertices_[index].color[2] = b;
	this->vertices_[index].color[3] = a;
}

void VertexBuffer::SetNormal(int index, float x, float y, float z, float a)
{
	this->vertices_[index].normal[0] = x;
	this->vertices_[index].normal[1] = y;
	this->vertices_[index].normal[2] = z;
	this->vertices_[index].normal[3] = 1.0;
}

void VertexBuffer::SetTexcoord(int index, float u, float v)
{
	this->vertices_[index].texcoord[0] = u;
	this->vertices_[index].texcoord[1] = v;
}

void VertexBuffer::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, vbo_);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vertex) * vertex_count_, vertices_);
}

void VertexBuffer::UnBind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Vertex& VertexBuffer::Get(int index)
{
	return vertices_[index];
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
	// 之前在 CreateBufferObject 并没有真正把 indices_buffer 提交到 OpenGL，
	// 我们可以在开辟缓冲区后再往里面填数据，再之后 才 SubmitData
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(unsigned int) * length_, indices_buffer_);
}

void ElementBuffer::UnBind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

