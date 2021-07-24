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
#include "Sprite.h"

#define TWO_PI 6.2831853f


struct Agent {
    float x, y;
    float angle;
    bool shouldTurn;
};

enum SpawnPosition {
    CENTER, CIRCLE, EDGES, RANDOM, MULTI_CIRCLE
};

class Simulation {
private:
    const size_t m_numAgents;
    std::vector<Agent> m_agents;

    Window *m_window;
    Settings *m_settings;
    Shader *m_shader;
    ComputeShader *m_agentShader;
    ComputeShader *m_effectShader;
    Texture *m_inTexture;
    Texture *m_outTexture;
    Sprite *m_sprite;

    void setupAgents(int width, int height);

public:
    Simulation(int width, int height);

    ~Simulation() = default;

    void run();
};


#endif
