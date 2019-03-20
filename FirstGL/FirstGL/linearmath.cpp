#include "linearmath.h"

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
