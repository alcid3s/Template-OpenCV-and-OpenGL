#include "Texture.h"
#include <iostream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>

#define STB_IMAGE_IMPLEMENTATION
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

Texture::Texture(cv::Mat image) {

    // Step 1: Generate an OpenGL texture ID
    GLuint textureID;
    glGenTextures(1, &textureID);

    // Step 2: Bind the texture
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Step 3: Set the texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // Step 4: Retrieve pixel data from the Mat
    const unsigned char* imageData = image.data;

    // Step 5: Upload pixel data to the OpenGL texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image.cols, image.rows, 0, GL_BGR, GL_UNSIGNED_BYTE, imageData);

    // Step 6: Unbind the texture
    glBindTexture(GL_TEXTURE_2D, 0);
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