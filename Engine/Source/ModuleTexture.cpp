#include "ModuleTexture.h"

#include "Application.h"
#include "ModuleEditor.h"

const std::string ModuleTexture::s_textureFolderPath = "textures/";

ModuleTexture::ModuleTexture()
{
}

ModuleTexture::~ModuleTexture()
{
}

GLuint ModuleTexture::LoadTextureFromFile(std::string i_texturePathInModel, std::string i_modelPath)
{
    DirectX::ScratchImage image;
    HRESULT loadingImageResult = LoadImageFromFile(i_texturePathInModel, i_modelPath, image);
    if (FAILED(loadingImageResult)) {
        App->editor->OutputToConsole(("Texture " + i_texturePathInModel + " failed to load").c_str());
        return -1;
    }

    GLuint texture;

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    GLint width, height, internalFormat, format, type;
    LoadInformationFromImage(image, width, height, internalFormat, format, type);

    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, type, image.GetPixels());

    glGenerateMipmap(GL_TEXTURE_2D);

    return texture;
}

HRESULT ModuleTexture::LoadImageFromFile(const std::string& i_texturePathInModel,
                                         const std::string& i_modelPath,
                                         DirectX::ScratchImage& o_image)
{
    std::string texturePath = i_texturePathInModel;
    std::string textureName = GetImageNameFromPath(i_texturePathInModel);
    DirectX::ScratchImage image;
    
    //try loading path in FBX
    HRESULT res = TryLoadingImage(texturePath, image);

    if (FAILED(res)) {
        //try loading in the same folder as the model
        texturePath = i_modelPath + textureName;
        res = TryLoadingImage(texturePath, image);
    }

    if (FAILED(res)) {
        //try loading in textures folder
        texturePath = s_textureFolderPath + textureName;
        res = TryLoadingImage(texturePath, image);
    }

    if (FAILED(res)) {
        App->editor->OutputToConsole(("Texture " + textureName + " not found").c_str());
    }
    else {
        res = RotateImage(image, o_image);
    }

    return res;
}

std::string ModuleTexture::GetImageNameFromPath(const std::string& i_texturePathInModel)
{
    std::string imageName;
    bool fileSeparatorNotFound = true;
    for (int i = i_texturePathInModel.size() - 1; fileSeparatorNotFound && 0 <= i; --i) {
        char currentChar = i_texturePathInModel[i];
        fileSeparatorNotFound = currentChar != '\\';
        if (fileSeparatorNotFound)
            imageName.insert(imageName.begin(), currentChar);
    }
    return imageName;
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

HRESULT ModuleTexture::RotateImage(const DirectX::ScratchImage& i_imageSource, DirectX::ScratchImage& o_rotatedImage)
{
    HRESULT result =
        DirectX::FlipRotate(i_imageSource.GetImages(), 1, i_imageSource.GetMetadata(), DirectX::TEX_FR_FLIP_VERTICAL, o_rotatedImage);
    return result;
}
