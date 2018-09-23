#include "stdafx_client.h"

#include "application.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	int exit_code = 0;

	if (nixie::Application::Init(hInstance))
	{
		exit_code = nixie::Application::Run();
	}

	return exit_code;
}