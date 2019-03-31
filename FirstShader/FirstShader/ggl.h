#pragma once
#define _CRT_SECURE_NO_DEPRECATE
#include <windows.h>
//#define GL_GLEXT_PROTOTYPES

// 需要链接 glew32.lib
#include "glew.h"
//#include "GL/GL.h"

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
#define PI 3.1415926f
#include "Include/glm/glm.hpp"
#include "Include/glm/ext.hpp"

