#include "Vector.h"

Vector2::Vector2()
{
	x = 0;
	y = 0;
}

Vector2::Vector2(float x, float y)
{
	this->x = x;
	this->y = y;
}

Vector3::Vector3()
{
	x = 0;
	y = 0;
	z = 0;
}

Vector3::Vector3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector4::Vector4()
{
	x = 0;
	y = 0;
	z = 0;
	t = 0;
}

Vector4::Vector4(float x, float y, float z, float t)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->t = t;
}

IntVector2::IntVector2()
{
	x = 0;
	y = 0;
}

IntVector2::IntVector2(int x, int y)
{
	this->x = x;
	this->y = y;
}

IntVector3::IntVector3()
{
	x = 0;
	y = 0;
	z = 0;
}

IntVector3::IntVector3(int x, int y, int z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

IntVector4::IntVector4()
{
	x = 0;
	y = 0;
	z = 0;
	t = 0;
}

IntVector4::IntVector4(int x, int y, int z, int t)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->t = t;
}