#include "mesh.h"
#include "io.h"
#include <limits>
using glm::mat4;
using glm::vec3;
using glm::identity;
using glm::identity;


TriMesh::TriMesh():shader(nullptr), m_bbox_shader(nullptr)
{
	model_matrix_ = glm::translate(identity<mat4>(), { 0.0f, 0.0f, -1.9f });
	model_matrix_ = glm::rotate(model_matrix_, PI / 2.0f, { 0.0f, 1.0f, 0.0f });
	glTranslatef(0.0f, 0.0f, -3.0f);
	//glRotated(90.0, 0, 1.0, 0);
}

TriMesh::~TriMesh()
{
	if (shader != nullptr) delete shader;
}

void TriMesh::ComputeBoundingBox()
{
	if (vertex_buffer_ == nullptr) return;
	using namespace glm;
	using namespace std;
	
	fvec3 mmin(numeric_limits<float>::max(), numeric_limits<float>::max(), numeric_limits<float>::max());
	fvec3 mmax(numeric_limits<float>::min(), numeric_limits<float>::min(), numeric_limits<float>::min());
	for (size_t vert_i = 0; vert_i < vertex_buffer_->GetVerticesCount(); vert_i++) {
		mmin[0] = min(mmin[0], vertex_buffer_->GetVertex()[vert_i].position[0]);
		mmin[1] = min(mmin[1], vertex_buffer_->GetVertex()[vert_i].position[1]);
		mmin[2] = min(mmin[2], vertex_buffer_->GetVertex()[vert_i].position[2]);
		mmax[0] = max(mmax[0], vertex_buffer_->GetVertex()[vert_i].position[0]);
		mmax[1] = max(mmax[1], vertex_buffer_->GetVertex()[vert_i].position[1]);
		mmax[2] = max(mmax[2], vertex_buffer_->GetVertex()[vert_i].position[2]);
	}
	bbox_.m_center = (mmax + mmin) * 0.5f;
	bbox_.m_extent = (mmax - mmin) * 0.5f;
}

void TriMesh::Init(const std::string model_path)
{
	vertex_buffer_ = new VertexBuffer();
	element_buffer_ = new ElementBuffer();
	LoadPly(model_path, vertex_buffer_, element_buffer_);

	if (shader != nullptr) delete shader;
	shader = new Shader;
	// shader->Init("trimesh.vert", "trimesh.frag");
	shader->Init("model_gooch.vert", "model_gooch.frag");

	shader->SetVector4("U_LightPosition", 0.0f, 1.0f, 1.0f, 1.0f);
	shader->SetVector4("U_LightAmbient", 1.0f, 0.0f, 0.0f, 1.0f);
	shader->SetVector4("U_LightAmbientMaterial", 0.1f, 0.1f, 0.1f, 1.0f);
	shader->SetVector4("U_LightDiffuse", 1.0f, 1.0f, 1.0f, 1.0f);
	shader->SetVector4("U_LightDiffuseMaterial", 0.6f, 0.6f, 0.6f, 1.0f);
	shader->SetVector4("U_LightSpecular", 1.0f, 1.0f, 1.0f, 1.0f);
	shader->SetVector4("U_LightSpecularMaterial", 1.0f, 1.0f, 1.0f, 1.0f);
	shader->SetVector4("U_CameraPosition", 0.0f, 0.0f, 0.0f, 1.0f);
	shader->SetVector4("U_LightOpt", 32.0f, 0.0f, 0.0f, 1.0f);

	this->ComputeBoundingBox();
	if (m_bbox_shader != nullptr) delete m_bbox_shader;
	m_bbox_shader = new Shader();
	m_bbox_shader->Init("wireframe.vert", "wireframe.frag");

}

void TriMesh::Draw(glm::mat4 view_matrix, glm::mat4 projection_matrix)
{
	glEnable(GL_DEPTH_TEST);
	vertex_buffer_->Bind();
	element_buffer_->Bind();

	auto ptr = glm::value_ptr((view_matrix));
	shader->SetVector4("U_CameraPosition", -ptr[12], -ptr[13], -ptr[14], 1.0);
	shader->Bind(glm::value_ptr(model_matrix_), glm::value_ptr(view_matrix), glm::value_ptr(projection_matrix));
	auto it = glm::inverseTranspose(model_matrix_);
	auto it_location = glGetUniformLocation(shader->GetProgramId(), "IT_ModelMatrix");
	glUniformMatrix4fv(it_location, 1, GL_FALSE, glm::value_ptr(it));

	//glDrawElements(GL_TRIANGLES, vertex_buffer_->GetVerticesCount(), GL_UNSIGNED_INT, nullptr);
	
	glDrawElements(GL_TRIANGLES, element_buffer_->GetLength(), GL_UNSIGNED_INT, (void*)0);
	//glDrawArrays(GL_TRIANGLES, 0, vertex_buffer_->GetVerticesCount());
	//
	vertex_buffer_->UnBind();
	element_buffer_->UnBind();
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void TriMesh::SetAmbientMaterial(float r, float g, float b, float a)
{
	shader->SetVector4("U_AmbientMaterial", r, g, b, a);
}

void TriMesh::SetSpecularMaterial(float r, float g, float b, float a)
{
	shader->SetVector4("U_SpecularMaterial", r, g, b, a);
}

void TriMesh::SetTexture(const std::string& texture_image_path)
{
	shader->SetTexture("U_Texture", texture_image_path);
}

void TriMesh::SetDiffuseMaterial(float r, float g, float b, float a)
{
	shader->SetVector4("U_DiffuseMaterial", r, g, b, a);
}
