#include "model_converter.h"

namespace Nixie
{
	ModelConverter::ModelConverter()
	{

	}

	ModelConverter* ModelConverter::singleton_;

	ModelConverter* ModelConverter::Get()
	{
		if (singleton_ == 0)
			singleton_ = new ModelConverter;

		return singleton_;
	}

	bool ModelConverter::Init()
	{
		return true;
	}

	bool ModelConverter::Run()
	{
		bool done = false;
		char filename[256];

		while (!done)
		{
			std::cout << "Enter model filename: ";
			std::cin >> filename;
			if (CheckFile(filename))
			{
				ProcessFile(filename);
				std::cout << std::endl << "File processed successfully" << std::endl << std::endl;
			}
			else
			{
				std::cout << std::endl << "File " << filename << " could not be opened." << std::endl << std::endl;
			}
		}

		return true;
	}

	bool ModelConverter::CheckFile(char* filename)
	{
		bool result;
		std::ifstream input_fs;

		input_fs.open(filename);

		result = input_fs.good();
		input_fs.clear();

		return result;
	}

	bool ModelConverter::ProcessFile(char* filename)
	{
		std::cout << std::endl << "Getting model metrics... ";

		if (!GetModelMetrics(filename))
		{
			std::cout << "FAILED" << std::endl;
			return false;
		}

		std::cout << "OK" << std::endl;
		std::cout << std::endl << "Reading file...";

		if (!Read(filename))
		{
			std::cout << "FAILED" << std::endl;
			return false;
		}

		std::cout << "OK" << std::endl;
		std::cout << std::endl << "Converting...";

		if (!Write(filename))
		{
			std::cout << "FAILED" << std::endl;
			return false;
		}

		std::cout << "OK" << std::endl;

		std::cout << std::endl << "Summary:" << std::endl;
		std::cout << "	Vertices: " << v_count_ << std::endl;
		std::cout << "	UVs:      " << t_count_ << std::endl;
		std::cout << "	Normals:  " << n_count_ << std::endl;
		std::cout << "	Faces:    " << f_count_ << std::endl << std::endl;

		return true;
	}

	bool ModelConverter::GetModelMetrics(char* filename)
	{
		std::ifstream input_fs;
		char input;

		// Reset model metrics
		v_count_ = 0;
		t_count_ = 0;
		n_count_ = 0;
		f_count_ = 0;

		input_fs.open(filename);

		if (input_fs.fail() == true)
			return false;

		input_fs.get(input);
		while (!input_fs.eof())
		{
			// Vertices
			if (input == 'v')
			{
				input_fs.get(input);
				if (input == ' ') { v_count_++; }
				if (input == 't') { t_count_++; }
				if (input == 'n') { n_count_++; }
			}

			// Faces
			if (input == 'f')
			{
				input_fs.get(input);
				if (input == ' ') { f_count_++; }
			}

			while (input != '\n')
			{
				input_fs.get(input);
			}

			input_fs.get(input);
		}

		input_fs.close();

		return true;
	}

	bool ModelConverter::Read(char* filename)
	{
		v_coords_ = new Vector3[v_count_];
		t_coords_ = new Vector3[t_count_];
		n_coords_ = new Vector3[n_count_];
		faces_ = new Face[f_count_];

		int v_index = 0;
		int t_index = 0;
		int f_index = 0;
		int n_index = 0;

		std::ifstream input_fs;

		char input, input2;

		input_fs.open(filename);

		if (input_fs.fail() == true)
		{
			return false;
		}

		input_fs.get(input);
		while (!input_fs.eof())
		{
			if (input == 'v')
			{
				input_fs.get(input);

				if (input == ' ')
				{
					input_fs >> v_coords_[v_index].x >> v_coords_[v_index].y >> v_coords_[v_index].z;
					v_coords_[v_index].z = v_coords_[v_index].z * -1.0f;
					v_index++;
				}

				if (input == 't')
				{
					input_fs >> t_coords_[t_index].x >> t_coords_[t_index].y;
					t_coords_[t_index].y = 1.0f - t_coords_[t_index].y;
					t_index++;
				}

				if (input == 'n')
				{
					input_fs >> n_coords_[n_index].x >> n_coords_[n_index].y >> n_coords_[n_index].z;
					n_coords_[n_index].z = n_coords_[n_index].z * -1.0f;
					n_index++;
				}
			}

			if (input == 'f')
			{
				input_fs.get(input);
				if (input == ' ')
				{
					input_fs >> faces_[f_index].v.z
						>> input2;

					if ((char)input_fs.peek() == '/')
					{
						faces_[f_index].t.z = 0;
						input_fs >> input2;
					}
					else
					{
						input_fs >> faces_[f_index].t.z;
						input_fs >> input2;
					}

					input_fs >> faces_[f_index].n.z;

					input_fs >> faces_[f_index].v.y
						>> input2;

					if ((char)input_fs.peek() == '/')
					{
						faces_[f_index].t.y= 0;
						input_fs >> input2;
					}
					else
					{
						input_fs >> faces_[f_index].t.y;
						input_fs >> input2;
					}

					input_fs >> faces_[f_index].n.y;

					input_fs >> faces_[f_index].v.x
						>> input2;

					if ((char)input_fs.peek() == '/')
					{
						faces_[f_index].t.x = 0;
						input_fs >> input2;
					}
					else
					{
						input_fs >> faces_[f_index].t.x;
						input_fs >> input2;
					}

					input_fs >> faces_[f_index].n.x;

					f_index++;
				}
			}

			while (input != '\n')
			{
				input_fs.get(input);
			}

			input_fs.get(input);
		}

		input_fs.close();

		return true;
	}

	bool ModelConverter::Write(char* filename)
	{
		std::ofstream output_fs;
		output_fs.open(std::string(filename).substr(0, std::string(filename).find_last_of('.')) + ".txt");

		output_fs << "Vertex Count: " << (f_count_ * 3) << std::endl;
		output_fs << std::endl;
		output_fs << "Data:" << std::endl;
		output_fs << std::endl;

		int v_index = 0;
		int t_index = 0;
		int n_index = 0;

		for (int i = 0; i < f_count_; i++)
		{
			v_index = faces_[i].v.x - 1;
			t_index = faces_[i].t.x- 1;
			n_index = faces_[i].n.x- 1;

			output_fs << v_coords_[v_index].x << ' ' << v_coords_[v_index].y << ' ' << v_coords_[v_index].z << ' '
				<< t_coords_[t_index].x << ' ' << t_coords_[t_index].y << ' '
				<< n_coords_[n_index].x << ' ' << n_coords_[n_index].y << ' ' << n_coords_[n_index].z << std::endl;

			v_index = faces_[i].v.y - 1;
			t_index = faces_[i].t.y - 1;
			n_index = faces_[i].n.y - 1;

			output_fs << v_coords_[v_index].x << ' ' << v_coords_[v_index].y << ' ' << v_coords_[v_index].z << ' '
				<< t_coords_[t_index].x << ' ' << t_coords_[t_index].y << ' '
				<< n_coords_[n_index].x << ' ' << n_coords_[n_index].y << ' ' << n_coords_[n_index].z << std::endl;

			v_index = faces_[i].v.z - 1;
			t_index = faces_[i].t.z - 1;
			n_index = faces_[i].n.z - 1;

			output_fs << v_coords_[v_index].x << ' ' << v_coords_[v_index].y << ' ' << v_coords_[v_index].z << ' '
				<< t_coords_[t_index].x << ' ' << t_coords_[t_index].y << ' '
				<< n_coords_[n_index].x << ' ' << n_coords_[n_index].y << ' ' << n_coords_[n_index].z << std::endl;
		}

		output_fs.close();

		if (v_coords_)
		{
			delete[] v_coords_;
			v_coords_ = 0;
		}
		if (t_coords_)
		{
			delete[] t_coords_;
			t_coords_ = 0;
		}
		if (n_coords_)
		{
			delete[] n_coords_;
			n_coords_ = 0;
		}
		if (faces_)
		{
			delete[] faces_;
			faces_ = 0;
		}

		return true;
	}
}