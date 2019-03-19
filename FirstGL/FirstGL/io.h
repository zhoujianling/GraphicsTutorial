#pragma once

#include "utils.h"
#include "model.h"

/** 读取ply格式的模型文件 **/
void LoadPly(std::string modelPath, Model *model);

/** 读取obj格式的模型文件 **/
void LoadObj(std::string modelPath, Model *model);

void LoadRGBImage(std::string imagePath, unsigned char *&rgbData, int& width, int &height);
