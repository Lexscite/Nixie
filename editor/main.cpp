#include "stdafx_editor.h"

#include "model_converter.h"

int main()
{
	int exit_code = 0;

	nixie::ModelConverter* model_converter = nixie::ModelConverter::Get();
	if (model_converter->Init())
		exit_code = model_converter->Run();

	return exit_code;
}