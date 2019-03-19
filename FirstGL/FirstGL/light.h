#pragma once

#include "ggl.h"

class Light
{
protected:
	// 用于确定这个光源来自 GL_LIGHT0 - GL_LIGHT7 中的哪一个
	GLenum mLightIdentifier;

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
 * 方向光不会衰减
 ***/
class DirectionLight: public Light
{
public:

	DirectionLight(GLenum light);

	/**
	 * 方向光的光源坐标仅用于确定光的方向，而非光源位置
	 */
	void SetPosition(float x, float y, float z);
};
