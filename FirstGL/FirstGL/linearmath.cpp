#define DECLARE_M33
#include "linearmath.h"
#include <cmath>

Vector3f::Vector3f(): position{0, 0, 0}
{
}

Vector3f::Vector3f(float x, float y, float z): position{x, y, z}
{
}

Vector3f Vector3f::mul(const Vector3f& b)
{
	Vector3f r;
	r.position[0] = position[0] * b.position[0] + position[0] * b.position[0];
	r.position[1] = position[1] * b.position[1] + position[1] * b.position[1];
	r.position[2] = position[2] * b.position[2] + position[2] * b.position[2];
	return r;
}

Vector3f Vector3f::cross(const Vector3f& b)
{
	Vector3f r;
	r.position[0] = position[1] * b.position[2] - position[2] * b.position[1];
	r.position[1] = position[2] * b.position[0] - position[0] * b.position[2];
	r.position[2] = position[0] * b.position[1] - position[1] * b.position[0];
	return r;
}

Vector3f Vector3f::add(const Vector3f& b)
{
	Vector3f r;
	r.position[0] = position[0] + b.position[0];
	r.position[1] = position[1] + b.position[1];
	r.position[2] = position[2] + b.position[2];
	return r;
}

Vector3f Vector3f::sub(const Vector3f& b)
{
	Vector3f r;
	r.position[0] = position[0] - b.position[0];
	r.position[1] = position[1] - b.position[1];
	r.position[2] = position[2] - b.position[2];
	return r;
}

Vector3f Vector3f::scale(float s)
{
	Vector3f r;
	r.position[0] = position[0] * s;
	r.position[1] = position[1] * s;
	r.position[2] = position[2] * s;
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
	return sqrt(position[0] * position[0] + position[1] * position[1] + position[2] * position[2]);
}

void Vector3f::normalize()
{
	const auto& length = this->length();
	if (length == 0) return;
	position[0] = position[0] / length;
	position[1] = position[1] / length;
	position[2] = position[2] / length;
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
	const auto vx = vector.position[0];
	const auto vy = vector.position[1];
	const auto vz = vector.position[2];
	const auto nx = vx * v11 + vy * v12 + vz * v13;
	const auto ny = vx * v21 + vy * v22 + vz * v23;
	const auto nz = vx * v31 + vy * v32 + vz * v33;
	return {nx, ny, nz};
}

Vector3f Matrix33f::operator*(const Vector3f& vec)
{
	return mul(vec);
}


