#include "stdafx.h"
#include "application.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	int exit_code = 0;

	if (voodoo::Application::Init(hInstance))
	{
		exit_code = voodoo::Application::Run();
	}

	return exit_code;
}