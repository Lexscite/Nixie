#include "stdafx.h"

#include "engine/app.h"


int WINAPI WinMain(__in HINSTANCE hInstance, __in_opt HINSTANCE hPrevInstance, __in LPSTR lpCmdLine, __in int nShowCmd)
{
	int exit_code = 0;

	auto app = Nixie::App::GetSingleton();
	if (app->Init(hInstance))
		exit_code = app->Run();

	return exit_code;
}