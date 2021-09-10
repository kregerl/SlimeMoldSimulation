#ifndef SLIMEMOLDSIMULATION_WINDOW_H
#define SLIMEMOLDSIMULATION_WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdint>

class Window {
public:
    Window(int width, int height, const std::string &title, bool isFullscreen = false);

    ~Window();

    void use();

    void close();

    void poll();

    bool shouldClose();

    [[nodiscard]]
    int getWidth() const;

    [[nodiscard]]
    int getHeight() const;

    [[nodiscard]]
    double getDeltaTime() const;

    [[nodiscard]]
    double getTimePassed() const;

    [[nodiscard]]
    void resetTimePassed();

    [[nodiscard]]
    bool isPaused() const { return m_isPaused; }

    GLFWwindow *getWindow() { return m_window; }

    bool showWindow = true;

    void startTimer();

private:
    bool m_isPaused = false;
    const int m_width, m_height;
    double m_deltaTime = 0.0f, m_prevFrame = 0.0f;
    // Used for configurable timer.
    double m_timerStart = 0.0f, m_timePassed = 0.0f;
    GLFWwindow *m_window;

    void processInput();

};


#endif
