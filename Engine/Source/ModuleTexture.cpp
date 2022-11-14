#include "ModuleTexture.h"

const std::string ModuleTexture::TEXTURE_FOLDER_PATH = "textures/";

ModuleTexture::ModuleTexture()
{
}

ModuleTexture::~ModuleTexture()
{
}

DirectX::ScratchImage ModuleTexture::LoadTextureFromFile(std::string textureName)
{
    std::string texturePath = TEXTURE_FOLDER_PATH + textureName;
    std::wstring texturePathAsWString = std::wstring(texturePath.begin(), texturePath.end());
    DirectX::ScratchImage image;
    HRESULT res;

    res = DirectX::LoadFromDDSFile(texturePathAsWString.c_str(), DirectX::DDS_FLAGS_NONE, nullptr, image);
    
    if (FAILED(res))
        res = DirectX::LoadFromTGAFile(texturePathAsWString.c_str(), DirectX::TGA_FLAGS_NONE, nullptr, image);
    
    if (SUCCEEDED(res))
        res = DirectX::LoadFromWICFile(texturePathAsWString.c_str(), DirectX::WIC_FLAGS_NONE, nullptr, image);

    return RotateImage(image);
}

DirectX::ScratchImage ModuleTexture::RotateImage(const DirectX::ScratchImage& imageSource)
{
    DirectX::ScratchImage rotatedImage;
    DirectX::FlipRotate(imageSource.GetImages(), 1, imageSource.GetMetadata(), DirectX::TEX_FR_FLIP_VERTICAL, rotatedImage);
    return rotatedImage;
}
