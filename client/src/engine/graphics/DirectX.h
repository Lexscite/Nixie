#ifndef __DIRECTX_H__
#define __DIRECTX_H__

#include <windows.h>
#include <iostream>
#include "../utils/Memory.h"

class CDirectX
{
public:
	static CDirectX* GetSingleton();

	bool Init();
	void Release();

private:
	CDirectX();

private:
	static CDirectX* s_singleton;
};

#endif