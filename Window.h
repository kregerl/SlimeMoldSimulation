#ifndef SLIMEMOLDSIMULATION_WINDOW_H
#define SLIMEMOLDSIMULATION_WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdint>

class Window {
public:
    Window(const int width, const int height, const std::string &title);

    ~Window();

    void use();

    void close();

    void poll();

    bool shouldClose();

    int getWidth() const;

    int getHeight() const;

    float getDeltaTime() const;

    bool isPaused() { return this->m_isPaused; }

    GLFWwindow *getWindow() { return this->m_window; }

private:
    bool m_isPaused = false;
    const int m_width, m_height;
    float m_deltaTime = 0.0, m_prevFrame = 0.0;
    GLFWwindow *m_window;

    void processInput();

};


#endif
