#include "Sprite.h"

Sprite::Sprite(float x0, float y0, float x1, float y1, GLuint textureId) : m_textureId(textureId) {
    glGenBuffers(1, &m_vbo);
    glGenVertexArrays(1, &m_vao);

    glBindVertexArray(m_vao);

    float vertices[] = {
            x1, y0, 1.0f, 1.0f,
            x1, y1, 1.0f, 0.0f,
            x0, y0, 0.0f, 1.0f,
            x1, y1, 1.0f, 0.0f,
            x0, y1, 0.0f, 0.0f,
            x0, y0, 0.0f, 1.0f
//            x1, y0, 0.5f, 0.5f,
//            x1, y1, 0.5f, 0.0f,
//            x0, y0, 0.0f, 0.5f,
//            x1, y1, 0.5f, 0.0f,
//            x0, y1, 0.0f, 0.0f,
//            x0, y0, 0.0f, 0.5f
    };
    // Texture coords are windowSize / textureSize

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices[0], GL_STATIC_DRAW);

    // (void *) 0 can be changed to nullptr
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *) (2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(m_vao);

}

Sprite::~Sprite() {
    glDeleteBuffers(1, &this->m_vbo);
    glDeleteVertexArrays(1, &this->m_vao);
}

void Sprite::draw() const {
    glBindTexture(GL_TEXTURE_2D, this->m_textureId);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindBuffer(GL_ARRAY_BUFFER, 0);


}