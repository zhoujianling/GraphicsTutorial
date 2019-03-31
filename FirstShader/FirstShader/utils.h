#pragma once

#include "ggl.h"
#include "Include/glm/gtx/string_cast.hpp"
#include "iostream"

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


/**
 * 编译 shader
 * @param shaderType: 是 VertexShader 还是 FragmentShader
 * @param shaderCode: d
 */
GLuint CompileShader(GLenum shaderType, const char *shaderCode);

/**
 * 链接 vertexShader 和 fragmentShader
 * @param vsShader: vertex shader
 * @param fsShader: fragment shader
 */
GLuint CreateShaderProgram(GLuint vsShader, GLuint fsShader);

/**
 * 创建 Buffer Object
 * @param bufferType 缓冲区类型
 * @param size 缓冲区的大小
 * @param usage static_draw 还是 dynamic_draw
 * @param data 具体的数据
 */
GLuint CreateBufferObject(GLenum bufferType, GLsizeiptr size, GLenum usage, void *data = nullptr);

template<typename T>
void printGLMMatrix(T const& m, const std::string  prompt = "")
{
	// 列向量转行向量，方便观察
	const auto tm = glm::transpose(m);
	std::string str = glm::to_string(tm);
	std::string log = prompt;
	//log += "???";
	int prevIndex = 0;
	for (int i = 0; i < str.length(); i ++)
	{
		if (str[i] == '(' && prevIndex == 0) {
			log += std::string(str.begin() + prevIndex, str.begin() + i + 1);
			log += "\n";
			prevIndex = i + 1;
		} else if (i + 1 < str.length() && str[i] == ')' && str[i + 1] == ',')
		{
			log += std::string(str.begin() + prevIndex, str.begin() + i + 2);
			log += "\n";
			prevIndex = i + 2;
		}
	}
	log += std::string(str.begin() + prevIndex,str.end());
	std::cout << log << std::endl;
}
