#include "Framebuffer.h"


Framebuffer::Framebuffer(int width, int height, GLenum access) {
    glGenFramebuffers(1, &this->m_fbo);
    this->m_colorTexture = new Texture(width, height, access);
    this->m_colorTexture->use();
    this->bind();
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->m_colorTexture->id, 0);
//    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, this->m_colorTexture->id, 0);
    this->checkErrors();
    this->unbind();
}

Framebuffer::~Framebuffer() {
    glDeleteFramebuffers(1, &this->m_fbo);
    delete this->m_colorTexture;
}

void Framebuffer::checkErrors() {
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        std::cout << "ERROR::FRAMEBUFFER - Framebuffer is incomplete!" << std::endl;
    }
}

void Framebuffer::bind() {
    this->m_colorTexture->use();
    GLenum drawBuffers[1] = {GL_COLOR_ATTACHMENT0};
    glDrawBuffers(1, drawBuffers);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, this->m_fbo);
    glViewport(0, 0, this->m_colorTexture->getWidth(), this->m_colorTexture->getHeight());
//    glViewport(0, 0, this->m_colorTexture->getWidth() / 2, this->m_colorTexture->getHeight() / 2);
}

void Framebuffer::unbind() {
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
}

Texture *Framebuffer::getTextureAttachment() const {
    return this->m_colorTexture;
}