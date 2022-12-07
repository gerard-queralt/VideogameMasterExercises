#pragma once

#include <string>
#include <list>

#include "assimp/scene.h"
#include "Geometry/AABB.h"

#include "Mesh.h"

class Model3D
{
public:
	~Model3D();

	static const std::string s_modelFolderPath;

	static Model3D* LoadFromFile(const std::string& i_fileName);
	void Draw();

	const AABB* GetAABB() {
		return m_aabb;
	}

private:
	friend class WindowModel3D;

	Model3D(std::string i_fileName);

	static bool CheckValidFormat(const std::string& i_fileName);
	void LoadMaterials(const aiScene* i_scene);
	void LoadMeshesAndComputeAABB(const aiScene* i_scene);

	std::string m_modelPath;

	AABB* m_aabb;

	std::vector<GLuint> m_textures;
	std::list<Mesh*> m_meshes;
};

