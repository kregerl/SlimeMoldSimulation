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
    this->speciesSpecs = {DEFAULT_SPECIES_SPEC, DEFAULT_SPECIES_SPEC, DEFAULT_SPECIES_SPEC};

    std::mt19937 random;
    std::uniform_real_distribution<float> posX(0, (float) width);
    std::uniform_real_distribution<float> posY(0, (float) height);
    std::uniform_real_distribution<float> angle(0, TWO_PI);
    std::uniform_int_distribution<int> species(0, this->currentNumSpecies - 1);

    switch (this->m_spawnPos) {
        case CIRCLE: {
            const float radius = std::min(width, height) / 2.0f;
            float x, y;
            for (size_t i = 0; i < this->m_numAgents; i++) {
                do {
                    x = posX(random);
                    y = posY(random);
                } while (powf(x - width * 0.5f, 2) + powf(y - height * 0.5f, 2) > (radius * radius));
                int index = species(random);
                agents.at(i) = {x, y, angle(random), index};


            }
            break;
        }
        case CENTER: {
            float centerX = width / 2.0f;
            float centerY = height / 2.0f;
            for (size_t i = 0; i < this->m_numAgents; i++) {
                int index = species(random);
                agents.at(i) = {centerX, centerY, angle(random), index};
            }
            break;
        }
        case EDGES: {
            for (size_t i = 0; i < this->m_numAgents; i++) {
                float x, y;
                int index = species(random);
                std::uniform_int_distribution<int> perimeterLength(0, 2 * width + 2 * height);
                int point = perimeterLength(random);
                if (point < (width + height)) {
                    if (point < width) {
                        x = point;
                        y = 0;
                    } else {
                        x = width;
                        y = point - width;
                    }
                } else {
                    point -= (width + height);
                    if (point < width) {
                        x = width - point;
                        y = height;
                    } else {
                        x = 0;
                        y = height - (point - width);
                    }
                }
                agents.at(i) = {x, y, angle(random), index};
            }

            break;
        }
        case RANDOM: {
            for (size_t i = 0; i < this->m_numAgents; i++) {
                int index = species(random);
                agents.at(i) = {posX(random), posY(random), angle(random), index};
            }
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

int AgentSystem::signum(int val) const {
    return (val > 0) ? 1 : ((val < 0) ? -1 : 0);
}

