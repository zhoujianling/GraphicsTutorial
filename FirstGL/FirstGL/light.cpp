#include "scene.h"

#include "light.h"


void DrawModel2()
{
	glClearColor(0, 0, 0, 1.); // 擦除背景使用的颜色, 传入的参数为橡皮擦的颜色
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_QUADS); 
	glColor4ub(255, 255, 255, 255); glVertex3d(-0.0f, -0.0f, -2.5f); // 第一个点的坐标
	glColor4ub(255, 255, 255, 255); glVertex3d(-0.0f, +0.2f, -2.5f); // 第一个点的坐标
	glColor4ub(255, 255, 255, 255); glVertex3d(0.2f, +0.2f, -2.5f); // 第一个点的坐标
	glColor4ub(255, 255, 255, 255); glVertex3d(0.2f, 0.0f, -2.5f); // 第一个点的坐标
	glEnd(); 
}

void EnableDirectionLight()
{
	DrawModel2();
	glEnable(GL_LIGHTING); // 开启光照算法，白色的四边形会变黑，没有法线信息会导致变黑
	// OpenGL 里面有八盏灯，从 0 - 7
	glEnable(GL_LIGHT0); // 开启第一盏灯，
	// 光源坐标，是齐次坐标 (x, y, z, w) -> (x/w, y/w, z/w, 1)
	const GLfloat light_pos[] = {0.0f, 1.0f, 0.0f, 0.0f}; 
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos); // 设置 LIGHT0 的位置

}


void EnableDirectionAmbient()
{
	glClearColor(0, 0, 0, 1.); // 擦除背景使用的颜色, 传入的参数为橡皮擦的颜色
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_LIGHT0); // 开启第一盏灯，
	glEnable(GL_CULL_FACE); 
	const GLfloat lightPos[] = {0.0f, 1.0f, 0.0f, 0.0f}; 
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos); // 设置 LIGHT0 的位置

	const GLfloat white_color[] = {1.0f, 1.0f, 1.0f, 1.0f}; // 白色光
	const GLfloat black_color[] = {0.0f, 0.0f, 0.0f, 1.0f}; // 黑色光 
	const GLfloat ambient_mat[] = {0.07f, 0.07f, 0.07f, 1.0f}; // 物体表面材质的反射系数
	const GLfloat diffuse_mat[] = {0.4f, 0.4f, 0.4f, 1.0f}; // 物体表面材质的漫反射系数
	const GLfloat specular_mat[] = {0.9f, 0.9f, 0.9f, 1.0f}; // 物体表面材质的镜面反射系数

	glLightfv(GL_LIGHT0, GL_AMBIENT, white_color); // 设置环境光
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_mat); // 物体正面对环境光的反射系数

	glLightfv(GL_LIGHT0, GL_DIFFUSE, white_color); // 设置漫反射
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_mat); // 物体正面漫反射系数

	glLightfv(GL_LIGHT0, GL_SPECULAR, white_color); // 设置镜面反射
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular_mat); // 物体正面镜面反射系数
	
	DrawModel2();
}

Light::Light()
{
	
}


void Light::SetAmbientColor(float r, float g, float b, float a)
{
	GLfloat ambient_color[] = { r, g, b, a };
	glLightfv(light_identifier_, GL_AMBIENT, ambient_color);
}

void Light::SetDiffuseColor(float r, float g, float b, float a)
{
	GLfloat diffuse_color[] = { r, g, b, a };
	glLightfv(light_identifier_, GL_DIFFUSE, diffuse_color);
}

void Light::SetSpecularColor(float r, float g, float b, float a)
{
	GLfloat specular_color[] = { r, g, b, a };
	glLightfv(light_identifier_, GL_SPECULAR, specular_color);
}

void Light::Enable()
{
	glEnable(GL_LIGHTING);
	glEnable(light_identifier_);
}

DirectionLight::DirectionLight(GLenum light)
{
}

void DirectionLight::SetPosition(float x, float y, float z)
{
	GLfloat pos[] = { x, y, z, 0 };
	glLightfv(light_identifier_, GL_POSITION, pos);
}

PointLight::PointLight(GLenum light)
{
	light_identifier_ = light;
	position_[0] = 0.0;
	position_[1] = 0.0;
	position_[2] = 0.0;
}

void PointLight::SetPosition(GLfloat x, GLfloat y, GLfloat z)
{
	position_[0] = x;
	position_[1] = y;
	position_[2] = z;
}

void PointLight::SetConstantAttenuation(float v)
{
	glLightf(light_identifier_, GL_CONSTANT_ATTENUATION, v);
}

void PointLight::SetLinearAttenuation(float v)
{
	glLightf(light_identifier_, GL_LINEAR_ATTENUATION, v);
}

void PointLight::SetQuadricAttenuation(float v)
{
	glLightf(light_identifier_, GL_QUADRATIC_ATTENUATION, v);
}

void PointLight::Update(float x, float y, float z)
{
	GLfloat pos[] = {position_[0] - x, position_[1] - y, position_[2] - z, 1.00 };
	glLightfv(light_identifier_, GL_POSITION, pos);
}

SpotLight::SpotLight(GLenum light) : PointLight(light)
{
}

void SpotLight::SetDirection(float x, float y, float z)
{
	float dir[] = { x, y, z };
	glLightfv(light_identifier_, GL_SPOT_DIRECTION, dir);
}

void SpotLight::SetExponent(float v)
{
	glLightf(light_identifier_, GL_SPOT_EXPONENT, v);
}

void SpotLight::SetCufoff(float v)
{
	glLightf(light_identifier_, GL_SPOT_CUTOFF, v);
}



