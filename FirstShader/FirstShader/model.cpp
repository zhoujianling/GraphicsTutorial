#include "mesh.h"
#include "camera.h"
#include "model.h"
#include <algorithm>
using glm::mat4;
using glm::vec3;
using glm::identity;
using glm::identity;

Model::Model():model_matrix_(identity<mat4>())
{}

void Model::Draw(const Camera& camera) {
	for (auto& mesh : meshes_) {
		mesh.Draw(camera.GetViewMatrix(), camera.GetProjectionMatrix(), model_matrix_);
	}
}

void Model::Init() {
	for (auto& mesh : meshes_) {
		mesh.InitShader();
	}
}

Model& Model::MoveBy(glm::fvec3 world_position) {
	// model_matrix_
	model_matrix_ = glm::translate(model_matrix_, world_position);
	return *this;
}

Model& Model::RotateBy(glm::fvec3 axis, float radian) {
	// TODO: 在此处插入 return 语句
	// model_matrix_ = glm::rotate(model_matrix_, PI / 2.0f, { 0.0f, 1.0f, 0.0f });
	model_matrix_ = glm::rotate(model_matrix_, radian, axis);
	return *this;
}

void Model::ComputeBoundingBox()
{
	using namespace glm;
	using namespace std;
	
	fvec3 mmin(numeric_limits<float>::max(), numeric_limits<float>::max(), numeric_limits<float>::max());
	fvec3 mmax(numeric_limits<float>::min(), numeric_limits<float>::min(), numeric_limits<float>::min());
	for (auto& mesh : meshes_) {
		auto& vertex_buffer_ = mesh.GetVertexBuffer();
		for (size_t vert_i = 0; vert_i < vertex_buffer_.GetVerticesCount(); vert_i++) {
			mmin.x = std::min(mmin.x, vertex_buffer_.GetVertex()[vert_i].position[0]);
			mmin.y = std::min(mmin.y, vertex_buffer_.GetVertex()[vert_i].position[1]);
			mmin.z = std::min(mmin.z, vertex_buffer_.GetVertex()[vert_i].position[2]);
			mmax.x = std::max(mmax.x, vertex_buffer_.GetVertex()[vert_i].position[0]);
			mmax.y = std::max(mmax.y, vertex_buffer_.GetVertex()[vert_i].position[1]);
			mmax.z = std::max(mmax.z, vertex_buffer_.GetVertex()[vert_i].position[2]);
		}
	}
	bbox_.center_ = (mmax + mmin) * 0.5f;
	bbox_.extent_ = (mmax - mmin) * 0.5f;
	int a = 0;
}
