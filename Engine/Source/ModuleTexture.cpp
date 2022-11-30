#include "ModuleTexture.h"

const std::string ModuleTexture::s_textureFolderPath = "textures/";

ModuleTexture::ModuleTexture()
{
}

ModuleTexture::~ModuleTexture()
{
}

GLuint ModuleTexture::LoadTextureFromFile(std::string i_textureName)
{
    GLuint texture;

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    DirectX::ScratchImage image = LoadImageFromFile(i_textureName);

    GLint width, height, internalFormat, format, type;
    LoadInformationFromImage(image, width, height, internalFormat, format, type);

    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, type, image.GetPixels());

    glGenerateMipmap(GL_TEXTURE_2D);

    return texture;
}

DirectX::ScratchImage ModuleTexture::LoadImageFromFile(std::string i_textureName)
{
    std::string texturePath = i_textureName;
    DirectX::ScratchImage image;
    
    HRESULT res = TryLoadingImage(texturePath, image);

    if (FAILED(res)) {
        texturePath = s_textureFolderPath + i_textureName;
        res = TryLoadingImage(texturePath, image);
    }

    return RotateImage(image);
}

HRESULT ModuleTexture::TryLoadingImage(std::string i_texturePath, DirectX::ScratchImage& o_image)
{
    std::wstring texturePathAsWString = std::wstring(i_texturePath.begin(), i_texturePath.end());
    HRESULT res;

    res = DirectX::LoadFromDDSFile(texturePathAsWString.c_str(), DirectX::DDS_FLAGS_NONE, nullptr, o_image);

    if (FAILED(res))
        res = DirectX::LoadFromTGAFile(texturePathAsWString.c_str(), DirectX::TGA_FLAGS_NONE, nullptr, o_image);

    if (FAILED(res))
        res = DirectX::LoadFromWICFile(texturePathAsWString.c_str(), DirectX::WIC_FLAGS_NONE, nullptr, o_image);
    
    return res;
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
