#include "camera.h"
#include "ggl.h"
#include "iostream"

/** 初始化为OpenGL 默认视口矩阵的状态 **/
Camera::Camera() :
position_(0.0f, 0.0f, 0.0f),
view_center_(0.0f, 0.0f, -1.0f),
up_(0.0f, 1.0f, 0.0f),
is_moving_left_(false),
is_moving_right_(false),
is_moving_forwards_(false),
is_moving_backwards_(false)
{
}

void Camera::Update(float delta_time)
{
	float move_speed = 2.0f;
	Vector3f forward_direction = view_center_ - position_;
	forward_direction.Normalize();
	Vector3f right_direction = forward_direction.Cross(up_);
	right_direction.Normalize();

	if (is_moving_left_)
	{
		const auto& delta = right_direction * delta_time * move_speed;
		position_ = position_ - delta;
		view_center_ = view_center_ - delta;
	}
	if (is_moving_right_)
	{
		const auto& delta = right_direction * delta_time * move_speed;
		position_ = position_ + delta;
		view_center_ = view_center_ + delta;
	}
	if (is_moving_forwards_)
	{
		const auto& delta = forward_direction * delta_time * move_speed;
		std::cout << "x: " << delta.v1 << " y: " << delta.v2 << " z: " << delta.v3 << std::endl;
		position_ = position_ + delta;
		view_center_ = view_center_ + delta;
	}
	if (is_moving_backwards_)
	{
		const auto& delta = forward_direction * delta_time * move_speed;
		std::cout << "x: " << delta.v1 << " y: " << delta.v2 << " z: " << delta.v3 << std::endl;
		position_ = position_ - delta;
		view_center_ = view_center_ - delta;
	}
	glLoadIdentity();
	gluLookAt(position_.v1, position_.v2, position_.v3,
		view_center_.v1, view_center_.v2, view_center_.v3,
		up_.v1, up_.v2, up_.v3);
}

void Camera::Pitch(float angle)
{
	auto view_direction = view_center_ - position_;
	view_direction.Normalize();
	auto right_direction = view_direction.Cross(up_);
	right_direction.Normalize();
	RotateView(angle, right_direction.v1, right_direction.v2, right_direction.v3);
}

void Camera::Yaw(float angle)
{
	RotateView(angle, up_.v1, up_.v2, up_.v3);
}

/**
 * 绕 (x,y,z) 旋转 angle 角度
 */
void Camera::RotateView(float angle, float x, float y, float z)
{
	Vector3f view_direction = view_center_ - position_;

	float C = cosf(angle);
	float S = sinf(angle);
	// 绕任意轴的旋转矩阵
	Matrix33f matrix33(
		{x * x * (1 - C) + C, x * y * (1 - C) - z * S, x * z * (1 - C) + y * S,
	y * x * (1 - C) + z * S, y * y * (1 - C) + C, y * z * (1 - C) - x * S,
	z * x * (1 - C) - y * S, z * y * (1 - C) + x * S, z * z * (1 - C) + C});
	const auto& new_direction = matrix33 * view_direction;
	view_center_ = position_ + new_direction;
}



