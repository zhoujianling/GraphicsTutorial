#pragma once
#include "ggl.h"


class A
{
public:
	template<class T> T function_m() { };
};

template<typename  U> void function_n(U argument)
{
	char object_x = argument.template function_m<char>();  // ill-formed
}

void SetViewPortSize(float width, float height);

void Init();

void Draw();

// 键盘按下事件
void OnKeyDown(char code);

// 键盘弹起事件
void OnKeyUp(char code);

void OnMouseMove(float deltaX, float deltaY);
