#pragma once

#include "Module.h"

#include <string>
#include "DirectXTex/DirectXTex.h"

class ModuleTexture : public Module
{
public:
	ModuleTexture();
	~ModuleTexture();

	static const std::string TEXTURE_FOLDER_PATH;

	DirectX::ScratchImage LoadTextureFromFile(std::string textureName);

private:
	DirectX::ScratchImage RotateImage(const DirectX::ScratchImage& imageSource);
};

