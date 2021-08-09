#ifndef SLIMEMOLDSIMULATION_AGENTSYSTEM_H
#define SLIMEMOLDSIMULATION_AGENTSYSTEM_H

#include <glm/glm.hpp>
#include <vector>
#include <random>

#define TWO_PI 6.2831853f
#define MAX_SPECIES 10

struct Agent {
    float x, y;
    float angle;
    int speciesIndex;
};

enum SpawnPosition {
    CENTER, CIRCLE, EDGES, RANDOM
};

struct SpeciesSpec {
    glm::vec3 color;
    float speed;
    float turnSpeed;
    float sensorOffsetDistance;
    float sensorAngleOffset;
    int sensorSize;
};
const static SpeciesSpec DEFAULT_SPECIES_SPEC = SpeciesSpec{glm::vec3(1.0f, 1.0f, 1.0f), 80.0f, 100.0f, 16.0f, 0.6f, 3};

class AgentSystem {
public:
    std::vector<Agent> agents;
    std::vector<SpeciesSpec> speciesSpecs;

    AgentSystem(int width, int height, size_t numAgents);

    ~AgentSystem();

    int getNumAgents() const;

private:
    const size_t m_numAgents;
    SpawnPosition m_spawnPos;

    void init(int width, int height);

};


#endif