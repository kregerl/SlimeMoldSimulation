#ifndef SLIMEMOLDSIMULATION_SPRITE_H
#define SLIMEMOLDSIMULATION_SPRITE_H


#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/vec4.hpp>

class Sprite {
public:
    Sprite(float x0, float y0, float x1, float y1, GLuint textureId);

    ~Sprite();

    void draw() const;

private:
    GLuint m_vao = 0, m_vbo = 0;
    GLuint m_textureId = 0;
};


#endif
