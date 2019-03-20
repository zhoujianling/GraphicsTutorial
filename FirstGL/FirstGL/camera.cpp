#include "camera.h"
#include "ggl.h"
#include "iostream"

/** 初始化为OpenGL 默认视口矩阵的状态 **/
Camera::Camera() :
mPos(0.0f, 0.0f, 0.0f),
mViewCenter(0.0f, 0.0f, -1.0f),
mUp(0.0f, 1.0f, 0.0f),
movingLeft(false),
movingRight(false),
movingForwards(false),
movingBackwards(false)
{
}

void Camera::Update(float deltaTime)
{
	float moveSpeed = 2.0f;
	if (movingLeft)
	{
		float delta = deltaTime * moveSpeed;
		mPos.position[0] = mPos.position[0] - delta;
		mViewCenter.position[0] = mViewCenter.position[0] - delta;
	}
	if (movingRight)
	{
		float delta = deltaTime * moveSpeed;
		mPos.position[0] = mPos.position[0] + delta;
		mViewCenter.position[0] = mViewCenter.position[0] + delta;
	}
	if (movingForwards)
	{
		float delta = deltaTime * moveSpeed;
		std::cout << "deltaForward: " << delta << std::endl;
		mPos.position[2] = mPos.position[2] - delta;
		mViewCenter.position[2] = mViewCenter.position[2] - delta;
	}
	if (movingBackwards)
	{
		float delta = deltaTime * moveSpeed;
		std::cout << "deltaBackwards: " << delta << std::endl;
		mPos.position[2] = mPos.position[2] + delta;
		mViewCenter.position[2] = mViewCenter.position[2] + delta;
	}
	glLoadIdentity();
	gluLookAt(mPos.position[0], mPos.position[1], mPos.position[2],
		mViewCenter.position[0], mViewCenter.position[1], mViewCenter.position[2],
		mUp.position[0], mUp.position[1], mUp.position[2]);
}


