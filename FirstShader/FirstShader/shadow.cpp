#include "shadow.h"
using glm::mat4;
using glm::vec3;
using glm::identity;
using glm::identity;

Shadow::Shadow(const VertexBuffer buffer, const ElementBuffer edge_buffer)
	:model_matrix_(identity<mat4>()){
	vertex_buffer_ = buffer;
	element_buffer_ = edge_buffer;

	// shader.Init("trimesh.vert", "trimesh.frag");
	shader.Init("hard_shadow.vert", "hard_shadow.frag");

	shader.SetVector4("U_LightPosition", 0.0f, 2.5f, 2.5f, 1.0f);
	shader.SetVector4("U_PlaneOpt", 0.0f, 1.0f, 0.0f, 0.99f);
	//shader.SetVector4("U_LightAmbient", 1.0f, 0.0f, 0.0f, 1.0f);
	//shader.SetVector4("U_LightAmbientMaterial", 0.1f, 0.1f, 0.1f, 1.0f);
	//shader.SetVector4("U_LightDiffuse", 1.0f, 1.0f, 1.0f, 1.0f);
	//shader.SetVector4("U_LightDiffuseMaterial", 0.6f, 0.6f, 0.6f, 1.0f);
	//shader.SetVector4("U_LightSpecular", 1.0f, 1.0f, 1.0f, 1.0f);
	//shader.SetVector4("U_LightSpecularMaterial", 1.0f, 1.0f, 1.0f, 1.0f);
	//shader.SetVector4("U_CameraPosition", 0.0f, 0.0f, 0.0f, 1.0f);
	// shader.SetVector4("U_LightOpt", 32.0f, 0.0f, 0.0f, 1.0f);
}

Shadow::~Shadow() {
}

void Shadow::Draw(glm::mat4 view_matrix, glm::mat4 projection_matrix) {
	glEnable(GL_DEPTH_TEST);
	vertex_buffer_.Bind();
	element_buffer_.Bind();

	auto ptr = glm::value_ptr((view_matrix));
	//shader.SetVector4("U_CameraPosition", -ptr[12], -ptr[13], -ptr[14], 1.0);
	shader.Bind(glm::value_ptr(model_matrix_), glm::value_ptr(view_matrix), glm::value_ptr(projection_matrix));
	auto it = glm::inverseTranspose(model_matrix_);
	auto it_location = glGetUniformLocation(shader.GetProgramId(), "IT_ModelMatrix");
	glUniformMatrix4fv(it_location, 1, GL_FALSE, glm::value_ptr(it));

	//glDrawElements(GL_TRIANGLES, vertex_buffer_->GetVerticesCount(), GL_UNSIGNED_INT, nullptr);
	
	glDrawElements(GL_TRIANGLES, element_buffer_.GetLength(), GL_UNSIGNED_INT, (void*)0);
	//glDrawArrays(GL_TRIANGLES, 0, vertex_buffer_->GetVerticesCount());
	//
	vertex_buffer_.UnBind();
	element_buffer_.UnBind();
	//glBindBuffer(GL_ARRAY_BUFFER, 0);

}
