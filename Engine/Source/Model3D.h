#pragma once

#include <string>

#include "scene.h"
#include "DirectXTex/DirectXTex.h"

#include "Mesh.h"

class Model3D
{
public:
	Model3D();
	~Model3D();

	void LoadFromFile(std::string i_fileName);
	void Draw();

private:
	void LoadMaterials(const aiScene* i_scene);
	void LoadMeshes(const aiMesh** i_meshes, int i_numMeshes);

	std::vector<DirectX::ScratchImage> m_materials;
	std::vector<Mesh*> m_meshes;
};

