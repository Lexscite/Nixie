#ifndef MODEL_CONVERTER_H
#define MODEL_CONVERTER_H

#pragma once

#include <iostream>
#include <fstream>
#include <string>

namespace Nixie
{
	typedef struct {
		float x, y, z;
	} Vector3;

	typedef struct {
		int x, y, z;
	} IntVector3;

	struct Face
	{
		IntVector3 v;
		IntVector3 t;
		IntVector3 n;
	};

	class ModelConverter final
	{
	public:
		static ModelConverter* GetSingleton();

		bool Init();
		bool Run();

	private:
		ModelConverter();

		bool CheckFile(char* filename);
		bool ProcessFile(char* filename);

		bool GetModelMetrics(char* filename);
		bool Read(char* filename);
		bool Write(char* filename);

	private:
		static ModelConverter* singleton_;

		int v_count_, t_count_, n_count_, f_count_;

		Vector3* v_coords_;
		Vector3* t_coords_;
		Vector3* n_coords_;
		Face* faces_;
	};
}

#endif