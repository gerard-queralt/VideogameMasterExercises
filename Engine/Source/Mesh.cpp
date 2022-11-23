#include "Mesh.h"

#include "float2.h"
#include "Application.h"
#include "ModuleRenderExercise.h"
#include "ModuleEditorCamera.h"

Mesh::Mesh()
{
}

Mesh::~Mesh()
{
}

void Mesh::LoadMesh(const aiMesh* i_mesh)
{
	LoadVBO(i_mesh);
	LoadEBO(i_mesh);
	CreateVAO();
}

void Mesh::Draw(GLuint i_texture)
{
	GLuint program = App->exercise->getProgram();
	const float4x4& view = App->camera->getView();
	const float4x4& proj = App->camera->getProj();
	float4x4 model = float4x4::identity;
	
	glUseProgram(program);
	
	glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, GL_TRUE, (const float*)&model);
	glUniformMatrix4fv(glGetUniformLocation(program, "view"), 1, GL_TRUE, (const float*)&view);
	glUniformMatrix4fv(glGetUniformLocation(program, "proj"), 1, GL_TRUE, (const float*)&proj);
	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, i_texture);
	glUniform1i(glGetUniformLocation(program, "diffuse"), 0);
	
	glBindVertexArray(m_vao);
	glDrawElements(GL_TRIANGLES, m_numIndices, GL_UNSIGNED_INT, nullptr);
}

void Mesh::LoadVBO(const aiMesh* i_mesh)
{
	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	
	GLuint vertex_size = (sizeof(float) * 3 + sizeof(float) * 2);
	GLuint buffer_size = vertex_size * i_mesh->mNumVertices;
	
	glBufferData(GL_ARRAY_BUFFER, buffer_size, nullptr, GL_STATIC_DRAW);
	
	GLuint position_size = sizeof(float) * 3 * i_mesh->mNumVertices;
	
	glBufferSubData(GL_ARRAY_BUFFER, 0, position_size, i_mesh->mVertices);
	
	GLuint uv_offset = position_size;
	GLuint uv_size = sizeof(float) * 2 * i_mesh->mNumVertices;
	
	float2* uvs = (float2*)(glMapBufferRange(GL_ARRAY_BUFFER, uv_offset, uv_size, GL_MAP_WRITE_BIT));
	
	for (int i = 0; i < i_mesh->mNumVertices; ++i)
	{
		uvs[i] = float2(i_mesh->mTextureCoords[0][i].x, i_mesh->mTextureCoords[0][i].y);
	}
	
	glUnmapBuffer(GL_ARRAY_BUFFER);
	
	m_numVertices = i_mesh->mNumVertices;
}

void Mesh::LoadEBO(const aiMesh* i_mesh)
{
	glGenBuffers(1, &m_ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
	
	GLuint index_size = sizeof(GLuint) * i_mesh->mNumFaces * 3;
	
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_size, nullptr, GL_STATIC_DRAW);
	
	GLuint* indices = (GLuint*)(glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_MAP_WRITE_BIT));
	
	for (int i = 0; i < i_mesh->mNumFaces; ++i)
	{
		assert(i_mesh->mFaces[i].mNumIndices == 3); // note: assume triangles = 3 indices per face
		*(indices++) = i_mesh->mFaces[i].mIndices[0];
		*(indices++) = i_mesh->mFaces[i].mIndices[1];
		*(indices++) = i_mesh->mFaces[i].mIndices[2];
	}
	
	glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
	
	m_numIndices = i_mesh->mNumFaces * 3;
}

void Mesh::CreateVAO()
{
	glGenVertexArrays(1, &m_vao);
	
	glBindVertexArray(m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
	
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(float) * 3 * m_numVertices));
}
