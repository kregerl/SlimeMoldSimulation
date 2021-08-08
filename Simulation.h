#ifndef SLIMEMOLDSIMULATION_SIMULATION_H
#define SLIMEMOLDSIMULATION_SIMULATION_H

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <random>
#include <algorithm>
#include <sys/random.h>
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
//    const size_t m_numAgents;
//    std::vector<Agent> m_agents;
//    std::vector<SpeciesSpec> m_speciesSpecs;

    Window *m_window;
    AgentSystem *m_agentSystem;
    Settings *m_settings;
    Shader *m_shader;
    ComputeShader *m_agentShader;
    ComputeShader *m_effectShader;
    Framebuffer *m_framebuffer;
    Sprite *m_sprite;

public:
    Simulation(int width, int height);

    ~Simulation() = default;

    void run();

    void clearColor();
};


#endif
