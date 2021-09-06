#ifndef SLIMEMOLDSIMULATION_SIMULATION_H
#define SLIMEMOLDSIMULATION_SIMULATION_H

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <random>
#include <algorithm>
#include <random>
#include "Window.h"
#include "Settings.h"
#include "Shader.h"
#include "ComputeShader.h"
#include "Texture.h"
#include "Framebuffer.h"
#include "Sprite.h"
#include "AgentSystem.h"

#define NUM_AGENTS 200000

class Simulation {
private:

    Window *m_window;
    AgentSystem *m_agentSystem;
    Settings *m_settings;
    Shader *m_shader;
    ComputeShader *m_agentShader;
    ComputeShader *m_effectShader;
    ComputeShader *m_colorShader;
    Framebuffer *m_simulationFramebuffer;
    Sprite *m_sprite;

public:
    Simulation(int width, int height);

    ~Simulation() = default;

    void run();

    void clearColor();
};


#endif
