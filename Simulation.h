#ifndef SLIMEMOLDSIMULATION_SIMULATION_H
#define SLIMEMOLDSIMULATION_SIMULATION_H
#define TWO_PI 6.2831853f

#include <glad/glad.h>
#include <vector>
#include <random>
#include <algorithm>
#include <sys/random.h>
#include "Window.h"
#include "Shader.h"
#include "ComputeShader.h"
#include "Texture.h"
#include "Sprite.h"

struct Agent {
    float x, y;
    float angle;
    bool shouldTurn;
};

class Simulation {
private:
    const size_t m_numAgents;
    std::vector<Agent> m_agents;

    Window *m_window;
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
