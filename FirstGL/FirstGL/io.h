#pragma once

#include "utils.h"
#include "model.h"

/** 读取ply格式的模型文件 **/
void LoadPly(std::string model_path, Model *model);

/** 读取obj格式的模型文件 **/
void LoadObj(std::string model_path, Model *model);

void LoadRGBImage(std::string image_path, unsigned char *&rgb_data, int& width, int &height);
