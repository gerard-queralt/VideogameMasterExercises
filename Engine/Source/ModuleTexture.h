#pragma once

#include "Module.h"

#include <string>
#include <glew.h>
#include "DirectXTex/DirectXTex.h"

class ModuleTexture : public Module
{
public:
	ModuleTexture();
	~ModuleTexture();

	static const std::string s_textureFolderPath;

	GLuint LoadTextureFromFile(std::string i_textureName);

private:
	DirectX::ScratchImage LoadImageFromFile(std::string i_textureName);
	HRESULT TryLoadingImage(std::string i_texturePath, DirectX::ScratchImage& o_image);
	DirectX::ScratchImage RotateImage(const DirectX::ScratchImage& i_imageSource);
	void LoadInformationFromImage(const DirectX::ScratchImage& i_image,
		GLint& o_width,
		GLint& o_height,
		GLint& o_internalFormat,
		GLint& o_format,
		GLint& o_type);
};

