#include "mesh.h"
#include "io.h"
#include <limits>
using glm::mat4;
using glm::vec3;
using glm::identity;
using glm::identity;

using namespace zjl;

TriMesh::TriMesh():is_transparent_(false)
{
}

TriMesh::~TriMesh()
{
}

void TriMesh::InitGeometry(const VertexBuffer& vb, const ElementBuffer& eb) {
	this->vertex_buffer_ = vb;
	this->element_buffer_ = eb;

}


void TriMesh::InitShader() {
	shader.Init("trimesh.vert", "trimesh.frag");
	// shader.Init("model_gooch.vert", "model_gooch.frag");

	shader.SetVector4("U_LightPosition", 0.0f, 2.5f, 1.5f, 1.0f);
	shader.SetVector4("U_LightAmbient", 1.0f, 1.0f, 1.0f, 1.0f);
	shader.SetVector4("U_LightAmbientMaterial", 0.05f, 0.05f, 0.05f, 1.0f);
	shader.SetVector4("U_LightDiffuse", 1.0f, 1.0f, 1.0f, 1.0f);
	shader.SetVector4("U_LightDiffuseMaterial", 0.6f, 0.6f, 0.6f, 1.0f);
	shader.SetVector4("U_LightSpecular", 1.0f, 1.0f, 1.0f, 1.0f);
	shader.SetVector4("U_LightSpecularMaterial", 0.9f, 0.9f, 0.9f, 1.0f);
	shader.SetVector4("U_CameraPosition", 0.0f, 0.0f, 0.0f, 1.0f);
	shader.SetVector4("U_LightOpt", 32.0f, 0.0f, 0.0f, 1.0f);

	// std::cerr << "Debug: texture_color_name: " << this->texture_color_name_ << std::endl;
	if (! this->texture_color_name_.empty()) {
		shader.SetTexture("U_Texture", this->texture_color_name_);
	}

	// ###############################################
	shadow_shader_.Init("hard_shadow.vert", "hard_shadow.frag");

	shadow_shader_.SetVector4("U_LightPosition", 0.0f, 2.5f, 2.5f, 1.0f);
	shadow_shader_.SetVector4("U_PlaneOpt", 0.0f, 1.0f, 0.0f, 0.99f);
}

void TriMesh::InitGeometry(const std::string model_path) {
	
	LoadModel(model_path, vertex_buffer_, element_buffer_);

	shader.Init("trimesh.vert", "trimesh.frag");
	// shader.Init("model_gooch.vert", "model_gooch.frag");

}

void zjl::TriMesh::DrawShadow(glm::mat4 view_matrix, glm::mat4 projection_matrix, 
	glm::mat4 model_matrix) {
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	vertex_buffer_.Bind();
	element_buffer_.Bind();

	//auto ptr = glm::value_ptr((view_matrix));
	//shader.SetVector4("U_CameraPosition", -ptr[12], -ptr[13], -ptr[14], 1.0);
	shadow_shader_.Bind(glm::value_ptr(model_matrix), glm::value_ptr(view_matrix), glm::value_ptr(projection_matrix));
	auto it = glm::inverseTranspose(model_matrix);
	auto it_location = glGetUniformLocation(shadow_shader_.GetProgramId(), "IT_ModelMatrix");
	glUniformMatrix4fv(it_location, 1, GL_FALSE, glm::value_ptr(it));

	//glDrawElements(GL_TRIANGLES, vertex_buffer_->GetVerticesCount(), GL_UNSIGNED_INT, nullptr);
	
	glDrawElements(GL_TRIANGLES, element_buffer_.GetLength(), GL_UNSIGNED_INT, (void*)0);

	vertex_buffer_.UnBind();
	element_buffer_.UnBind();
}


void TriMesh::Draw(glm::mat4 view_matrix, glm::mat4 projection_matrix, glm::mat4 model_matrix) {
	glEnable(GL_DEPTH_TEST);
	if (is_transparent_) {
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	vertex_buffer_.Bind();
	element_buffer_.Bind();

	auto ptr = glm::value_ptr((view_matrix));
	shader.SetVector4("U_CameraPosition", -ptr[12], -ptr[13], -ptr[14], 1.0);
	shader.Bind(glm::value_ptr(model_matrix), glm::value_ptr(view_matrix), glm::value_ptr(projection_matrix));
	auto it = glm::inverseTranspose(model_matrix);
	auto it_location = glGetUniformLocation(shader.GetProgramId(), "IT_ModelMatrix");
	glUniformMatrix4fv(it_location, 1, GL_FALSE, glm::value_ptr(it));

	//glDrawElements(GL_TRIANGLES, vertex_buffer_.GetVerticesCount(), GL_UNSIGNED_INT, nullptr);
	
	glDrawElements(GL_TRIANGLES, element_buffer_.GetLength(), GL_UNSIGNED_INT, (void*)0);
	//glDrawArrays(GL_TRIANGLES, 0, vertex_buffer_.GetVerticesCount());
	//
	vertex_buffer_.UnBind();
	element_buffer_.UnBind();
	glDisable(GL_BLEND);

	//glPolygonMode(GL_FRONT, GL_FILL);
	//glPolygonMode(GL_BACK, GL_FILL);
}

void TriMesh::SetAmbientMaterial(float r, float g, float b, float a)
{
	shader.SetVector4("U_AmbientMaterial", r, g, b, a);
}

void TriMesh::SetSpecularMaterial(float r, float g, float b, float a)
{
	shader.SetVector4("U_SpecularMaterial", r, g, b, a);
}

//void TriMesh::SetTexture(const std::string& texture_image_path)
//{
//	shader.SetTexture("U_Texture", texture_image_path);
//}

void TriMesh::SetDiffuseMaterial(float r, float g, float b, float a)
{
	shader.SetVector4("U_DiffuseMaterial", r, g, b, a);
}
