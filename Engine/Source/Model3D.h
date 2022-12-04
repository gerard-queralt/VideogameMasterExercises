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

	static Model3D* LoadFromFile(const std::string& i_fileName);
	void Draw();

private:
	friend class WindowModel3D;

	Model3D(std::string i_fileName);

	static bool CheckValidFormat(const std::string& i_fileName);
	void LoadMaterials(const aiScene* i_scene);
	void LoadMeshes(const aiScene* i_scene);

	std::vector<GLuint> m_textures;
	std::list<Mesh*> m_meshes;
	std::string m_modelPath;
};

