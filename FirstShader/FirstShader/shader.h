#pragma once

#include "ggl.h"

/**
 * 对于一个要画的物体，我们通常要写它的 VertexShader 和 FragmentShader
 * 代码的读取、编译、链接，可以进一步封装
 */
class Shader
{
private:
	GLuint programId;

	GLint positionLocation;

	GLint colorLocation;

	GLint texcoordLocation;

	GLint normalLocation;

	GLint modelMatrixLocation;
	GLint viewMatrixLocation;
	GLint projectionMatrixLocation;

public:
	int GetPositionLocation() const { return positionLocation; }

	int GetColorLocation() const { return colorLocation; }

	int GetTexcoordLocation() const { return texcoordLocation; }

	int GetNormalLocation() const { return normalLocation; }
		
	void Init(const std::string& vs, const std::string& fs);

	void Bind(float *M, float *V, float *P);
};
