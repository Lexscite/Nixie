#include "Vector.h"

Vector2::Vector2(float x, float y)
{
	this->x = x;
	this->y = y;
}

Vector2* Vector2::Zero()
{
	return new Vector2(0, 0);
}

Vector3::Vector3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector3* Vector3::Zero()
{
	return new Vector3(0, 0, 0);
}

IntVector2::IntVector2(int x, int y)
{
	this->x = x;
	this->y = y;
}

IntVector2* IntVector2::Zero()
{
	return new IntVector2(0, 0);
}

IntVector3::IntVector3(int x, int y, int z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

IntVector3* IntVector3::Zero()
{
	return new IntVector3(0, 0, 0);
}