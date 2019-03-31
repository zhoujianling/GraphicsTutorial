#pragma once

#include "utils.h"
#include "vertex.h"
// #include "model.h"

/** 读取ply格式的模型文件 **/
void LoadPly(std::string modelPath, VertexBuffer *model, ElementBuffer *element_buffer);
//
// /** 读取obj格式的模型文件 **/
// void LoadObj(std::string modelPath, TriMesh *model);

void LoadRGBImage(std::string imagePath, unsigned char *&rgbData, int& width, int &height);
