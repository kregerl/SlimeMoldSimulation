#version 460 core

in vec2 coords;
uniform sampler2D tex;
out vec4 FragColor;

void main() {
    FragColor = texture(tex, coords);
}