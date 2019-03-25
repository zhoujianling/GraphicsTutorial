#pragma once

#include "linearmath.h"

class Camera
{

private:
	/** ���λ�� **/
	Vector3f mPos;

	/** ��������ĸ��� **/
	Vector3f mViewCenter;

	/** ���ͷ������ **/
	Vector3f mUp;

	// ��������� XoZ ƽ���ϵ��ƶ�
	bool movingLeft;

	bool movingRight;

	bool movingForwards;

	bool movingBackwards;

public:
	Camera();
	
	void Update(float deltaTime);

	void SetMovingLeft(const bool& l) { this->movingLeft = l; }

	void SetMovingRight(const bool& l) { this->movingRight = l; }

	void SetMovingForward(const bool& l) { this->movingForwards= l; }

	void SetMovingBackward(const bool& l) { this->movingBackwards = l; }

	Vector3f GetPosition() const { return this->mPos; }

	void Pitch(float angle);

	void Yaw(float angle);

	/**
	 * �����������Ƕ���ת�� �����λ�ò��䣬�൱��������ӵ�ı���
	 */
	void RotateView(float angle, float x, float y, float z);
};
