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
	const GLfloat lightPos[] = {0.0f, 1.0f, 0.0f, 0.0f}; 
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos); // 设置 LIGHT0 的位置

}


void EnableDirectionAmbient()
{
	glClearColor(0, 0, 0, 1.); // 擦除背景使用的颜色, 传入的参数为橡皮擦的颜色
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_LIGHT0); // 开启第一盏灯，
	glEnable(GL_CULL_FACE); 
	const GLfloat lightPos[] = {0.0f, 1.0f, 0.0f, 0.0f}; 
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos); // 设置 LIGHT0 的位置

	const GLfloat whiteColor[] = {1.0f, 1.0f, 1.0f, 1.0f}; // 白色光
	const GLfloat blackColor[] = {0.0f, 0.0f, 0.0f, 1.0f}; // 黑色光 
	const GLfloat ambientMat[] = {0.07f, 0.07f, 0.07f, 1.0f}; // 物体表面材质的反射系数
	const GLfloat diffuseMat[] = {0.4f, 0.4f, 0.4f, 1.0f}; // 物体表面材质的漫反射系数
	const GLfloat specularMat[] = {0.9f, 0.9f, 0.9f, 1.0f}; // 物体表面材质的镜面反射系数

	glLightfv(GL_LIGHT0, GL_AMBIENT, whiteColor); // 设置环境光
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambientMat); // 物体正面对环境光的反射系数

	glLightfv(GL_LIGHT0, GL_DIFFUSE, whiteColor); // 设置漫反射
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseMat); // 物体正面漫反射系数

	glLightfv(GL_LIGHT0, GL_SPECULAR, whiteColor); // 设置镜面反射
	glMaterialfv(GL_FRONT, GL_SPECULAR, specularMat); // 物体正面镜面反射系数
	
	DrawModel2();
}

Light::Light()
{
	
}


void Light::SetAmbientColor(float r, float g, float b, float a)
{
	GLfloat ambientColor[] = { r, g, b, a };
	glLightfv(mLightIdentifier, GL_AMBIENT, ambientColor);
}

void Light::SetDiffuseColor(float r, float g, float b, float a)
{
	GLfloat diffuseColor[] = { r, g, b, a };
	glLightfv(mLightIdentifier, GL_DIFFUSE, diffuseColor);
}

void Light::SetSpecularColor(float r, float g, float b, float a)
{
	int ab = 0;
	int c = ab;
	GLfloat specularColor[] = { r, g, b, a };
	glLightfv(mLightIdentifier, GL_SPECULAR, specularColor);
}

void Light::Enable()
{
	glEnable(GL_LIGHTING);
	glEnable(mLightIdentifier);
}

DirectionLight::DirectionLight(GLenum light)
{
}

void DirectionLight::SetPosition(float x, float y, float z)
{
	GLfloat pos[] = { x, y, z, 0 };
	glLightfv(mLightIdentifier, GL_POSITION, pos);
}

PointLight::PointLight(GLenum light)
{
	mLightIdentifier = light;
}

void PointLight::SetPosition(GLfloat x, GLfloat y, GLfloat z)
{
	GLfloat pos[] = { x, y, z, 1.00 };
	glLightfv(mLightIdentifier, GL_POSITION, pos);
}

void PointLight::SetConstantAttenuation(float v)
{
	glLightf(mLightIdentifier, GL_CONSTANT_ATTENUATION, v);
}

void PointLight::SetLinearAttenuation(float v)
{
	glLightf(mLightIdentifier, GL_LINEAR_ATTENUATION, v);
}

void PointLight::SetQuadricAttenuation(float v)
{
	glLightf(mLightIdentifier, GL_QUADRATIC_ATTENUATION, v);
}

SpotLight::SpotLight(GLenum light) : PointLight(light)
{
}

void SpotLight::SetDirection(float x, float y, float z)
{
	float dir[] = { x, y, z };
	glLightfv(mLightIdentifier, GL_SPOT_DIRECTION, dir);
}

void SpotLight::SetExponent(float v)
{
	glLightf(mLightIdentifier, GL_SPOT_EXPONENT, v);
}

void SpotLight::SetCufoff(float v)
{
	glLightf(mLightIdentifier, GL_SPOT_CUTOFF, v);
}



