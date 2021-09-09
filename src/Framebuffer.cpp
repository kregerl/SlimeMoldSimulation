#include "Framebuffer.h"


Framebuffer::Framebuffer(int width, int height, GLenum access) : Framebuffer(width, height, access,
                                                                             GL_COLOR_ATTACHMENT0) {

}

Framebuffer::Framebuffer(int width, int height, GLenum access, GLuint texture) {
    glGenFramebuffers(1, &m_fbo);
    m_colorTexture = new Texture(width, height, access);
    m_colorTexture->use();
    bind();
    glFramebufferTexture2D(GL_FRAMEBUFFER, texture, GL_TEXTURE_2D, m_colorTexture->id, 0);
    //    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, m_colorTexture->id, 0);
    checkErrors();
    unbind();
}

Framebuffer::~Framebuffer() {
    glDeleteFramebuffers(1, &m_fbo);
    delete m_colorTexture;
}

void Framebuffer::checkErrors() {
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        std::cout << "ERROR::FRAMEBUFFER - Framebuffer is incomplete!" << std::endl;
    }
}

void Framebuffer::bind() {
    m_colorTexture->use();
    GLenum drawBuffers[1] = {GL_COLOR_ATTACHMENT0};
    glDrawBuffers(1, drawBuffers);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_fbo);
    glViewport(0, 0, m_colorTexture->getWidth(), m_colorTexture->getHeight());
//    glViewport(0, 0, m_colorTexture->getWidth() / 2, m_colorTexture->getHeight() / 2);
}

void Framebuffer::unbind() {
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
}

Texture *Framebuffer::getTextureAttachment() const {
    return m_colorTexture;
}

GLuint Framebuffer::getId() const {
    return m_fbo;
}