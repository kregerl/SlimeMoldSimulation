#ifndef SLIMEMOLDSIMULATION_TEXTURE_H
#define SLIMEMOLDSIMULATION_TEXTURE_H

#include <glad/glad.h>
#include <iostream>

class Texture {
private:
    GLenum m_texAccess;
public:
    GLuint id = 0;

    Texture(int width, int height, GLenum access);

    ~Texture() = default;

    void use();
};


#endif
