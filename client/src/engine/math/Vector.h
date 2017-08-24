#ifndef __VECTOR_H__
#define __VECTOR_H__

#pragma once

class CVector2
{
public:
	CVector2(int x, int y);

public:
	int m_x;
	int m_y;
};

class CVector3
{
public:
	CVector3(int x, int y, int z);

public:
	int m_x;
	int m_y;
	int m_z;
};

#endif