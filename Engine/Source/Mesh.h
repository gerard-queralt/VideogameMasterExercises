#pragma once

#include <vector>
#include "scene.h"
#include "glew.h"

class Mesh
{
public:
	Mesh();
	~Mesh();

	void LoadMesh(const aiMesh* i_mesh);

	void Draw(const std::vector<GLuint>& i_modelTextures);

private:
	void LoadVBO(const aiMesh* i_mesh);
	void LoadEBO(const aiMesh* i_mesh);
	void CreateVAO();

	GLuint m_vbo;
	GLuint m_ebo;
	GLuint m_vao;

	int m_materialIndex;
	int m_numVertices;
	int m_numIndices;
};

