#include "camera.h"
#include "Include/glm/gtx/rotate_vector.hpp"
#include <iostream>
#include "utils.h"

using glm::identity;
using glm::rotate;
using glm::translate;
using glm::scale;
using glm::perspective;
using glm::mat4;
using glm::vec3;
using glm::vec4;

Camera::Camera():
view_matrix_(identity<mat4>()),
projection_matrix_(identity<mat4>()),
position_({0.0f, 0.0f, 0.0f}),
look_at_(0.0f, 0.0f, -1.0f),
up_(0.0f, 1.0f, 0.0f)
{
}

void Camera::Init(float ratio)
{
	view_matrix_ = glm::lookAt<float, glm::defaultp>(position_, look_at_, up_);
	projection_matrix_ = perspective(PI / 3.0F, ratio, 0.1f, 1000.0f);
}

void Camera::Translate(const glm::vec3& delta)
{
	// std::cout << "x: " << delta[0] << " y: " << delta[1] << " z: " << delta[2] << std::endl;
	position_ += delta;
	look_at_ += delta;
	view_matrix_ = glm::lookAt<float, glm::defaultp>(position_, look_at_, up_);
	//PrintGLMMatrix(view_matrix_);
}

void Camera::Yaw(float angle)
{
	Rotate(angle, up_);
}

void Camera::Pitch(float angle)
{
	Rotate(angle, glm::normalize(RightHandDirection()));
}
 
void Camera::Rotate(const float angle, const glm::vec3& axis)
{
	//view_matrix_ = rotate(view_matrix_, angle, axis);
	auto direction_look_at = vec3(look_at_[0] - position_[0], look_at_[1] - position_[1], look_at_[2] - position_[2]);
	direction_look_at = rotate(direction_look_at, angle, axis);
	//up_ = rotate(up_, angle, axis); // 我去，不能转 up_ 向量噢
	look_at_ = vec3(position_[0] + direction_look_at[0], position_[1] + direction_look_at[1], position_[2] + direction_look_at[2]);
	view_matrix_ = glm::lookAt<float, glm::defaultp>(position_, look_at_, up_);
}
