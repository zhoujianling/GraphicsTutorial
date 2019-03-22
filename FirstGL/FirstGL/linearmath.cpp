#define DECLARE_M33
#include "linearmath.h"
#include <cmath>

Vector3f::Vector3f(): 
v1(0), v2(0), v3(0)
{
}

Vector3f::Vector3f(float x, float y, float z): 
v1(x), v2(y), v3(z)
{
}

Vector3f Vector3f::mul(const Vector3f& b)
{
	Vector3f r;
	r.v1 = v1 * b.v1 + v1 * b.v1;
	r.v2 = v2 * b.v2 + v2 * b.v2;
	r.v3 = v3 * b.v3 + v3 * b.v3;
	return r;
}

Vector3f Vector3f::cross(const Vector3f& b)
{
	Vector3f r;
	r.v1 = v2 * b.v3 - v3 * b.v2;
	r.v2 = v3 * b.v1 - v1 * b.v3;
	r.v3 = v1 * b.v2 - v2 * b.v1;
	return r;
}

Vector3f Vector3f::add(const Vector3f& b)
{
	Vector3f r;
	r.v1 = v1 + b.v1;
	r.v2 = v2 + b.v2;
	r.v3 = v3 + b.v3;
	return r;
}

Vector3f Vector3f::sub(const Vector3f& b)
{
	Vector3f r;
	r.v1 = v1 - b.v1;
	r.v2 = v2 - b.v2;
	r.v3 = v3 - b.v3;
	return r;
}

Vector3f Vector3f::scale(float s)
{
	Vector3f r;
	r.v1 = v1 * s;
	r.v2 = v2 * s;
	r.v3 = v3 * s;
	return r;
}

Vector3f Vector3f::operator*(const Vector3f& b)
{
	return mul(b);
}

Vector3f Vector3f::operator*(float s)
{
	return scale(s);
}

Vector3f Vector3f::operator-(const Vector3f& v)
{
	return sub(v);
}

Vector3f Vector3f::operator+(const Vector3f& v)
{
	return add(v);
}

float Vector3f::length() const
{
	return sqrt(v1 * v1 + v2 * v2 + v3 * v3);
}

void Vector3f::normalize()
{
	const auto& length = this->length();
	if (length == 0) return;
	v1 = v1 / length;
	v2 = v2 / length;
	v3 = v3 / length;
}

Matrix33f::Matrix33f(float val11, float val12, float val13, float val21, float val22, float val23, float val31,
	float val32, float val33)
{
	vals[0] = val11;
	vals[1] = val12;
	vals[2] = val13;
	vals[3] = val21;
	vals[4] = val22;
	vals[5] = val23;
	vals[6] = val31;
	vals[7] = val32;
	vals[8] = val33;
}

Matrix33f::Matrix33f(float array[9])
{
	vals[0] = array[0];
	vals[1] = array[1];
	vals[2] = array[2];
	vals[3] = array[3];
	vals[4] = array[4];
	vals[5] = array[5];
	vals[6] = array[6];
	vals[7] = array[7];
	vals[8] = array[8];
}

/** Matrix33 * Vector3 **/
Vector3f Matrix33f::mul(const Vector3f& vector)
{
	const auto vx = vector.v1;
	const auto vy = vector.v2;
	const auto vz = vector.v3;
	const auto nx = vx * v11 + vy * v12 + vz * v13;
	const auto ny = vx * v21 + vy * v22 + vz * v23;
	const auto nz = vx * v31 + vy * v32 + vz * v33;
	return {nx, ny, nz};
}

Vector3f Matrix33f::operator*(const Vector3f& vec)
{
	return mul(vec);
}


