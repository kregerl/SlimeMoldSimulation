#include "Simulation.h"


Simulation::Simulation(int width, int height) {
    this->m_agentSystem = new AgentSystem(width, height, NUM_AGENTS);
    this->m_window = new Window(width, height, "Slime Mold Simulation");
    this->m_settings = new Settings(this->m_window, this->m_agentSystem);

    this->m_shader = new Shader("/home/loucas/CLionProjects/SlimeMoldSimulation/shaders/main.vert",
                                "/home/loucas/CLionProjects/SlimeMoldSimulation/shaders/main.frag");

    this->m_agentShader = new ComputeShader("/home/loucas/CLionProjects/SlimeMoldSimulation/shaders/agents.comp");

    this->m_agentShader->useSSBO(1, this->m_agentSystem->getNumAgents() * sizeof(Agent),
                                 &this->m_agentSystem->agents[0]);
    this->m_agentShader->useUBO(2, MAX_SPECIES * sizeof(SpeciesSpec), &this->m_agentSystem->speciesSpecs[0]);
    this->m_effectShader = new ComputeShader("/home/loucas/CLionProjects/SlimeMoldSimulation/shaders/effects.comp");
    this->m_colorShader = new ComputeShader("/home/loucas/CLionProjects/SlimeMoldSimulation/shaders/color.comp");


    this->m_simulationFramebuffer = new Framebuffer(width, height, GL_READ_WRITE);
//    this->m_displayFramebuffer = new Framebuffer(width, height, GL_READ_WRITE);


    this->m_sprite = new Sprite(-1.0f, 1.0f, 1.0f, -1.0f, this->m_simulationFramebuffer->getTextureAttachment()->id);


}


void Simulation::run() {
    while (!this->m_window->shouldClose()) {
        this->m_window->use();
//        Init frames
        this->m_settings->init();
//        Render simulation
//        --------------------------------------------
        float deltaTime = m_window->getDeltaTime();

        this->m_simulationFramebuffer->bind();
        if (this->m_settings->shouldReset()) {
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            this->m_settings->m_shouldReset = !this->m_settings->m_shouldReset;
            this->m_agentShader->clearSSBO(1);
            this->m_settings->setPlaying(false);
            this->m_agentSystem->init(this->m_window->getWidth(), this->m_window->getHeight());
            this->m_agentShader->useSSBO(1, this->m_agentSystem->getNumAgents() * sizeof(Agent),
                                         &this->m_agentSystem->agents[0]);
        }


        this->m_agentShader->use();
        this->m_agentShader->useUBO(2, MAX_SPECIES * sizeof(SpeciesSpec), &this->m_agentSystem->speciesSpecs[0]);
        this->m_agentShader->setInt("currentNumSpecies", this->m_agentSystem->currentNumSpecies);
        this->m_agentShader->setVec3("color", this->m_settings->getColor());
        this->m_agentShader->setFloat("deltaTime", deltaTime);
        this->m_agentShader->setFloat("speed", this->m_settings->getSpeed());
        this->m_agentShader->setFloat("turnSpeed", this->m_settings->getSpeed());
        this->m_agentShader->setFloat("sensorOffsetDistance", this->m_settings->getSensorOffsetDistance());
        this->m_agentShader->setFloat("sensorAngleOffset", this->m_settings->getSensorAngle());
        this->m_agentShader->setInt("sensorSize", this->m_settings->getSensorSize());
        this->m_agentShader->setBool("isRunning", this->m_settings->isRunning());
        ComputeShader::dispatch(this->m_agentSystem->getNumAgents() / 64, 1, 1);


        glMemoryBarrier(GL_COLOR_BUFFER_BIT);

        this->m_colorShader->use();
        this->m_colorShader->setVec3("speciesColor1", this->m_settings->speciesColor1);
        this->m_colorShader->setVec3("speciesColor2", this->m_settings->speciesColor2);
        this->m_colorShader->setVec3("speciesColor3", this->m_settings->speciesColor3);
        ComputeShader::dispatch(this->m_window->getWidth() / 8, this->m_window->getHeight() / 8, 1);

        glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT | GL_SHADER_STORAGE_BARRIER_BIT);

        this->m_effectShader->use();
        this->m_effectShader->setVec3("colorMod", this->m_settings->getColorMod());
        this->m_effectShader->setFloat("deltaTime", deltaTime);
        this->m_effectShader->setFloat("diffuseSpeed", this->m_settings->getDiffuseSpeed());
        this->m_effectShader->setFloat("evaporationSpeed", this->m_settings->getEvaporateSpeed());
        this->m_effectShader->setBool("shouldBlur", this->m_settings->shouldBlur());
        this->m_effectShader->setBool("isRunning", this->m_settings->isRunning());
        ComputeShader::dispatch(this->m_window->getWidth() / 8, this->m_window->getHeight() / 8, 1);


        glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
        this->m_simulationFramebuffer->unbind();


        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        this->m_shader->use();
        this->m_sprite->draw();

//      --------------------------------------------

        Settings::draw();
        this->m_window->poll();
    }

    Settings::shutdown();
    this->m_window->close();
}

