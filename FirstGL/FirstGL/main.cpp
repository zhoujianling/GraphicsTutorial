//#include <tchar.h>
#include <windows.h>
#include <gl/GL.h>
// 指示链接 opengl32.lib 这个库, VS 默认带这个库
#pragma comment (lib, "opengl32.lib") 
//#include <iostream>

//using std::cout;
//using std::endl;

/**
 * @param msg: 1 表示用户关闭了窗口， 2 表示用户用户拖拽了窗口
 * @param wParam: 额外的信息 
 */
LRESULT CALLBACK GLWindowProc(HWND hwn, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CLOSE:
		// 窗口关闭，发送 QUIT 消息
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwn, msg, wParam, lParam);
}

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, LPSTR cmdLine, int nShowCommand) {
	// 注册窗口
	WNDCLASSEX windowClass; // 这是一个结构体
	windowClass.cbClsExtra = 0;
	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.cbWndExtra = 0;
	windowClass.hbrBackground = nullptr;
	windowClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
	windowClass.hIcon = nullptr;
	windowClass.hIconSm = nullptr;
	windowClass.hInstance = hInstance;
	windowClass.lpfnWndProc = GLWindowProc; // 用户操作处理回调函数指针
	windowClass.lpszClassName = "GLWindow"; // ClassName 不能乱改?
	windowClass.lpszMenuName = nullptr;
	windowClass.style = CS_VREDRAW | CS_HREDRAW; // 垂直重绘 + 水平重绘
	// 执行注册
	auto atom = RegisterClassEx(&windowClass);
	RECT rect;
	rect.left = 0;
	rect.right = 800;
	rect.top = 0;
	rect.bottom = 600;
	// 这个函数保证视口的rect 为 800 x 600，加上标题栏等烂七八糟的，重新得到 rect 的大小
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, 0);
	const int windowWidth = rect.right - rect.left;
	const int windowHeight = rect.bottom - rect.top;

	if (atom == 0) {
		MessageBox(nullptr, "notice", "Error", MB_OK);
		return 0;
	}
	HWND hwnd = CreateWindowEx(NULL, "GLWindow", "GL", WS_OVERLAPPEDWINDOW, 
		100, 100, windowWidth, windowHeight, 
		nullptr, nullptr, hInstance, nullptr);
	// ==================
	// 创建 OpenGL 渲染环境
	HDC hdc = GetDC((hwnd)); // 获取设备上下文
	PIXELFORMATDESCRIPTOR pfd; // 像素格式配置类
	memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
	pfd.nVersion = 1;
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.cColorBits = 32; // RGBA 各占8bit
	pfd.cDepthBits = 24; // 深度缓冲区
	pfd.cStencilBits = 8; // 蒙版缓冲区
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	int pixelFormat = ChoosePixelFormat(hdc, &pfd); // windows 帮我们选择 pixelFormat
	SetPixelFormat(hdc, pixelFormat, &pfd);
	HGLRC rc = wglCreateContext(hdc);// handle GL render context 创建渲染环境
	wglMakeCurrent(hdc, rc); // 使渲染环境生效
	// ====================
	ShowWindow(hwnd, SW_SHOW); //
	UpdateWindow(hwnd); // 画面可能是脏的，需要重新刷新一下
	MSG msg;
	// 自己处理事件， 让程序不退出
	while (true)
	{
		// if (PeekMessage(&msg, hwnd, 0, 0, PM_REMOVE))
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				break;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return 0;
}

