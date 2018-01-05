#ifndef MESH_H
#define MESH_H

#pragma once

#include "../component.h"
#include "../../graphics/mesh_data.h"

class Mesh : public Component
{
private:

public:
	Mesh(char* file_path);

private:
	virtual void OnInit() override;
	virtual void OnUpdate() override;

private:
	char* file_path_;
	MeshData* mesh_data_;

private:
};

#endif