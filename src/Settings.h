#ifndef SLIMEMOLDSIMULATION_SETTINGS_H
#define SLIMEMOLDSIMULATION_SETTINGS_H

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <glm/glm.hpp>
#include <vector>
#include <fstream>
#include <yaml-cpp/node/node.h>
#include <yaml-cpp/node/parse.h>
#include <yaml-cpp/emitter.h>
#include <yaml-cpp/stlemitter.h>

#include "Window.h"
#include "Texture.h"
#include "AgentSystem.h"
#include "Framebuffer.h"

#define GLSL_VERSION "#version 460 core"
#define IMAGE_BUTTON_SIZE ImVec2(24, 24)
#define PICKER_SIZE 3

const static std::string spawnPositionNames[] = {"Center", "Circle", "Edges", "Random"};
const static SpawnPosition spawnPositions[] = {CENTER, CIRCLE, EDGES, RANDOM};

const static YAML::Emitter &operator<<(YAML::Emitter &out, const glm::vec3 &vec) {
    std::vector<float> result;
    result.push_back(vec.x);
    result.push_back(vec.y);
    result.push_back(vec.z);
    out << YAML::BeginSeq << YAML::Flow << result << YAML::EndSeq;
    return out;
}

const static YAML::Emitter &operator<<(YAML::Emitter &out, const SpeciesSpec &spec) {
    out << YAML::BeginMap;
    out << YAML::Key << "Speed" << YAML::Value << spec.speed;
    out << YAML::Key << "Turn Speed" << YAML::Value << spec.turnSpeed;
    out << YAML::Key << "Sensor Offset" << YAML::Value << spec.sensorOffsetDistance;
    out << YAML::Key << "Sensor Angle" << YAML::Value << spec.sensorAngleOffset;
    out << YAML::Key << "Sensor Size" << YAML::Value << spec.sensorSize;
    out << YAML::Key << "Color" << YAML::Value << spec.color;
    out << YAML::EndMap;
    return out;
}

class Settings {
public:


    bool m_shouldReset = false;
    glm::vec3 speciesColor1 = {1.0, 0.0, 0.0};
    glm::vec3 speciesColor2 = {0.0, 1.0, 0.0};
    glm::vec3 speciesColor3 = {0.0, 0.0, 1.0};

    Settings(Window *window, AgentSystem *system);

    ~Settings() = default;

    void init();

    static void draw();

    static void shutdown();


    [[maybe_unused]] [[nodiscard]]
    glm::vec3 getColor() const;

    [[maybe_unused]] [[nodiscard]]
    glm::vec3 getColorMod() const;


    [[maybe_unused]] [[nodiscard]]
    float getSpeed() const;

    [[maybe_unused]] [[nodiscard]]
    float getTurnSpeed() const;

    [[maybe_unused]] [[nodiscard]]
    float getSensorOffsetDistance() const;

    [[maybe_unused]] [[nodiscard]]
    float getSensorAngle() const;

    [[maybe_unused]] [[nodiscard]]
    float getDiffuseSpeed() const;

    [[maybe_unused]] [[nodiscard]]
    float getEvaporateSpeed() const;

    [[maybe_unused]] [[nodiscard]]
    int getSensorSize() const;

    [[maybe_unused]] [[nodiscard]]
    bool shouldBlur() const;

    [[maybe_unused]] [[nodiscard]]
    bool isRunning() const;

    [[maybe_unused]]
    void setPlaying(bool playing);

    [[maybe_unused]] [[nodiscard]]
    bool shouldReset() const;




private:
//    std::vector<SpeciesSpec> &specs;

    AgentSystem *m_agentSystem;
    Window *m_window;

    Texture *m_currentTexture;
    Texture *m_playTexture;
    Texture *m_pauseTexture;
    Texture *m_resetTexture;


    bool m_playing = true;
    bool m_showWindow = true;
    bool m_blur = true;
    float m_agentColor[PICKER_SIZE]{};
    float m_effectColor[PICKER_SIZE]{};
    float m_simulationSpeed = 80.0f;
    float m_turnSpeed = 100.0f;
    float m_sensorOffsetDistance = 16.0f;
    float m_sensorAngle = 0.6f;
    float m_diffuseSpeed = 10.0;
    float m_evaporateSpeed = 0.4f;
    int m_sensorSize = 3;
    char *m_numSpecies;
    char *m_spawnPosition;
    char *m_speciesItems[MAX_SPECIES]{};

    void exportSettings();
};


#endif //SLIMEMOLDSIMULATION_SETTINGS_H
