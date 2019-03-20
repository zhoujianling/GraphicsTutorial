#pragma once

struct Vector3f
{
	float position[3];

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
