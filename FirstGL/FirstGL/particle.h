#pragma once

#include "ggl.h"
#include "linearmath.h"

class Particle
{
private:
	GLuint mTexture;

	// 粒子位置
	Vector3f mPosition;

	// 粒子大小
	float mHalfSize;

public:
	Particle();

	void Draw();

	GLuint getTexture() const { return mTexture; }

	Vector3f getPosition() const { return mPosition; }

	float getHalfSize() const { return mHalfSize; }
};

