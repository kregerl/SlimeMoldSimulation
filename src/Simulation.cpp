#include "Simulation.h"


Simulation::Simulation(int width, int height) {
    m_window = new Window(width, height, "Slime Mold Simulation");
    m_agentSystem = new AgentSystem(m_window->getWidth(), m_window->getHeight(), NUM_AGENTS);
    m_settings = new Settings(m_window, m_agentSystem);

    // Move to a relative execution path.

    m_shader = new Shader(".\\shaders\\main.vert",
                          ".\\shaders\\main.frag");
    // Move to a relative execution path.
    m_agentShader = new ComputeShader(".\\shaders\\agents.comp");

    m_agentShader->useSSBO(1, m_agentSystem->getNumAgents() * sizeof(Agent),
                           &m_agentSystem->agents[0]);
    m_agentShader->useUBO(2, MAX_SPECIES * sizeof(SpeciesSpec), &m_agentSystem->speciesSpecs[0]);
    // Move to a relative execution path.
    m_effectShader = new ComputeShader(".\\shaders\\effects.comp");
    m_colorShader = new ComputeShader(".\\shaders\\color.comp");


    m_simulationFramebuffer = new Framebuffer(m_window->getWidth(), m_window->getHeight(), GL_READ_WRITE);


    m_sprite = new Sprite(-1.0f, 1.0f, 1.0f, -1.0f, m_simulationFramebuffer->getTextureAttachment()->id);


}


void Simulation::run() {
    while (!m_window->shouldClose()) {
        m_window->use();
//      Init frames
        m_settings->init();
//      Render simulation
//        --------------------------------------------

//      Add a small delay to the start of the simulation to avoid startup problems with spawning
        if (glfwGetTime() > 0.75) {
            double deltaTime = m_window->getDeltaTime();


            m_simulationFramebuffer->bind();
            if (m_settings->shouldReset()) {
                glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
                glClear(GL_COLOR_BUFFER_BIT);
                m_settings->parseYAML();
                m_settings->m_shouldReset = !m_settings->m_shouldReset;
                ComputeShader::clearSSBO(1);
                m_settings->setPlaying(m_settings->shouldRandomizePresets());
                m_agentSystem->init(m_window->getWidth(), m_window->getHeight());
                m_agentShader->useSSBO(1, m_agentSystem->getNumAgents() * sizeof(Agent),
                                       &m_agentSystem->agents[0]);

            }


            m_agentShader->use();
            m_agentShader->useUBO(2, MAX_SPECIES * sizeof(SpeciesSpec), &m_agentSystem->speciesSpecs[0]);
            m_agentShader->setInt("currentNumSpecies", m_agentSystem->currentNumSpecies);
            m_agentShader->setVec3("color", m_settings->getColor());
            m_agentShader->setFloat("deltaTime", static_cast<float>(deltaTime));
            m_agentShader->setFloat("speed", m_settings->getSpeed());
            m_agentShader->setFloat("turnSpeed", m_settings->getSpeed());
            m_agentShader->setFloat("sensorOffsetDistance", m_settings->getSensorOffsetDistance());
            m_agentShader->setFloat("sensorAngleOffset", m_settings->getSensorAngle());
            m_agentShader->setInt("sensorSize", m_settings->getSensorSize());
            m_agentShader->setBool("isRunning", m_settings->isRunning());
            ComputeShader::dispatch(m_agentSystem->getNumAgents() / 64, 1, 1);


            glMemoryBarrier(GL_COLOR_BUFFER_BIT);


            m_colorShader->use();
            m_colorShader->setVec3("colors", m_agentSystem->getSpeciesColors(), MAX_SPECIES);
            ComputeShader::dispatch(m_window->getWidth() / 8, m_window->getHeight() / 8, 1);

            glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT | GL_SHADER_STORAGE_BARRIER_BIT);

            m_effectShader->use();
            m_effectShader->setVec3("colorMod", m_settings->getColorMod());
            m_effectShader->setFloat("deltaTime", static_cast<float>(deltaTime));
            m_effectShader->setFloat("diffuseSpeed", m_settings->getDiffuseSpeed());
            m_effectShader->setFloat("evaporationSpeed", m_settings->getEvaporateSpeed());
            m_effectShader->setBool("shouldBlur", m_settings->shouldBlur());
            m_effectShader->setBool("isRunning", m_settings->isRunning());
            ComputeShader::dispatch(m_window->getWidth() / 8, m_window->getHeight() / 8, 1);


            glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
            m_simulationFramebuffer->unbind();


            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            m_shader->use();
            m_sprite->draw();

//      --------------------------------------------

            Settings::draw();
            m_window->poll();
        }

    }

    Settings::shutdown();
    m_window->close();
}

