#pragma once

#include "ggl.h"
#include "camera.h"

class SkyBox final
{

private:
	GLuint textures_[6];

	GLuint fast_draw_call_;

	Camera* curr_camera_;

public:
	SkyBox();

	/**
	 * @param: 天空盒的6张图片所在的目录路径 
	 **/
	void Init(const char *image_dir, Camera *camera);

	/** 绘制天空盒 **/
	void DrawCommand();

	void Draw();

};
