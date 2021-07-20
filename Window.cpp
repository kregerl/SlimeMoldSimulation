#include "Window.h"

Window::Window(const int width, const int height, const std::string &title) : m_width(width),
                                                                              m_height(height) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    this->m_window = glfwCreateWindow(this->m_width, this->m_height, title.c_str(), nullptr, nullptr);

    if (this->m_window == nullptr) {
        std::cout << "ERROR: Cant open null util." << std::endl;
        glfwTerminate();
    }
    glfwMakeContextCurrent(this->m_window);
//    glfwSetFramebufferSizeCallback(this->m_window, framebuffer_size_callback);
//    glfwSetWindowSizeCallback(this->m_window, window_resize_callback);

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
    glfwTerminate();
}


void Window::unuse() {
    glfwSwapBuffers(this->m_window);
    glfwPollEvents();
}

int Window::getWidth() const {
    return this->m_width;
}

int Window::getHeight() const {
    return this->m_height;
}

float Window::getDeltaTime() const {
    return this->m_deltaTime;
}

bool Window::shouldClose() {
    return glfwWindowShouldClose(this->m_window);
}

void Window::processInput() {
    if (glfwGetKey(this->m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(this->m_window, true);
    if (glfwGetKey(this->m_window, GLFW_KEY_SPACE) == GLFW_PRESS)
        this->m_isPaused = !m_isPaused;
}