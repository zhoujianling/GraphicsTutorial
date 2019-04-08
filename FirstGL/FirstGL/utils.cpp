#include "utils.h"
#include "io.h"
#include "iostream"

unsigned char* DecodeBMP(unsigned char* bmp_data, int& width, int& height)
{
	if (0x4D42 == *reinterpret_cast<unsigned short*>(bmp_data))
	{
		const auto pixel_data_offset = *reinterpret_cast<int*>(bmp_data + 10);
		width = *reinterpret_cast<int*>(bmp_data + 18);
		height = *reinterpret_cast<int*>(bmp_data + 22);
		const auto bmp_img_data = bmp_data + pixel_data_offset;
		// BGR -> RGB
		for (int i = 0; i < width * height * 3; i += 3)
		{
			unsigned char temp = bmp_img_data[i];
			bmp_img_data[i] = bmp_img_data[i + 2];
			bmp_img_data[i + 2] = temp;
		}
		return bmp_img_data;
	}
	return nullptr;
}

GLuint CreateTexture2D(unsigned char* pixel_data, int width, int height, GLenum type)
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
	glTexImage2D(GL_TEXTURE_2D, 0, type, width, height, 0, type, GL_UNSIGNED_BYTE, pixel_data);
	glBindTexture(GL_TEXTURE_2D, 0); // 设置当前纹理为0号纹理，类似当前矩阵的概念？
	return texture;
}

GLuint CreateTexture2DFromBmp(const char *bmp_Path)
{
	int n_file_size = 0;
	auto bmp_file_data = LoadFile(bmp_Path, n_file_size);
	if (bmp_file_data == nullptr)
	{
		fprintf(stderr, "Error, cannot open file.\n");
		return 0; // 出错，返回 0 号黑色纹理单元
	}
	int width = 0, height = 0;
	unsigned char *bmp_image_data = nullptr;
	LoadRGBImage(bmp_Path, bmp_image_data, width, height);
	//= DecodeBMP(bmpFileData, width, height);
	if (width <= 0 || height <= 0)
	{
		fprintf(stderr, "Error, cannot decode image.\n");
		delete bmp_file_data;
		return 0;
	}

	const GLuint texture_id = CreateTexture2D(bmp_image_data, width, height, GL_RGB);
//	delete bmpFileData;
	delete bmp_image_data;
	return texture_id;
}

/**
 * 将所有绘制指令（glBegin(xxxx)) 打包进显示列表
 */
GLuint CreateDisplayList(std::function<void()> foo)
{
	const GLuint display_list = glGenLists(1); // 声明 OpenGL 的显示列表
	glNewList(display_list, GL_COMPILE);
	foo();
	glEndList();
	return display_list;
}

// 代码生成 size x size 的纹理
GLuint CreateProcedureTexture(int size)
{
	const auto image_data = new unsigned char[size * size * 4];
	for (int x = 0; x < size; x ++)
	{
		for (int y = 0; y < size; y ++)
		{
			int i = (x + y * size) * 4;
			image_data[i + 0] = 255;
			image_data[i + 1] = 255;
			image_data[i + 2] = 255;
			image_data[i + 3] = 255;
		}
	}
	GLuint texture = CreateTexture2D(image_data, size, size, GL_RGBA);
	delete[] image_data;
	return texture;
}

float GetFrameTime()
{
	static unsigned long latest_time = 0;
	static unsigned long time_since_boot = 0;
	time_since_boot = timeGetTime();
	const auto frame_time = latest_time == 0 ? 0 : time_since_boot - latest_time;
	latest_time = time_since_boot;
	return static_cast<float>(frame_time) / 1000.0f;
}

