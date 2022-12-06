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
	if (!m_textures.empty())
		glDeleteTextures(m_textures.size(), &m_textures[0]);
	for (Mesh* mesh : m_meshes)
		delete mesh;
	m_meshes.clear();
	delete m_aabb;
}

Model3D* Model3D::LoadFromFile(const std::string& i_fileName)
{
	App->editor->OutputToConsole(std::string("Loading model " + i_fileName + "...").c_str());

	if (!CheckValidFormat(i_fileName)) {
		App->editor->OutputToConsole("File is not FBX");
		return nullptr;
	}

	Model3D* model = new Model3D(i_fileName);

	std::string filePath = i_fileName;
	const aiScene* scene = aiImportFile(filePath.c_str(), aiProcessPreset_TargetRealtime_MaxQuality);
	
	if (scene)
	{
		App->editor->OutputToConsole("Loading textures...");
		model->LoadMaterials(scene);
		if (model->m_textures.size() != scene->mNumMaterials) {
			App->editor->OutputToConsole("Some texture(s) failed to load");
			aiReleaseImport(scene);
			delete model;
			return nullptr;
		}
		App->editor->OutputToConsole("Loading meshes...");
		model->LoadMeshesAndComputeAABB(scene);
		App->editor->OutputToConsole("AABB computed");
		aiReleaseImport(scene);
		App->editor->OutputToConsole("Model loaded successfully!");
		return model;
	}
	else
	{
		std::string errorString = "Error loading " + i_fileName + ": " + aiGetErrorString();
		App->editor->OutputToConsole(errorString.c_str());
		delete model;
		return nullptr;
	}
}

bool Model3D::CheckValidFormat(const std::string& i_fileName)
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
		(*it)->Draw();
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

void Model3D::LoadMeshesAndComputeAABB(const aiScene* i_scene)
{
	aiMesh** meshes = i_scene->mMeshes;
	unsigned int numMeshes = i_scene->mNumMeshes;

	float3 minVert = float3(math::floatMax);
	float3 maxVert = float3(math::floatMin);
	
	for (int i = 0; i < numMeshes; ++i) {
		//create mesh instance
		Mesh* mesh = Mesh::LoadMesh(meshes[i], m_textures);
		m_meshes.push_back(mesh);

		//update min and max vertices
		aiVector3D* meshVert = meshes[i]->mVertices;
		unsigned int numVertices = meshes[i]->mNumVertices;
		for (int v = 0; v < numVertices; ++v) {
			aiVector3D vert = meshVert[v];
			minVert = float3(math::Min(minVert.x, vert.x),
				math::Min(minVert.y, vert.y),
				math::Min(minVert.z, vert.z));
			maxVert = float3(math::Max(maxVert.x, vert.x),
				math::Max(maxVert.y, vert.y),
				math::Max(maxVert.z, vert.z));
		}
	}

	//when we start to use GameObjects,
	//this will need to access the position of the transform and add it to the vectors
	m_aabb = new AABB(minVert, maxVert);
}
