#include "stdafx.h"

#include "engine/app.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	int exit_code = 0;

	if (nixie::App::Init(hInstance))
	{
		exit_code = nixie::App::Run();
	}

	return exit_code;
}