#ifndef SLIMEMOLDSIMULATION_TEXTURE_H
#define SLIMEMOLDSIMULATION_TEXTURE_H


#include <glad/glad.h>
#include <iostream>
#include <filesystem>
#include "stb_image.h"

class Texture {
private:
    GLenum m_texAccess = 0;
    int m_width = 0, m_height = 0;

    void checkErrors(unsigned char *, GLint imageChannels) const;

public:
    GLuint id = 0;

    Texture(int width, int height, GLenum access);

    Texture(const std::string &fileName, GLenum access, GLint imageChannels = GL_RGBA);

    ~Texture() = default;

    [[nodiscard]]
    int getWidth() const;

    [[nodiscard]]
    int getHeight() const;

    [[nodiscard]]
    void *getImGuiTextureId() const;

    void use() const;
};


#endif
