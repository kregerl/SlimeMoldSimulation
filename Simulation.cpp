#include "Simulation.h"

Simulation::Simulation(int width, int height) : m_numAgents(300000) {
    this->setupAgents(width, height);
    this->m_window = new Window(width, height, "Slime Mold Simulation");

    this->m_shader = new Shader("/home/loucas/CLionProjects/SlimeMoldSimulation/shaders/main.vert",
                                "/home/loucas/CLionProjects/SlimeMoldSimulation/shaders/main.frag");

    this->m_agentShader = new ComputeShader("/home/loucas/CLionProjects/SlimeMoldSimulation/shaders/agents.comp");

    // For some reason the data portion needs to be &this->m_agents[0], using &this->m_agents does not work for some reason.
    this->m_agentShader->useSSBO(this->m_numAgents * sizeof(Agent), &this->m_agents[0]);
    this->m_effectShader = new ComputeShader("/home/loucas/CLionProjects/SlimeMoldSimulation/shaders/effects.comp");

    this->m_inTexture = new Texture(width, height, GL_READ_WRITE);
    this->m_outTexture = new Texture(width, height, GL_WRITE_ONLY);

    this->m_sprite = new Sprite(-1.0f, 1.0f, 1.0f, -1.0f, this->m_outTexture->id);
}

void Simulation::setupAgents(int width, int height) {
    this->m_agents.resize(this->m_numAgents);

    std::mt19937 random;
    std::uniform_real_distribution<float> posX(0, (float) width);
    std::uniform_real_distribution<float> posY(0, (float) height);
    std::uniform_real_distribution<float> angle(0, TWO_PI);

    for (size_t i = 0; i < this->m_numAgents; i++) {
//        this->m_agents[i] = {glm::vec2(posX(random), posY(random)), angle(random)};
        Agent agent;
        agent.x = width / 2;
        agent.y = height / 2;
//        agent.x = posX(random);
//        agent.y = posY(random);

        agent.angle = angle(random);
        agent.shouldTurn = true;
        this->m_agents[i] = agent;
    }

}


void Simulation::run() {


    while (!this->m_window->shouldClose()) {
        this->m_window->use();
        if (!this->m_window->isPaused()) {
            float deltaTime = m_window->getDeltaTime();

            this->m_inTexture->use();
            this->m_outTexture->use();

            this->m_agentShader->use();
            this->m_agentShader->setFloat("deltaTime", deltaTime);
            ComputeShader::dispatch(this->m_numAgents / 64, 1, 1);

            glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT | GL_SHADER_STORAGE_BARRIER_BIT);
            this->m_effectShader->use();
            this->m_effectShader->setFloat("deltaTime", deltaTime);
            ComputeShader::dispatch(this->m_window->getWidth() / 8, this->m_window->getHeight() / 8, 1);

            glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);

            glClearColor(0.9f, 0.9f, 0.9f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
        }

        this->m_shader->use();
        this->m_sprite->draw();
        this->m_window->unuse();
    }
}
