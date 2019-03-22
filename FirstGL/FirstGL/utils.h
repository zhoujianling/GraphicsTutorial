#pragma once

#include "ggl.h"

/** 加载文件内容到内存 **/
unsigned char* LoadFile(const char* filePath, int& fileSize);

/** 解码 BMP 图片 **/
unsigned char* DecodeBMP(unsigned char* bmpData, int& width, int& height);

/** 
 * 创建二维纹理 
 * @param type: 像素类型
 * @return 返回纹理对象的标识符
 **/
GLuint CreateTexture2D(unsigned char* pixelData, int with, int height, GLenum type);

GLuint CreateTexture2DFromBmp(const char *bmpPath);

GLuint CreateDisplayList(std::function<void()> foo);

/** 生成程序纹理 **/
GLuint CreateProcedureTexture(int size);

/** 统计渲染每一帧的时间，需要链接 winmm.lib **/
float GetFrameTime();

