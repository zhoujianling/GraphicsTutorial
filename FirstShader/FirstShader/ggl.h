#pragma once
#define _CRT_SECURE_NO_DEPRECATE
#include <windows.h>
//#define GL_GLEXT_PROTOTYPES

// Windows 不提供 glew.h，自己下载，拷贝头文件和lib文件到 VC++ 的include 目录和 lib目录下
// 需要链接 glew32.lib
#include "GL/glew.h"
#include "GL/GL.h"

// Windows 默认提供 "gl/GL.h", 需要链接 opengl32.lib
// 该头文件缺失一些方法和枚举值的定义，故倾向使用 glew.h
#include <gl/GLU.h> // 工具类

//#define GL_CLAMP_TO_EDGE 0X812F

#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <sstream>
#include <vector>
#include <functional>

