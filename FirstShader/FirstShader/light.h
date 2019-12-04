#pragma once

#include "ggl.h"

class Light {
protected:
	// 用于确定这个光源来自 GL_LIGHT0 - GL_LIGHT7 中的哪一个
	GLenum light_identifier_;

	Light();

public:

	// 环境光
	void SetAmbientColor(float r, float g, float b, float a);

	// 漫反射
	void SetDiffuseColor(float r, float g, float b, float a);

	// 镜面反射
	void SetSpecularColor(float r, float g, float b, float a);

	void Enable();

};

/**
 * 方向光的齐次坐标第四项为0，导致处于无穷远处
 * 方向光*不会衰减*
 ***/
class DirectionLight : public Light
{
public:

	DirectionLight(GLenum light);

	/**
	 * 方向光的光源坐标仅用于确定光的方向，而非光源位置
	 */
	void SetPosition(float x, float y, float z);
};


/**
 * 点光源的能量会衰减，越远光线越暗
 */
class PointLight : public Light
{
private:
	float position_[3];

public:
	PointLight(GLenum light);

	void SetPosition(GLfloat x, GLfloat y, GLfloat z);

	// 设置常数衰减系数
	void SetConstantAttenuation(float v);

	// 设置线性衰减系数
	void SetLinearAttenuation(float v);

	// 设置二次方衰减系数
	void SetQuadricAttenuation(float v);

	/**
	 * 参数是摄像机的位置
	 */
	void Update(float x, float y, float z);
};

// 聚光灯
class SpotLight : public PointLight
{
public:
	SpotLight(GLenum light);

	// 聚光灯方向
	void SetDirection(float x, float y, float z);

	// 聚光度
	void SetExponent(float v);

	// 照射范围
	void SetCufoff(float v);
};
