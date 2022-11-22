#pragma once

#include <string>

#include "scene.h"

class Model3D
{
public:
	Model3D();
	~Model3D();

	void LoadFromFile(std::string i_fileName);
	void LoadMaterials(const aiScene* scene);
};

