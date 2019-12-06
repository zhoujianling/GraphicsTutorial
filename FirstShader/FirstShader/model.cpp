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
	glEnable(GL_STENCIL_TEST);
	// 蒙版默认初始化为 0
	glClearStencil(0);
	glStencilMask(0xFF);
	glStencilFunc(GL_NOTEQUAL, 0x1, 0xFF); // 当和 0XFF 做 and运算的结果 NOTEQUAL 1时，通过蒙版测试
	// glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE); // ???
	// glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
	for (auto& mesh : meshes_) {
		mesh.DrawShadow(camera.GetViewMatrix(), camera.GetProjectionMatrix(), model_matrix_);
	//glStencilMask(0x00);
	}
	// 关闭蒙版写入
	glStencilMask(0x00);

	glDisable(GL_STENCIL_TEST);

	for (auto& mesh : meshes_) {
		mesh.Draw(camera.GetViewMatrix(), camera.GetProjectionMatrix(), model_matrix_);
	}
	bbox_wire_.Draw(camera.GetViewMatrix(), camera.GetProjectionMatrix(), model_matrix_);
}

void Model::Init() {
	ComputeBoundingBox();
	bbox_.ToWireframe(bbox_wire_.GetVertexBuffer(), bbox_wire_.GetElementBuffer());

	for (auto& mesh : meshes_) {
		mesh.InitShader();
	}
	bbox_wire_.InitShader();
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

Model& Model::ScaleBy(float ratio) {
	// TODO: 在此处插入 return 语句
	model_matrix_ = glm::scale(model_matrix_, { ratio, ratio, ratio });
	return *this;
}

void Model::ComputeBoundingBox() {
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
