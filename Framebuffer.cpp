#include "Framebuffer.h"


Framebuffer::Framebuffer(int width, int height, GLenum access) {
    glGenFramebuffers(1, &this->m_fbo);
    this->m_colorTexture = new Texture(width, height, access);

    this->bind();
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->m_colorTexture->id, 0);

    this->validate();
    this->unbind();
}

Framebuffer::~Framebuffer() {
    glDeleteFramebuffers(1, &this->m_fbo);
    delete this->m_colorTexture;
}

void Framebuffer::validate() {
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        std::cout << "ERROR::FRAMEBUFFER - Framebuffer is incomplete!" << std::endl;
    }
}

void Framebuffer::bind() {
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, this->m_fbo);
}

void Framebuffer::unbind() {
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
}