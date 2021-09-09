#include "AgentSystem.h"

AgentSystem::AgentSystem(int width, int height, size_t numAgents) : m_numAgents(numAgents),
                                                                    m_spawnPos(SpawnPosition::CENTER) {
    speciesSpecs = {SpeciesSpec(glm::vec3(1.0f, 0.0f, 0.0f)), SpeciesSpec(glm::vec3(0.0f, 1.0f, 0.0f)),
                    SpeciesSpec(glm::vec3(0.0f, 0.0f, 1.0f))};
    init(width, height);
}


void AgentSystem::init(int width, int height) {
    agents.resize(m_numAgents);


    std::mt19937 random;
    std::uniform_real_distribution<float> posX(0, (float) width);
    std::uniform_real_distribution<float> posY(0, (float) height);
    std::uniform_real_distribution<float> angle(0, TWO_PI);
    std::uniform_int_distribution<int> species(0, currentNumSpecies - 1);

    switch (m_spawnPos) {
        case CIRCLE: {
            const float radius = std::min(width, height) / 2.0f;
            float x, y;
            for (size_t i = 0; i < m_numAgents; i++) {
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
            for (size_t i = 0; i < m_numAgents; i++) {
                int index = species(random);
                agents.at(i) = {centerX, centerY, angle(random), index};
            }
            break;
        }
        case EDGES: {
            for (size_t i = 0; i < m_numAgents; i++) {
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
            for (size_t i = 0; i < m_numAgents; i++) {
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
    return m_numAgents;
}


void AgentSystem::setSpawnPos(SpawnPosition spawnPos) {
    m_spawnPos = spawnPos;
}

std::vector<glm::vec3> AgentSystem::getSpeciesColors() {
    std::vector<glm::vec3> colors;
    for (auto &spec: speciesSpecs) {
        colors.push_back(spec.color);
    }

    return colors;
}

