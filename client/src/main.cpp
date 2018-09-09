#include "stdafx.h"

#include "engine/app.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	int exit_code = 0;

	auto app = Nixie::App::Get();
	if (app->Init(hInstance))
		exit_code = app->Run();

	return exit_code;
}