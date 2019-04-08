#include "mesh.h"
#include "io.h"
using glm::mat4;
using glm::vec3;
using glm::identity;
using glm::identity;

TriMesh::TriMesh()
{
	model_matrix_ = glm::translate(identity<mat4>(), { 0.0f, 0.0f, -1.9f });
	model_matrix_ = glm::rotate(model_matrix_, PI / 2.0f, { 0.0f, 1.0f, 0.0f });
	glTranslatef(0.0f, 0.0f, -3.0f);
	//glRotated(90.0, 0, 1.0, 0);
}

void TriMesh::Init(const std::string model_path)
{
	vertex_buffer_ = new VertexBuffer();
	element_buffer_ = new ElementBuffer();
	LoadPly(model_path, vertex_buffer_, element_buffer_);

	shader = new Shader;
	shader->Init("trimesh.vert", "trimesh.frag");

	shader->SetVector4("U_LightPosition", 0.0f, 1.0f, 1.0f, 1.0f);
	shader->SetVector4("U_LightAmbient", 1.0f, 0.0f, 0.0f, 1.0f);
	shader->SetVector4("U_LightAmbientMaterial", 0.1f, 0.1f, 0.1f, 1.0f);
	shader->SetVector4("U_LightDiffuse", 1.0f, 1.0f, 1.0f, 1.0f);
	shader->SetVector4("U_LightDiffuseMaterial", 0.6f, 0.6f, 0.6f, 1.0f);
}

void TriMesh::Draw(glm::mat4 view_matrix, glm::mat4 projection_matrix)
{
	glEnable(GL_DEPTH_TEST);
	vertex_buffer_->Bind();
	element_buffer_->Bind();
	shader->Bind(glm::value_ptr(model_matrix_), glm::value_ptr(view_matrix), glm::value_ptr(projection_matrix));
	auto it = glm::inverseTranspose(model_matrix_);
	auto it_location = glGetUniformLocation(shader->GetProgramId(), "IT_ModelMatrix");
	glUniformMatrix4fv(it_location, 1, GL_FALSE, glm::value_ptr(it));
	// 
	//glDrawElements(GL_TRIANGLES, vertex_buffer_->GetVerticesCount(), GL_UNSIGNED_INT, nullptr);
	
	glDrawElements(GL_TRIANGLES, element_buffer_->GetLength(), GL_UNSIGNED_INT, (void*)0);
	//glDrawArrays(GL_TRIANGLES, 0, vertex_buffer_->GetVerticesCount());
	//
	vertex_buffer_->UnBind();
	element_buffer_->UnBind();
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
}
