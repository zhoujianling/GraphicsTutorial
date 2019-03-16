#pragma once

#include "ggl.h"

class SkyBox final
{

private:
	GLuint mTextures[6];

	GLuint mFastDrawCall;

public:
	/**
	 * @param: 天空盒的6张图片所在的目录路径 
	 **/
	void Init(const char *imageDir);

	/** 绘制天空盒 **/
	void DrawCommand();

	void Draw();

};
