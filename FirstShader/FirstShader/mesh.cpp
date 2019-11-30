#include "mesh.h"
#include "io.h"
#include <limits>
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

TriMesh::~TriMesh()
{
}

void TriMesh::ComputeBoundingBox()
{
	using namespace glm;
	using namespace std;
	
	fvec3 mmin(numeric_limits<float>::max(), numeric_limits<float>::max(), numeric_limits<float>::max());
	fvec3 mmax(numeric_limits<float>::min(), numeric_limits<float>::min(), numeric_limits<float>::min());
	for (size_t vert_i = 0; vert_i < vertex_buffer_.GetVerticesCount(); vert_i++) {
		mmin.x = min(mmin.x, vertex_buffer_.GetVertex()[vert_i].position[0]);
		mmin.y = min(mmin.y, vertex_buffer_.GetVertex()[vert_i].position[1]);
		mmin.z = min(mmin.z, vertex_buffer_.GetVertex()[vert_i].position[2]);
		mmax.x = max(mmax.x, vertex_buffer_.GetVertex()[vert_i].position[0]);
		mmax.y = max(mmax.y, vertex_buffer_.GetVertex()[vert_i].position[1]);
		mmax.z = max(mmax.z, vertex_buffer_.GetVertex()[vert_i].position[2]);
	}
	bbox_.center_ = (mmax + mmin) * 0.5f;
	bbox_.extent_ = (mmax - mmin) * 0.5f;
	int a = 0;
}

void TriMesh::Init(const std::string model_path)
{
	//vertex_buffer_ = new VertexBuffer();
	//element_buffer_ = new ElementBuffer();
	LoadPly(model_path, &vertex_buffer_, &element_buffer_);

	// shader.Init("trimesh.vert", "trimesh.frag");
	shader.Init("model_gooch.vert", "model_gooch.frag");

	shader.SetVector4("U_LightPosition", 0.0f, 1.0f, 1.0f, 1.0f);
	shader.SetVector4("U_LightAmbient", 1.0f, 0.0f, 0.0f, 1.0f);
	shader.SetVector4("U_LightAmbientMaterial", 0.1f, 0.1f, 0.1f, 1.0f);
	shader.SetVector4("U_LightDiffuse", 1.0f, 1.0f, 1.0f, 1.0f);
	shader.SetVector4("U_LightDiffuseMaterial", 0.6f, 0.6f, 0.6f, 1.0f);
	shader.SetVector4("U_LightSpecular", 1.0f, 1.0f, 1.0f, 1.0f);
	shader.SetVector4("U_LightSpecularMaterial", 1.0f, 1.0f, 1.0f, 1.0f);
	shader.SetVector4("U_CameraPosition", 0.0f, 0.0f, 0.0f, 1.0f);
	shader.SetVector4("U_LightOpt", 32.0f, 0.0f, 0.0f, 1.0f);

	this->ComputeBoundingBox();

}

void TriMesh::Draw(glm::mat4 view_matrix, glm::mat4 projection_matrix)
{
	glEnable(GL_DEPTH_TEST);
	vertex_buffer_.Bind();
	element_buffer_.Bind();

	auto ptr = glm::value_ptr((view_matrix));
	shader.SetVector4("U_CameraPosition", -ptr[12], -ptr[13], -ptr[14], 1.0);
	shader.Bind(glm::value_ptr(model_matrix_), glm::value_ptr(view_matrix), glm::value_ptr(projection_matrix));
	auto it = glm::inverseTranspose(model_matrix_);
	auto it_location = glGetUniformLocation(shader.GetProgramId(), "IT_ModelMatrix");
	glUniformMatrix4fv(it_location, 1, GL_FALSE, glm::value_ptr(it));

	//glDrawElements(GL_TRIANGLES, vertex_buffer_.GetVerticesCount(), GL_UNSIGNED_INT, nullptr);
	
	glDrawElements(GL_TRIANGLES, element_buffer_.GetLength(), GL_UNSIGNED_INT, (void*)0);
	//glDrawArrays(GL_TRIANGLES, 0, vertex_buffer_.GetVerticesCount());
	//
	vertex_buffer_.UnBind();
	element_buffer_.UnBind();
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void TriMesh::SetAmbientMaterial(float r, float g, float b, float a)
{
	shader.SetVector4("U_AmbientMaterial", r, g, b, a);
}

void TriMesh::SetSpecularMaterial(float r, float g, float b, float a)
{
	shader.SetVector4("U_SpecularMaterial", r, g, b, a);
}

void TriMesh::SetTexture(const std::string& texture_image_path)
{
	shader.SetTexture("U_Texture", texture_image_path);
}

void TriMesh::SetDiffuseMaterial(float r, float g, float b, float a)
{
	shader.SetVector4("U_DiffuseMaterial", r, g, b, a);
}
