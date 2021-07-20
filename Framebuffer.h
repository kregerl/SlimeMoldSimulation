
#ifndef SLIMEMOLDSIMULATION_FRAMEBUFFER_H
#define SLIMEMOLDSIMULATION_FRAMEBUFFER_H

#include<glad/glad.h>
#include "Texture.h"

class Framebuffer {
public:
    Framebuffer(int width, int height, GLenum access);

    ~Framebuffer();

    void validate();

    void bind();

    void unbind();


private:
    GLuint m_fbo;
    Texture *m_colorTexture;


};


#endif
