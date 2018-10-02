#include "stdafx_client.h"

#include "application.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	int exit_code = 0;

	if (vodoo::Application::Init(hInstance))
	{
		exit_code = vodoo::Application::Run();
	}

	return exit_code;
}