#include "ggl.h"
#include "scene.h"
#include <Windows.h>
#include "utils.h"
// 指示链接 opengl32.lib 这个库, VS 默认带这个库
#pragma comment (lib, "opengl32.lib") 
//#pragma comment (lib, "glew32.lib") 
#pragma comment (lib, "glu32.lib") 
#pragma comment (lib, "winmm.lib") 

POINT original_pos;

bool is_rotating_view = false;

unsigned char* LoadFile(const char* file_path, int& file_Size)
{
	unsigned char *file_content = nullptr;
	file_Size = 0;

	FILE *fp = fopen(file_path, "rb");
	if (fp == nullptr)
	{
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
		file_Size = nlen;
	}
	fclose(fp);
	return file_content;
}

/**
 * @param msg: 1 表示用户关闭了窗口， 2 表示用户用户拖拽了窗口
 * @param w_param: 额外的信息 
 */
LRESULT CALLBACK GLWindowProc(HWND hwn, UINT msg, WPARAM w_param, LPARAM l_param)
{
	switch (msg)
	{
	case WM_KEYDOWN:
		OnKeyDown(w_param);
		return 0;
	case WM_KEYUP:
		OnKeyUp(w_param);
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
			OnMouseMove(delta_x, delta_y);
			SetCursorPos(original_pos.x, original_pos.y);
		}
			return 0;
	case WM_CLOSE:
		// 窗口关闭，发送 QUIT 消息
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwn, msg, w_param, l_param);
}

void SetWindowContent(WNDCLASSEX *window_class, HINSTANCE h_instance)
{
	window_class -> cbClsExtra = 0;
	window_class -> cbSize = sizeof(WNDCLASSEX);
	window_class -> cbWndExtra = 0;
	window_class -> hbrBackground = nullptr;
	window_class -> hCursor = LoadCursor(nullptr, IDC_ARROW);
	window_class -> hIcon = nullptr;
	window_class -> hIconSm = nullptr;
	window_class -> hInstance = h_instance;
	window_class -> lpfnWndProc = GLWindowProc; // 用户操作处理回调函数指针
	window_class -> lpszClassName = "GLWindow"; // ClassName 不能乱改?
	window_class -> lpszMenuName = nullptr;
	window_class -> style = CS_VREDRAW | CS_HREDRAW; // 垂直重绘 + 水平重绘
	
}

/**
 * 创建 OpenGL 渲染环境
 *
 */
HDC SetOpenGlEnv(HWND hwnd)
{
	// ==================
	auto hdc = GetDC(hwnd); // 获取设备上下文
	PIXELFORMATDESCRIPTOR pfd; // 像素格式配置类
	memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
	pfd.nVersion = 1;
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.cColorBits = 32; // RGBA 各占8bit
	pfd.cDepthBits = 24; // 深度缓冲区
	pfd.cStencilBits = 8; // 蒙版缓冲区
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	int pixel_format = ChoosePixelFormat(hdc, &pfd); // windows 帮我们选择 pixelFormat
	SetPixelFormat(hdc, pixel_format, &pfd);
	const auto rc = wglCreateContext(hdc);// handle GL render context 创建渲染环境
	wglMakeCurrent(hdc, rc); // 使渲染环境生效
	Init();
	
	return hdc;
}


/**
 * windows 窗口程序的入口函数
 */
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, LPSTR cmdLine, int nShowCommand) {
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
		Draw();
		SwapBuffers(hdc); // 交换 OpenGl 的缓冲区，把后面的缓冲区交换到前面来
	}
	return 0;
}

