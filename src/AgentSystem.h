#ifndef SLIMEMOLDSIMULATION_AGENTSYSTEM_H
#define SLIMEMOLDSIMULATION_AGENTSYSTEM_H

#include <glm/glm.hpp>
#include <vector>
#include <random>
#include <iostream>

#define TWO_PI 6.2831853f
#define MAX_SPECIES 3

struct Agent {
    float x, y;
    float angle;

    int speciesIndex;
};

enum SpawnPosition {
    CENTER, CIRCLE, EDGES, RANDOM
};

struct SpeciesSpec {
    SpeciesSpec() {}

    SpeciesSpec(glm::vec3 color) : color(color), speed(80.0f), turnSpeed(100.0f), sensorOffsetDistance(16.0f),
                                   sensorAngleOffset(0.6f), sensorSize(3) {}
    glm::vec3 color;
    float speed;
    float turnSpeed;
    float sensorOffsetDistance;
    float sensorAngleOffset;

    int sensorSize;
};


class AgentSystem {
public:
    std::vector<Agent> agents;
    std::vector<SpeciesSpec> speciesSpecs;
    int currentNumSpecies = 1;

    AgentSystem(int width, int height, size_t numAgents);

    ~AgentSystem() = default;


    [[nodiscard]] int getNumAgents() const;

    void init(int width, int height);


    void setSpawnPos(SpawnPosition spawnPos);

    std::vector<glm::vec3> getSpeciesColors();

private:
//    const SpeciesSpec DEFAULT_SPECIES_SPEC = SpeciesSpec{glm::vec3(1.0f, 1.0f, 1.0f), 80.0f, 100.0f, 16.0f, 0.6f, 3};
    const size_t m_numAgents;
    SpawnPosition m_spawnPos;

};


#endif
