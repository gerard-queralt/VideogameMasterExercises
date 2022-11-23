#pragma once

#include "scene.h"
#include "glew.h"

class Mesh
{
public:
	Mesh();
	~Mesh();

	void LoadMesh(const aiMesh* i_mesh);

	void Draw(GLuint i_textures);

private:
	void LoadVBO(const aiMesh* i_mesh);
	void LoadEBO(const aiMesh* i_mesh);
	void CreateVAO();

	GLuint m_vbo;
	GLuint m_ebo;
	GLuint m_vao;

	int m_numVertices;
	int m_numIndices;
};

