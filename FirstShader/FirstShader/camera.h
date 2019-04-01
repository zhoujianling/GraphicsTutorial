#pragma once
#include "ggl.h"

class Camera
{
private:
	glm::mat4 view_matrix_;

	glm::mat4 projection_matrix_;

	glm::vec3 position_;

	/** 看向的点 **/
	glm::vec3 look_at_;

	/** 头顶的方向 **/
	glm::vec3 up_;

public:
	Camera();

	void Init(float ratio);

	/** 在 x0z 平面上位移 **/
	void Translate(const glm::vec3& displacement);

	void Yaw(float angle);
	
	void Pitch(float angle);

	/**
	 * @param angle: 旋转的**弧度值**
	 * @param axis: 旋转轴
	 */
	void Rotate(const float angle, const glm::vec3& axis);

	/**
	 * 传值即可
	 */
	glm::mat4 GetViewMatrix() const { return view_matrix_; }

	glm::mat4 GetProjectionMatrix() const { return projection_matrix_; }

	glm::vec3 ForwardDirection() const { return glm::vec3(
		look_at_[0] - position_[0],
		look_at_[1] - position_[1],
		look_at_[2] - position_[2]
	);}

	glm::vec3 UpDirection() const { return up_; }

	glm::vec3 RightHandDirection() const { return glm::cross(ForwardDirection(), up_); }
};
