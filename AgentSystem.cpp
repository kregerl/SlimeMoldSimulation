#include "AgentSystem.h"
#include <iostream>

AgentSystem::AgentSystem(int width, int height, size_t numAgents) : m_numAgents(numAgents),
                                                                    m_spawnPos(SpawnPosition::CIRCLE) {
    this->init(width, height);
}


AgentSystem::~AgentSystem() {

}

void AgentSystem::init(int width, int height) {
    this->agents.resize(this->m_numAgents);
    this->speciesSpecs.resize(MAX_SPECIES);

    for (int i = 0; i < MAX_SPECIES; i++) {
        // Working but needs to be editable by the settings class.
        // Specs should not hold the color, should be separate buffer.
        if (i == 1) {
            this->speciesSpecs[i] = SpeciesSpec{glm::vec3(1.0f, 0.5f, 1.0f), 80.0f, 100.0f, 16.0f, 0.6f, 3};
        } else {
            this->speciesSpecs[i] = DEFAULT_SPECIES_SPEC;
        }
    }


    std::mt19937 random;
    std::uniform_real_distribution<float> posX(0, (float) width);
    std::uniform_real_distribution<float> posY(0, (float) height);
    std::uniform_real_distribution<float> angle(0, TWO_PI);
    std::uniform_int_distribution<int> randIndex(0, this->currentNumSpecies - 1);

    switch (this->m_spawnPos) {
        case CIRCLE: {
            const float radius = std::min(width, height) / 2.0f;
            float x, y;
            for (size_t i = 0; i < this->m_numAgents; i++) {
                do {
                    x = posX(random);
                    y = posY(random);
                } while (powf(x - width * 0.5f, 2) + powf(y - height * 0.5f, 2) > (radius * radius));
                int index = randIndex(random);
                agents.at(i) = {x, y, angle(random), index, this->speciesColors.at(index)};


            }
            break;
        }
        case CENTER: {
            break;
        }
        case EDGES: {
            break;
        }
        case RANDOM: {
            break;
        }
        default: {
            break;
        }
    }


}


int AgentSystem::getNumAgents() const {
    return this->m_numAgents;
}