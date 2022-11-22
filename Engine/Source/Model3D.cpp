#include "Model3D.h"

#include <vector>

#include "Application.h"
#include "ModuleEditor.h"
#include "ModuleTexture.h"

#include "cimport.h"
#include "postprocess.h"

Model3D::Model3D()
{
}

Model3D::~Model3D()
{
}

void Model3D::LoadFromFile(std::string i_fileName)
{
	const aiScene* scene = aiImportFile(i_fileName.c_str(), aiProcessPreset_TargetRealtime_MaxQuality);
	if (scene)
	{
		// TODO: LoadTextures(scene->mMaterials, scene->mNumMaterials);
		// TODO: LoadMeshes(scene->mMeshes, scene->mNumMeshes);
	}
	else
	{
		std::string errorString = "Error loading " + i_fileName + ": " + aiGetErrorString();
		App->editor->OutputToConsole(errorString.c_str());
	}
}

void Model3D::LoadMaterials(const aiScene* i_scene)
{
	aiString file;
	std::vector<DirectX::ScratchImage> materials;

	materials.reserve(i_scene->mNumMaterials);

	for (unsigned i = 0; i < i_scene->mNumMaterials; ++i)
	{
		if (i_scene->mMaterials[i]->GetTexture(aiTextureType_DIFFUSE, 0, &file) == AI_SUCCESS)
		{
			materials.push_back(App->texture->LoadTextureFromFile(file.data));
		}
	}
}
