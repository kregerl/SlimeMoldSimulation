#include "Texture.h"


Texture::Texture(int width, int height, GLenum access) : m_texAccess(access), m_width(width), m_height(height) {
    glGenTextures(1, &id);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, this->m_width, this->m_height, 0, GL_RGBA, GL_FLOAT, nullptr);
    std::cout << this->id << std::endl;
}

Texture::Texture(const std::string &fileName, GLenum access, GLint imageChannels) : m_texAccess(access) {
    glGenTextures(1, &this->id);
    glBindTexture(GL_TEXTURE_2D, this->id);

    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // 7/28 unused for now, changed to a nullptr since it is unused.
    // 7/31 new nrChannels to determine the image channels, 1 GL_R, 2 GL_RG, 3 GL_RGB, 4 GL_RGBA
//    int nrChannels;
    // Implement a get filesystem path.
    unsigned char *data = stbi_load(fileName.c_str(), &this->m_width, &this->m_height, /*nrChannels*/ nullptr, 0);
    this->checkErrors(data, imageChannels);
    stbi_image_free(data);

}

void Texture::use() const {
    glBindImageTexture(0, id, 0, GL_FALSE, 0, this->m_texAccess, GL_RGBA32F);
}

void Texture::checkErrors(unsigned char *data, GLint imageChannels) const {
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, imageChannels, this->m_width, this->m_height, 0, imageChannels, GL_UNSIGNED_BYTE,
                     data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture" << std::endl;
    }
}

int Texture::getWidth() const {
    return this->m_width;
}

int Texture::getHeight() const {
    return this->m_height;
}

void *Texture::getImGuiTextureId() const {
    // Cast to size_t to avoid compiler warnings.
    return (void *) (size_t) this->id;
}