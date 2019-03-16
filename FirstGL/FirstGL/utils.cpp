#include "utils.h"

unsigned char* DecodeBMP(unsigned char* bmpData, int& width, int& height)
{
	if (0x4D42 == *reinterpret_cast<unsigned short*>(bmpData))
	{
		auto pixelDataOffset = *reinterpret_cast<int*>(bmpData + 10);
		width = *reinterpret_cast<int*>(bmpData + 18);
		height = *reinterpret_cast<int*>(bmpData + 22);
		auto bmpImgData = bmpData + pixelDataOffset;
		// BGR -> RGB
		for (int i = 0; i < width * height * 3; i += 3)
		{
			unsigned char temp = bmpImgData[i];
			bmpImgData[i] = bmpImgData[i + 2];
			bmpImgData[i + 2] = temp;
		}
		return bmpImgData;
	}
	return nullptr;
}

GLuint CreateTexture2D(unsigned char* pixelData, int width, int height, GLenum type)
{
	GLuint texture;
	glGenTextures(1, &texture); // 申请 1 个纹理地址
	glBindTexture(GL_TEXTURE_2D, texture); // 2d 纹理， 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // 纹理过小怎么办，线性插值
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // 线性插值
	// 以下指定过滤方式， 第二个参数还可以为 GL_REPEAT, UV 若大于 1.0， 则重复搬运纹理
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP); // UV坐标超过1.0怎么办， 去纹理边界（1.0）处取
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP); // UV坐标超过1.0怎么办 
	// 将内存里的图片数据拷贝到显存里
	// 第二个参数 0， 是指 mipmap 的 level
	// border 必须为 0
	glTexImage2D(GL_TEXTURE_2D, 0, type, width, height, 0, type, GL_UNSIGNED_BYTE, pixelData);
	glBindTexture(GL_TEXTURE_2D, 0); // 设置当前纹理为0号纹理，类似当前矩阵的概念？
	return texture;
}

GLuint CreateTexture2DFromBmp(const char *bmpPath)
{
	int nFileSize = 0;
	unsigned char *bmpFileData = LoadFile(bmpPath, nFileSize);
	if (bmpFileData == nullptr)
	{
		fprintf(stderr, "Error, cannot open file.\n");
		return 0; // 出错，返回 0 号黑色纹理单元
	}
	int width = 0, height = 0;
	unsigned char *bmpImageData = DecodeBMP(bmpFileData, width, height);
	if (width <= 0 || height <= 0)
	{
		fprintf(stderr, "Error, cannot decode image.\n");
		delete bmpFileData;
		return 0;
	}

	GLuint textureID = CreateTexture2D(bmpImageData, width, height, GL_RGB);
	delete bmpFileData;
	return textureID;
}

/**
 * 将所有绘制指令（glBegin(xxxx)) 打包进显示列表
 */
GLuint CreateDisplayList(std::function<void()> foo)
{
	GLuint displayList = glGenLists(1); // 声明 OpenGL 的显示列表
	glNewList(displayList, GL_COMPILE);
	foo();
	glEndList();
	return displayList;
}
