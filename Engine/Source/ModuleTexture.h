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

	static const std::string TEXTURE_FOLDER_PATH;

	DirectX::ScratchImage LoadTextureFromFile(std::string i_textureName);
	void LoadInformationFromImage(const DirectX::ScratchImage& i_image,
								  GLint& o_width,
								  GLint& o_height,
								  GLint& o_internalFormat,
								  GLint& o_format,
								  GLint& o_type);

private:
	DirectX::ScratchImage RotateImage(const DirectX::ScratchImage& i_imageSource);
};

