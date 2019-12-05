#include "scene.h"
#include "ggl.h"
#include <Windows.h>
#include <cstdio>
#include "utils.h"
#include <iostream>
// // 指示链接 opengl32.lib 这个库, VS 默认带这个库
#pragma comment (lib, "glew32.lib") 
#pragma comment (lib, "glu32.lib") 
#pragma comment (lib, "opengl32.lib") 
#pragma comment (lib, "winmm.lib") 

POINT original_pos;

bool is_rotating_view = false;

Scene scene;

unsigned char* LoadFile(const char* file_path, int& file_size)
{
	unsigned char *file_content = nullptr;
	file_size = 0;

	FILE *fp = fopen(file_path, "rb");
	if (fp == nullptr)
	{
		std::cerr << "Warning: Fail to open file: " << file_path << std::endl;
		return file_content;
	}
	fseek(fp, 0, SEEK_END); // 移动文件指针到尾部
	int nlen = ftell(fp);
	if (nlen > 0)
	{
		rewind(fp); // 移到头部
		file_content = new unsigned char[nlen + 1];
		fread(file_content, sizeof(unsigned char), nlen, fp);
		file_content[nlen] = 0;
		file_size = nlen;
	}
	fclose(fp);
	return file_content;
}

/**
 * @param msg: 1 表示用户关闭了窗口， 2 表示用户用户拖拽了窗口
 * @param wParam: 额外的信息
 */
LRESULT CALLBACK GLWindowProc(HWND hwn, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_KEYDOWN:
		scene.OnKeyDown(wParam);
		return 0;
	case WM_KEYUP:
		scene.OnKeyUp(wParam);
		return 0;
	case WM_RBUTTONDOWN:
		GetCursorPos(&original_pos);
		ShowCursor(false);
		is_rotating_view = true;
		return 0;
	case WM_RBUTTONUP:
		SetCursorPos(original_pos.x, original_pos.y);
		ShowCursor(true);
		is_rotating_view = false;
		return 0;
	case WM_MOUSEMOVE:
		if (is_rotating_view)
		{
			POINT current_pos;
			GetCursorPos(&current_pos);
			const int delta_x = current_pos.x - original_pos.x;
			const int delta_y = current_pos.y - original_pos.y;
			scene.OnMouseMove(delta_x, delta_y);
			SetCursorPos(original_pos.x, original_pos.y);
		}
		return 0;
	case WM_CLOSE:
		// 窗口关闭，发送 QUIT 消息
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwn, msg, wParam, lParam);
}

void SetWindowContent(WNDCLASSEX *windowClass, HINSTANCE hInstance)
{
	windowClass->cbClsExtra = 0;
	windowClass->cbSize = sizeof(WNDCLASSEX);
	windowClass->cbWndExtra = 0;
	windowClass->hbrBackground = nullptr;
	windowClass->hCursor = LoadCursor(nullptr, IDC_ARROW);
	windowClass->hIcon = nullptr;
	windowClass->hIconSm = nullptr;
	windowClass->hInstance = hInstance;
	windowClass->lpfnWndProc = GLWindowProc; // 用户操作处理回调函数指针
	windowClass->lpszClassName = "GLWindow"; // ClassName 不能乱改?
	windowClass->lpszMenuName = nullptr;
	windowClass->style = CS_VREDRAW | CS_HREDRAW; // 垂直重绘 + 水平重绘

}

/**
 * 创建 OpenGL 渲染环境
 *
 */
HDC SetOpenGlEnv(HWND hwnd)
{
	// ==================
	const auto hdc = GetDC(hwnd); // 获取设备上下文
	PIXELFORMATDESCRIPTOR pfd; // 像素格式配置类
	memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
	pfd.nVersion = 1;
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.cColorBits = 32; // RGBA 各占8bit
	pfd.cDepthBits = 24; // 深度缓冲区
	pfd.cStencilBits = 8; // 蒙版缓冲区
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	const int pixel_format = ChoosePixelFormat(hdc, &pfd); // windows 帮我们选择 pixelFormat
	SetPixelFormat(hdc, pixel_format, &pfd);
	HGLRC rc = wglCreateContext(hdc);// handle GL render context 创建渲染环境
	wglMakeCurrent(hdc, rc); // 使渲染环境生效
	glewInit();
	if (glewInit()) {
		std::cerr 
		<< "Unable to initialize GLEW ... exiting" 
		<< std::endl; 
		exit(EXIT_FAILURE);
	}
	std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
	scene.SetViewPortSize(800.0f, 600.0f);

	scene.Init();

	return hdc;
}


/**
 * windows 窗口程序的入口函数
 */
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, LPSTR cmdLine, int nShowCommand) {
	char temp[2048];
	GetSystemDirectory(temp, 2048);
	printf("system directory: %s\n", temp);
	// 注册窗口
	WNDCLASSEX window_class; // 这是一个结构体, 描述窗口信息
	SetWindowContent(&window_class, hInstance);
	const auto atom = RegisterClassEx(&window_class); // 注册窗口
		
	RECT rect;
	rect.left = 0;
	rect.right = 800;
	rect.top = 0;
	rect.bottom = 600;
	// 这个函数保证视口的rect 为 800 x 600，加上标题栏等烂七八糟的，重新得到 rect 的大小
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, 0);
	const int window_width = rect.right - rect.left;
	const int window_height = rect.bottom - rect.top;
	
	if (atom == 0) {
		MessageBox(nullptr, "notice", "Error", MB_OK);
		return 0;
	}
	
	HWND hwnd = CreateWindowEx(NULL, "GLWindow", "GL", WS_OVERLAPPEDWINDOW,
		100, 100, window_width, window_height,
		nullptr, nullptr, hInstance, nullptr);
	const auto hdc = SetOpenGlEnv(hwnd); // 初始化 OpenGL 渲染环境
	ShowWindow(hwnd, SW_SHOW); //
	UpdateWindow(hwnd); // 画面可能是脏的，需要重新刷新一下
	
	MSG msg;
	// 自己处理事件， 让程序不退出
	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				break;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		scene.UpdateScene();
		scene.Draw();
		SwapBuffers(hdc); // 交换 OpenGl 的缓冲区，把后面的缓冲区交换到前面来
	}
	return 0;
}

