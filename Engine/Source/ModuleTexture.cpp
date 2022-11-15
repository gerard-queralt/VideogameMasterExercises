#include "ModuleTexture.h"

const std::string ModuleTexture::TEXTURE_FOLDER_PATH = "textures/";

ModuleTexture::ModuleTexture()
{
}

ModuleTexture::~ModuleTexture()
{
}

DirectX::ScratchImage ModuleTexture::LoadTextureFromFile(std::string i_textureName)
{
    std::string texturePath = TEXTURE_FOLDER_PATH + i_textureName;
    std::wstring texturePathAsWString = std::wstring(texturePath.begin(), texturePath.end());
    DirectX::ScratchImage image;
    HRESULT res;

    res = DirectX::LoadFromDDSFile(texturePathAsWString.c_str(), DirectX::DDS_FLAGS_NONE, nullptr, image);
    
    if (FAILED(res))
        res = DirectX::LoadFromTGAFile(texturePathAsWString.c_str(), DirectX::TGA_FLAGS_NONE, nullptr, image);
    
    if (FAILED(res))
        res = DirectX::LoadFromWICFile(texturePathAsWString.c_str(), DirectX::WIC_FLAGS_NONE, nullptr, image);

    return RotateImage(image);
}

void ModuleTexture::LoadInformationFromImage(const DirectX::ScratchImage& i_image,
                                             GLint& o_width,
                                             GLint& o_height,
                                             GLint& o_internalFormat,
                                             GLint& o_format,
                                             GLint& o_type)
{
    DirectX::TexMetadata metadata = i_image.GetMetadata();
    o_width = metadata.width;
    o_height = metadata.height;
    switch (metadata.format)
    {
    case DXGI_FORMAT_R8G8B8A8_UNORM_SRGB:
    case DXGI_FORMAT_R8G8B8A8_UNORM:
        o_internalFormat = GL_RGBA8;
        o_format = GL_RGBA;
        o_type = GL_UNSIGNED_BYTE;
        break;
    case DXGI_FORMAT_B8G8R8A8_UNORM_SRGB:
    case DXGI_FORMAT_B8G8R8A8_UNORM:
        o_internalFormat = GL_RGBA8;
        o_format = GL_BGRA;
        o_type = GL_UNSIGNED_BYTE;
        break;
    case DXGI_FORMAT_B5G6R5_UNORM:
        o_internalFormat = GL_RGB8;
        o_format = GL_BGR;
        o_type = GL_UNSIGNED_BYTE;
        break;
    default:
        assert(false && "Unsupported format");
    }
}

DirectX::ScratchImage ModuleTexture::RotateImage(const DirectX::ScratchImage& i_imageSource)
{
    DirectX::ScratchImage rotatedImage;
    DirectX::FlipRotate(i_imageSource.GetImages(), 1, i_imageSource.GetMetadata(), DirectX::TEX_FR_FLIP_VERTICAL, rotatedImage);
    return rotatedImage;
}
