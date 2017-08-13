#include "DirectX.h"

CDirectX::CDirectX() {}

CDirectX* CDirectX::s_singleton;

CDirectX* CDirectX::GetSingleton()
{
	if (s_singleton == nullptr)
		s_singleton = new CDirectX;

	return s_singleton;
}

bool CDirectX::Init(HWND hwnd, UINT screenWidth, UINT screenHeight)
{
	return true;
}

void CDirectX::Release()
{

}