#include "Window.h"

// Mark window unused for now.
static void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

// Store the fullscreen bool somewhere to allow ImGui to change fullscreen / windowed
Window::Window(const int width, const int height, const std::string &title, bool isFullscreen) : m_width(isFullscreen ? 1920 : width),
                                                                              m_height(isFullscreen ? 1080 : height) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_window = glfwCreateWindow(m_width, m_height, title.c_str(),isFullscreen  ? glfwGetPrimaryMonitor() : nullptr, nullptr);

    if (m_window == nullptr) {
        std::cout << "ERROR: Cant open null util." << std::endl;
        glfwTerminate();
    }
    glfwMakeContextCurrent(m_window);
    glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);
//    glfwSetWindowSizeCallback(m_window, window_resize_callback);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "ERROR: Failed to load GLAD" << std::endl;
        glfwTerminate();
    }

    std::cout << glGetString(GL_VERSION) << std::endl;
}

Window::~Window() {
    glfwTerminate();
}

void Window::use() {

    double currentFrame = glfwGetTime();
    m_deltaTime = currentFrame - m_prevFrame;
    m_prevFrame = currentFrame;

    processInput();
}

void Window::close() {
    glfwDestroyWindow(m_window);
    glfwTerminate();
}


void Window::poll() {
    glfwSwapBuffers(m_window);
    glfwPollEvents();
}

int Window::getWidth() const {
    return m_width;
}

int Window::getHeight() const {
    return m_height;
}

double Window::getDeltaTime() const {
    return m_deltaTime;
}

bool Window::shouldClose() {
    return glfwWindowShouldClose(m_window);
}

void Window::processInput() {
    if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(m_window, true);
    if (glfwGetKey(m_window, GLFW_KEY_SPACE) == GLFW_PRESS)
        showWindow = true;

}

