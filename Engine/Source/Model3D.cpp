#include "Model3D.h"

#include <vector>

#include "Application.h"
#include "ModuleEditor.h"
#include "ModuleTexture.h"

#include "cimport.h"
#include "postprocess.h"

const std::string Model3D::s_modelFolderPath = "models/";

Model3D::Model3D(std::string i_fileName)
{
	//remove the last char until we find a /
	while (0 < i_fileName.size() && i_fileName[i_fileName.size() - 1] != '\\')
		i_fileName.pop_back();
	m_modelPath = i_fileName;
}

Model3D::~Model3D()
{
}

Model3D* Model3D::LoadFromFile(std::string i_fileName)
{
	if (!CheckValidFormat(i_fileName)) {
		App->editor->OutputToConsole("File is not FBX");
		return nullptr;
	}

	Model3D* model = new Model3D(i_fileName);

	std::string filePath = i_fileName;
	const aiScene* scene = aiImportFile(filePath.c_str(), aiProcessPreset_TargetRealtime_MaxQuality);
	
	if (scene)
	{
		model->LoadMaterials(scene);
		if (model->m_textures.size() != scene->mNumMaterials) {
			App->editor->OutputToConsole("Some texture(s) failed to load");
			return nullptr;
		}
		model->LoadMeshes(scene->mMeshes, scene->mNumMeshes);
		aiReleaseImport(scene);
		return model;
	}
	else
	{
		std::string errorString = "Error loading " + i_fileName + ": " + aiGetErrorString();
		App->editor->OutputToConsole(errorString.c_str());
		return nullptr;
	}
}

bool Model3D::CheckValidFormat(std::string i_fileName)
{
	//this could be more simple if we just get the last 4 characters of the string
	//but this way is more usable
	std::string fileFormat;
	bool dotNotFound = true;
	for (int i = i_fileName.size() - 1; dotNotFound && 0 <= i; --i) {
		char currentChar = i_fileName[i];
		fileFormat.insert(fileFormat.begin(), currentChar);
		dotNotFound = currentChar != '.';
	}
	return fileFormat == ".fbx";
}

void Model3D::Draw()
{
	for (std::list<Mesh*>::iterator it = m_meshes.begin(); it != m_meshes.end(); ++it) {
		(*it)->Draw(m_textures);
	}
}

void Model3D::LoadMaterials(const aiScene* i_scene)
{
	aiString file;

	m_textures.reserve(i_scene->mNumMaterials);

	for (unsigned i = 0; i < i_scene->mNumMaterials; ++i)
	{
		if (i_scene->mMaterials[i]->GetTexture(aiTextureType_DIFFUSE, 0, &file) == AI_SUCCESS)
		{
			GLuint texture = App->texture->LoadTextureFromFile(file.data, m_modelPath);
			if (texture == -1) {
				//texture failed to load, exit
				return;
			}
			m_textures.push_back(texture);
		}
	}
}

void Model3D::LoadMeshes(aiMesh** i_meshes, int i_numMeshes)
{
	for (int i = 0; i < i_numMeshes; ++i) {
		Mesh* mesh = Mesh::LoadMesh(i_meshes[i]);
		m_meshes.push_back(mesh);
	}
}
