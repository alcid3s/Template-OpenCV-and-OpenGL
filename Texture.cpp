#include "Texture.h"
#include <iostream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>
#include "stb_image.h"

Texture::Texture(const std::string& fileName) : id(0), buffer(nullptr), width(0), height(0), BPP(0)
{
    stbi_set_flip_vertically_on_load(1);
    buffer = stbi_load(fileName.c_str(), &width, &height, &BPP, 4);
    if (buffer == nullptr)
    {
        std::cout << stbi_failure_reason() << std::endl;
    }

    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // S and T are like X and Y for textures.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glBindTexture(GL_TEXTURE_2D, 0);

    if (buffer) {
        stbi_image_free(buffer);
    }
}

Texture::Texture(cv::Mat mat)
    : id(0), t_Buffer(nullptr),
    width(0), height(0), BPP(4) // Assuming 4 bytes per pixel (RGBA)
{
    // flips texture vertically. Bottom left of image is 0,0 for OpenGL
    stbi_set_flip_vertically_on_load(1);

    auto byteArray = matToBytes(mat);

    t_Buffer = stbi_load_from_memory(byteArray.data(), byteArray.size(), &width, &height, &BPP, 4);
    if (t_Buffer == nullptr)
    {
        std::cout << stbi_failure_reason() << std::endl;
    }

    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, t_Buffer);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // S and T are like X and Y for textures.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glBindTexture(GL_TEXTURE_2D, 0);

    if (t_Buffer) {
        stbi_image_free(t_Buffer);
    }
}

std::vector<unsigned char> Texture::matToBytes(cv::Mat image) {
    std::vector<unsigned char> byteArray;
    cv::imencode(".jpg", image, byteArray);
    return byteArray;
}


Texture::~Texture()
{
    glDeleteTextures(1, &id);
}

void Texture::bind()
{
    glBindTexture(GL_TEXTURE_2D, id);
}

void Texture::unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}