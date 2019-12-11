#include "wireframe.h"
#include "io.h"
#include <limits>
#include <unordered_set>

using glm::mat4;
using glm::vec3;
using glm::identity;
using glm::identity;



WireFrame::WireFrame() {
}

WireFrame::~WireFrame()
{}


void WireFrame::InitShader() {
	shader.Init("wireframe.vert", "wireframe.frag");

	shader.SetVector4("U_LightPosition", 0.0f, 1.0f, 1.0f, 1.0f);
	shader.SetVector4("U_LightAmbient", 1.0f, 0.0f, 0.0f, 1.0f);
	shader.SetVector4("U_LightAmbientMaterial", 0.1f, 0.1f, 0.1f, 1.0f);
	shader.SetVector4("U_LightDiffuse", 1.0f, 1.0f, 1.0f, 1.0f);
	shader.SetVector4("U_LightDiffuseMaterial", 0.6f, 0.6f, 0.6f, 1.0f);
	shader.SetVector4("U_LightSpecular", 1.0f, 1.0f, 1.0f, 1.0f);
	shader.SetVector4("U_LightSpecularMaterial", 1.0f, 1.0f, 1.0f, 1.0f);
	shader.SetVector4("U_CameraPosition", 0.0f, 0.0f, 0.0f, 1.0f);
	shader.SetVector4("U_LightOpt", 32.0f, 0.0f, 0.0f, 1.0f);
}

void WireFrame::Draw(glm::mat4 view_matrix, glm::mat4 projection_matrix, glm::mat4 model_matrix) {
	glEnable(GL_DEPTH_TEST);
	vertex_buffer_.Bind();
	element_buffer_.Bind();

	auto ptr = glm::value_ptr((view_matrix));
	//shader.SetVector4("U_CameraPosition", -ptr[12], -ptr[13], -ptr[14], 1.0);
	shader.Bind(glm::value_ptr(model_matrix), glm::value_ptr(view_matrix), glm::value_ptr(projection_matrix));
	auto it = glm::inverseTranspose(model_matrix);
	auto it_location = glGetUniformLocation(shader.GetProgramId(), "IT_ModelMatrix");
	glUniformMatrix4fv(it_location, 1, GL_FALSE, glm::value_ptr(it));

	//glDrawElements(GL_TRIANGLES, vertex_buffer_->GetVerticesCount(), GL_UNSIGNED_INT, nullptr);
	
	glDrawElements(GL_LINES, element_buffer_.GetLength(), GL_UNSIGNED_INT, (void*)0);

	vertex_buffer_.UnBind();
	element_buffer_.UnBind();
}

void WireFrame::SetAmbientMaterial(float r, float g, float b, float a)
{
	shader.SetVector4("U_AmbientMaterial", r, g, b, a);
}

void WireFrame::SetSpecularMaterial(float r, float g, float b, float a)
{
	shader.SetVector4("U_SpecularMaterial", r, g, b, a);
}

void WireFrame::SetTexture(const std::string& texture_image_path)
{
	shader.SetTexture("U_Texture", texture_image_path);
}

void WireFrame::SetDiffuseMaterial(float r, float g, float b, float a)
{
	shader.SetVector4("U_DiffuseMaterial", r, g, b, a);
}


