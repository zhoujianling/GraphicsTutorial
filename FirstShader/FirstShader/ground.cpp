#include "ground.h"


using glm::mat4;
using glm::identity;
using glm::identity;

void Ground::Init()
{
	//model_matrix_ = identity<mat4>();
	model_matrix_ = glm::translate(identity<mat4>(), {0.0f, 0.0f, -0.6f});
	//printGLMMatrix(model_matrix_);
	buffer_ = new VertexBuffer();
	buffer_->SetVertexCount(1600);
	for (int z = 0; z < 20; ++z)
	{
		float zStart = 100.0f - z * 10.0f;
		for (int x = 0; x < 20; ++x)
		{
			int offset = (x + z * 20) * 4;
			float xStart = x * 10.0f - 100.0f;
			buffer_->SetPosition(offset + 0, xStart, -1.0f, zStart);
			buffer_->SetPosition(offset + 1, xStart + 10.0f, -1.0f, zStart);
			buffer_->SetPosition(offset + 2, xStart, -1.0f, zStart - 10.0f);
			buffer_->SetPosition(offset + 3, xStart + 10.0f, -1.0f, zStart - 10.0f);

			buffer_->SetNormal(offset + 0, 0.0f, 1.0f, 0.0f);
			buffer_->SetNormal(offset + 1, 0.0f, 1.0f, 0.0f);
			buffer_->SetNormal(offset + 2, 0.0f, 1.0f, 0.0f);
			buffer_->SetNormal(offset + 3, 0.0f, 1.0f, 0.0f);

			float color = ((z % 2) ^ (x % 2)) ? 0.1f : 0.8f;
			buffer_->SetColor(offset + 0, color, color, color);
			buffer_->SetColor(offset + 1, color, color, color);
			buffer_->SetColor(offset + 2, color, color, color);
			buffer_->SetColor(offset + 3, color, color, color);
		}
	}
//	std::cerr << "sizeof(vertex):" << sizeof(Vertex) << " vertices number: " << vertex_buffer_->GetVerticesCount() << std::endl;
	//vbo = CreateBufferObject(GL_ARRAY_BUFFER, sizeof(Vertex) * vertex_buffer_->GetVerticesCount(), GL_STATIC_DRAW, vertex_buffer_->GetVertex());
	shader = new Shader;
	shader->Init("ground.vert", "ground.frag");
}

void Ground::Draw(glm::mat4& viewMatrix, glm::mat4& projectionMatrix)
{
	glEnable(GL_DEPTH_TEST);
	//glBindBuffer(GL_ARRAY_BUFFER, vbo);
	buffer_->Bind();
	shader->Bind(glm::value_ptr(model_matrix_), glm::value_ptr(viewMatrix), glm::value_ptr(projectionMatrix));
	for (int i = 0; i < 400; i ++)
	{
		glDrawArrays(GL_TRIANGLE_STRIP, i * 4, 4);
		//glDrawArrays(GL_QUADS, i * 4, 4);
	}
	// GLenum error = glGetError();
	// if (error != GL_NO_ERROR) {
	// 	printf("error: 0x%x\n", error);
	// }
	buffer_->UnBind();
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
