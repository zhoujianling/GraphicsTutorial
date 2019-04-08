#pragma once

#include "ggl.h"
#include "linearmath.h"

class Particle
{
private:
	GLuint texture_;

	// 粒子位置
	Vector3f position_;

	// 粒子大小
	float half_size_;

public:
	Particle();

	void Draw();

	GLuint GetTexture() const { return texture_; }

	Vector3f GetPosition() const { return position_; }

	float GetHalfSize() const { return half_size_; }
};

