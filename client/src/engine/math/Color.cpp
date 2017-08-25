#include "Color.h"

Color::Color(int r, int g, int b)
{
	this->r = 1 / 255 * r;
	this->g = 1 / 255 * g;
	this->b = 1 / 255 * b;
	this->a = 1.0f;
}

Color::Color(int r, int g, int b, int a)
{
	this->r = 1 / 255 * r;
	this->g = 1 / 255 * g;
	this->b = 1 / 255 * b;
	this->a = 1 / 255 * a;
}

Color::Color(float r, float g, float b)
{
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = 1.0f;
}

Color::Color(float r, float g, float b, float a)
{
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}

Color::Color(IntVector3 vector)
{
	this->r = 1 / 255 * vector.x;
	this->g = 1 / 255 * vector.y;
	this->b = 1 / 255 * vector.z;
	this->a = 1.0f;
}

Color::Color(Vector3 vector)
{
	this->r = vector.x;
	this->g = vector.y;
	this->b = vector.z;
	this->a = 1.0f;
}