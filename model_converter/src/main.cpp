#include <iostream>
#include <fstream>
#include <string>

typedef struct
{
	float x, y, z;
} VertexType;

typedef struct
{
	int vIndex1, vIndex2, vIndex3;
	int tIndex1, tIndex2, tIndex3;
	int nIndex1, nIndex2, nIndex3;
} FaceType;

bool Start();
void GetModelFilename(char*);
bool ReadFileCounts(char*, int&, int&, int&, int&);
bool LoadDataStructures(char*, int, int, int, int);

int main()
{
	if (Start())
		return -1;
}

bool Start()
{
	bool result;
	char filename[256];
	int vertexCount, textureCount, normalCount, faceCount;

	GetModelFilename(filename);

	result = ReadFileCounts(filename, vertexCount, textureCount, normalCount, faceCount);
	if (!result)
	{
		return false;
	}

	std::cout << std::endl;
	std::cout << "Vertices: " << vertexCount << std::endl;
	std::cout << "UVs:      " << textureCount << std::endl;
	std::cout << "Normals:  " << normalCount << std::endl;
	std::cout << "Faces:    " << faceCount << std::endl;

	result = LoadDataStructures(filename, vertexCount, textureCount, normalCount, faceCount);
	if (!result)
	{
		return false;
	}

	std::cout << "\nFile has been converted.\n" << std::endl;

	Start();

	return true;
}

void GetModelFilename(char* filename)
{
	bool done;
	std::ifstream fin;

	done = false;
	while (!done)
	{
		std::cout << "Enter model filename: ";

		std::cin >> filename;

		fin.open(filename);

		if (fin.good())
		{
			done = true;
		}
		else
		{
			fin.clear();
			std::cout << std::endl;
			std::cout << "File " << filename << " could not be opened." << std::endl << std::endl;
		}
	}

	return;
}

bool ReadFileCounts(char* filename, int& vertexCount, int& textureCount, int& normalCount, int& faceCount)
{
	std::ifstream fin;
	char input;

	vertexCount = 0;
	textureCount = 0;
	normalCount = 0;
	faceCount = 0;

	fin.open(filename);

	if (fin.fail() == true)
	{
		return false;
	}

	fin.get(input);
	while (!fin.eof())
	{
		if (input == 'v')
		{
			fin.get(input);
			if (input == ' ') { vertexCount++; }
			if (input == 't') { textureCount++; }
			if (input == 'n') { normalCount++; }
		}

		if (input == 'f')
		{
			fin.get(input);
			if (input == ' ') { faceCount++; }
		}

		while (input != '\n')
		{
			fin.get(input);
		}

		fin.get(input);
	}

	fin.close();

	return true;
}

bool LoadDataStructures(char* filename, int vertexCount, int textureCount, int normalCount, int faceCount)
{
	VertexType *vertices, *texcoords, *normals;
	FaceType *faces;
	std::ifstream fin;
	int vertexIndex, texcoordIndex, normalIndex, faceIndex, vIndex, tIndex, nIndex;
	char input, input2;
	std::ofstream fout;


	vertices = new VertexType[vertexCount];
	if (!vertices)
	{
		return false;
	}

	texcoords = new VertexType[textureCount];
	if (!texcoords)
	{
		return false;
	}

	normals = new VertexType[normalCount];
	if (!normals)
	{
		return false;
	}

	faces = new FaceType[faceCount];
	if (!faces)
	{
		return false;
	}

	vertexIndex = 0;
	texcoordIndex = 0;
	normalIndex = 0;
	faceIndex = 0;

	fin.open(filename);

	if (fin.fail() == true)
	{
		return false;
	}

	fin.get(input);
	while (!fin.eof())
	{
		if (input == 'v')
		{
			fin.get(input);

			if (input == ' ')
			{
				fin >> vertices[vertexIndex].x >> vertices[vertexIndex].y >> vertices[vertexIndex].z;

				vertices[vertexIndex].z = vertices[vertexIndex].z * -1.0f;
				vertexIndex++;
			}

			if (input == 't')
			{
				fin >> texcoords[texcoordIndex].x >> texcoords[texcoordIndex].y;

				texcoords[texcoordIndex].y = 1.0f - texcoords[texcoordIndex].y;
				texcoordIndex++;
			}

			if (input == 'n')
			{
				fin >> normals[normalIndex].x >> normals[normalIndex].y >> normals[normalIndex].z;

				normals[normalIndex].z = normals[normalIndex].z * -1.0f;
				normalIndex++;
			}
		}

		if (input == 'f')
		{
			fin.get(input);
			if (input == ' ')
			{
				fin >> faces[faceIndex].vIndex3
					>> input2;

				if ((char)fin.peek() == '/')
				{
					faces[faceIndex].tIndex3 = 0;
					fin >> input2;
				}
				else
				{
					fin >> faces[faceIndex].tIndex3;
					fin >> input2;
				}

				fin >> faces[faceIndex].nIndex3;
					
				fin >> faces[faceIndex].vIndex2
					>> input2;

				if ((char)fin.peek() == '/')
				{
					faces[faceIndex].tIndex2 = 0;
					fin >> input2;
				}
				else
				{
					fin >> faces[faceIndex].tIndex2;
					fin >> input2;
				}

				fin >> faces[faceIndex].nIndex2;

				fin >> faces[faceIndex].vIndex1
					>> input2;

				if ((char)fin.peek() == '/')
				{
					faces[faceIndex].tIndex1 = 0;
					fin >> input2;
				}
				else
				{
					fin >> faces[faceIndex].tIndex1;
					fin >> input2;
				}

				fin >> faces[faceIndex].nIndex1;

				faceIndex++;
			}
		}

		while (input != '\n')
		{
			fin.get(input);
		}

		fin.get(input);
	}

	fin.close();

	fout.open(std::string(filename).substr(0, std::string(filename).find_last_of('.')) + ".txt");

	fout << "Vertex Count: " << (faceCount * 3) << std::endl;
	fout << std::endl;
	fout << "Data:" << std::endl;
	fout << std::endl;

	for (int i = 0; i < faceIndex; i++)
	{
		vIndex = faces[i].vIndex1 - 1;
		tIndex = faces[i].tIndex1 - 1;
		nIndex = faces[i].nIndex1 - 1;

		fout << vertices[vIndex].x << ' ' << vertices[vIndex].y << ' ' << vertices[vIndex].z << ' '
			<< texcoords[tIndex].x << ' ' << texcoords[tIndex].y << ' '
			<< normals[nIndex].x << ' ' << normals[nIndex].y << ' ' << normals[nIndex].z << std::endl;

		vIndex = faces[i].vIndex2 - 1;
		tIndex = faces[i].tIndex2 - 1;
		nIndex = faces[i].nIndex2 - 1;

		fout << vertices[vIndex].x << ' ' << vertices[vIndex].y << ' ' << vertices[vIndex].z << ' '
			<< texcoords[tIndex].x << ' ' << texcoords[tIndex].y << ' '
			<< normals[nIndex].x << ' ' << normals[nIndex].y << ' ' << normals[nIndex].z << std::endl;

		vIndex = faces[i].vIndex3 - 1;
		tIndex = faces[i].tIndex3 - 1;
		nIndex = faces[i].nIndex3 - 1;

		fout << vertices[vIndex].x << ' ' << vertices[vIndex].y << ' ' << vertices[vIndex].z << ' '
			<< texcoords[tIndex].x << ' ' << texcoords[tIndex].y << ' '
			<< normals[nIndex].x << ' ' << normals[nIndex].y << ' ' << normals[nIndex].z << std::endl;
	}

	fout.close();

	if (vertices)
	{
		delete[] vertices;
		vertices = 0;
	}
	if (texcoords)
	{
		delete[] texcoords;
		texcoords = 0;
	}
	if (normals)
	{
		delete[] normals;
		normals = 0;
	}
	if (faces)
	{
		delete[] faces;
		faces = 0;
	}

	return true;
}
