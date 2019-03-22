#pragma once

struct Vector3f
{
	float v1;

	float v2;

	float v3;

	Vector3f();

	Vector3f(float x, float y, float z);

	Vector3f mul(const Vector3f&);

	Vector3f cross(const Vector3f&);

	Vector3f add(const Vector3f&);

	Vector3f sub(const Vector3f&);

	Vector3f scale(float);

	Vector3f operator* (const Vector3f&);

	Vector3f operator* (float);

	//Vector3f operator*= (double);

	Vector3f operator- (const Vector3f&);

	Vector3f operator+ (const Vector3f&);

	/** 向量长度 **/
	float length() const;

	/** 向量归一化 **/
	void normalize();
};

struct Matrix33f
{
	float vals[9];

#ifdef DECLARE_M33
#define v11 vals[0]
#define v12 vals[1]
#define v13 vals[2]
#define v21 vals[3]
#define v22 vals[4]
#define v23 vals[5]
#define v31 vals[6]
#define v32 vals[7]
#define v33 vals[8]
#endif

	Matrix33f(float val11, float val12, float val13, float val21, float val22, float val23,
		float val31, float val32, float val33);

	Matrix33f(float array[9]);

	Vector3f mul(const Vector3f& vector);
	
	Vector3f operator* (const Vector3f&);
};


//
//struct Vector4f
//{
//	float position[4];
//
//	Vector4f();
//
//	Vector4f(float x, float y, float z, float d);
//
//	Vector3f mul(const Vector3f&);
//
//	Vector3f cross(const Vector3f&);
//
//	Vector3f add(const Vector3f&);
//
//	Vector3f sub(const Vector3f&);
//
//	Vector3f scale(double);
//
//	Vector3f operator* (const Vector3f&);
//
//	Vector3f operator* (double);
//
//	//Vector3f operator*= (double);
//
//	Vector3f operator- (const Vector3f&);
//
//	Vector3f operator+ (const Vector3f&);
//
//	//Vector3f operator= (const Vector3f&);
//	
//};
