#pragma once

#include <vector>
#include "scene.h"
#include "glew.h"

class Mesh
{
public:
	~Mesh();

	static Mesh* LoadMesh(const aiMesh* i_mesh, const std::vector<GLuint>& i_modelTextures);

	void Draw();

private:
	friend class WindowModel3D;

	Mesh();

	void LoadVBO(const aiMesh* i_mesh);
	void LoadEBO(const aiMesh* i_mesh);
	void CreateVAO();

	GLuint m_vbo;
	GLuint m_ebo;
	GLuint m_vao;

	GLuint m_texture;
	int m_textureWidth;
	int m_textureHeight;
	int m_numVertices;
	int m_numTriangles;
};

