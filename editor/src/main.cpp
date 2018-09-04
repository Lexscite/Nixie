#include "model_converter.h"

int main()
{
	int exit_code = 0;

	Nixie::ModelConverter* model_converter = Nixie::ModelConverter::GetSingleton();
	if (model_converter->Init())
		exit_code = model_converter->Run();

	return exit_code;
}