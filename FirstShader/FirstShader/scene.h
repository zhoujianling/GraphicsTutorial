#pragma once
#include "ggl.h"


void SetViewPortSize(float width, float height);

void Init();

void UpdateScene();

void Draw();

// 键盘按下事件
void OnKeyDown(char code);

// 键盘弹起事件
void OnKeyUp(char code);

void OnMouseMove(float delta_x, float delta_y);
