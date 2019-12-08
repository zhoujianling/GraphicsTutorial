#include "vertex.h"
#include "utils.h"
// #include "happly.h"
#include "io.h"
#include "iostream"

VertexBuffer::VertexBuffer():
vertices_(nullptr),
vertex_count_(0),
vbo_(0)
{
}

VertexBuffer::~VertexBuffer()
{
	std::cerr << "Debug: " << "VertexBuffer is destroying ..." << std::endl;
	if (vertices_ != nullptr) {
		ClearBuffer();
	}
}

VertexBuffer::VertexBuffer(const VertexBuffer& buffer)
{
	this->vbo_ = buffer.vbo_;
	this->vertex_count_ = buffer.vertex_count_;
	this->vertices_ = new Vertex[this->vertex_count_];
	memcpy(this->vertices_, buffer.vertices_, sizeof(Vertex) * this->vertex_count_);
}

VertexBuffer& VertexBuffer::operator=(const VertexBuffer& buffer)
{
	// TODO: 在此处插入 return 语句
	if (this != &buffer) {
		if (this->vertices_ != nullptr) ClearBuffer();
		this->vbo_ = buffer.vbo_;
		this->vertex_count_ = buffer.vertex_count_;
		this->vertices_ = new Vertex[this->vertex_count_];
		memcpy(this->vertices_, buffer.vertices_, sizeof(Vertex) * this->vertex_count_);
	}
	return *this;
}

VertexBuffer::VertexBuffer(VertexBuffer&& buffer):vertices_(nullptr), vertex_count_(0), vbo_(0)
{
	vertices_ = buffer.vertices_;
	vertex_count_ = buffer.vertex_count_;
	vbo_ = buffer.vbo_;
	buffer.vertices_ = nullptr;
	buffer.vertex_count_ = 0;
}

VertexBuffer& VertexBuffer::operator=(VertexBuffer&& buffer)
{
	// TODO: 在此处插入 return 语句
	if (this != &buffer) {
		ClearBuffer();
		vertices_ = buffer.vertices_;
		vertex_count_ = buffer.vertex_count_;
		vbo_ = buffer.vbo_;
		buffer.vertices_ = nullptr;
		buffer.vertex_count_ = 0;
	}
	return *this;
}

void VertexBuffer::SetVertexCount(int c)
{
	if (c <= 0) {
		std::cerr << "count <= 0" << std::endl;
		return;
	}
	if (this->vertices_ != nullptr) {
		delete this->vertices_;
		this->vertices_ = nullptr;
		this->vertex_count_ = 0;
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

void VertexBuffer::ClearBuffer()
{
	delete[] vertices_;
	this->vertex_count_ = 0;
}

Vertex& VertexBuffer::Get(int index) const
{
	return vertices_[index];
}

ElementBuffer::ElementBuffer():indices_buffer_(nullptr), length_(0)
{
}

ElementBuffer::ElementBuffer(const ElementBuffer& buffer)
{
	this->ebo = buffer.ebo;
	this->length_ = buffer.length_;
	this->indices_buffer_ = new unsigned int[buffer.length_];
	memcpy(this->indices_buffer_, buffer.indices_buffer_, sizeof(unsigned int) * buffer.length_);
}

// todo move ctor
// todo move assignment operator

ElementBuffer& ElementBuffer::operator=(const ElementBuffer& buffer)
{
	// TODO: 在此处插入 return 语句
	if (this != &buffer) {
		if (this->indices_buffer_ != nullptr) {
			ClearBuffer();
		}
		this->ebo = buffer.ebo;
		this->length_ = buffer.length_;
		this->indices_buffer_ = new unsigned int[buffer.length_];
		memcpy(this->indices_buffer_, buffer.indices_buffer_, sizeof(unsigned int) * buffer.length_);
	}
	return *this;
}

ElementBuffer::ElementBuffer(ElementBuffer&& buffer):indices_buffer_(nullptr), length_(0), ebo(0) {
	std::cout << "move element buffer ..." << std::endl;
	this->indices_buffer_ = buffer.indices_buffer_;
	this->length_ = buffer.length_;
	this->ebo = buffer.ebo;
	buffer.indices_buffer_ = nullptr;
	buffer.length_ = 0;
}

ElementBuffer& ElementBuffer::operator=(ElementBuffer&& buffer)
{
	// TODO: 在此处插入 return 语句
	if (this != &buffer) {
		ClearBuffer();
		this->indices_buffer_ = buffer.indices_buffer_;
		this->length_ = buffer.length_;
		this->ebo = buffer.ebo;
		buffer.indices_buffer_ = nullptr;
		buffer.length_ = 0;
	}
	return *this;
}

ElementBuffer::~ElementBuffer()
{
	if (indices_buffer_ != nullptr) {
		ClearBuffer();
	}
}

void ElementBuffer::SetBufferLength(int len)
{
	if (len < 1) {
		std::cerr << "Error: buffer length: " << len << std::endl;
	}
	if (this->indices_buffer_ != nullptr) {
		delete this->indices_buffer_;
		this->indices_buffer_ = nullptr;
		this->length_ = 0;
	}
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

void ElementBuffer::ClearBuffer()
{
	delete indices_buffer_;
	this->indices_buffer_ = nullptr;
	this->length_ = 0;
}

