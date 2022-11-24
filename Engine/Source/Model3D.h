#pragma once

#include <string>
#include <list>

#include "scene.h"

#include "Mesh.h"

class Model3D
{
public:
	~Model3D();

	static const std::string s_modelFolderPath;

	static Model3D* LoadFromFile(std::string i_fileName);
	void Draw();

private:
	Model3D();

	void LoadMaterials(const aiScene* i_scene);
	void LoadMeshes(aiMesh** i_meshes, int i_numMeshes);

	std::vector<GLuint> m_textures;
	std::list<Mesh*> m_meshes;
};

