#pragma once

#include "linearmath.h"

class Camera
{

private:
	/** 相机位置 **/
	Vector3f position_;

	/** 相机看向哪个点 **/
	Vector3f view_center_;

	/** 相机头顶向量 **/
	Vector3f up_;

	// 控制相机在 XoZ 平面上的移动
	bool is_moving_left_;

	bool is_moving_right_;

	bool is_moving_forwards_;

	bool is_moving_backwards_;

public:
	Camera();
	
	void Update(float delta_time);

	void SetMovingLeft(const bool& l) { this->is_moving_left_ = l; }

	void SetMovingRight(const bool& l) { this->is_moving_right_ = l; }

	void SetMovingForward(const bool& l) { this->is_moving_forwards_= l; }

	void SetMovingBackward(const bool& l) { this->is_moving_backwards_ = l; }

	Vector3f GetPosition() const { return this->position_; }

	void Pitch(float angle);

	void Yaw(float angle);

	/**
	 * 让摄像机任意角度旋转， 相机的位置不变，相当于相机的视点改变了
	 */
	void RotateView(float angle, float x, float y, float z);
};

