#ifndef SLIMEMOLDSIMULATION_FRAMEBUFFER_H
#define SLIMEMOLDSIMULATION_FRAMEBUFFER_H

#include<glad/glad.h>
#include "Texture.h"

class Framebuffer {
public:
    Framebuffer(int width, int height, GLenum access);

    Framebuffer(int width, int height, GLenum access, GLuint texture);

    ~Framebuffer();

    void checkErrors();

    void bind();

    void unbind();

    Texture *getTextureAttachment() const;

    GLuint getId() const;


private:
    GLuint m_fbo;
    Texture *m_colorTexture;


};


#endif
