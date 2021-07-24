#ifndef SLIMEMOLDSIMULATION_SETTINGS_H
#define SLIMEMOLDSIMULATION_SETTINGS_H

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#include <glm/vec4.hpp>
#include "Window.h"

#define GLSL_VERSION "#version 460 core"
#define AGENT_PICKER_SIZE 4
#define EFFECT_PICKER_SIZE 3


class Settings {
public:

    Settings(Window *window);

    ~Settings();

    void init();

    static void draw();

    static void shutdown();

    glm::vec4 getColor();

    [[maybe_unused]] [[nodiscard]]
    float getSpeed() const;

    [[maybe_unused]] [[nodiscard]]
    float getTurnSpeed() const;

    [[maybe_unused]] [[nodiscard]]
    float getSensorOffsetDistance() const;

    [[maybe_unused]] [[nodiscard]]
    float getSensorAngle() const;

    [[maybe_unused]] [[nodiscard]]
    int getSensorSize() const;

    [[maybe_unused]] [[nodiscard]]
    bool shouldBlur() const;


private:
    bool m_showWindow = true;
    bool m_blur = true;
    bool m_evaporate = true;
    float m_agentColor[AGENT_PICKER_SIZE]{};
    float m_effectColor[EFFECT_PICKER_SIZE]{};
    float m_simulationSpeed = 80.0f;
    float m_turnSpeed = 100.0f;
    float m_sensorOffsetDistance = 16.0f;
    float m_sensorAngle = 0.6f;
    int m_sensorSize = 3;
};


#endif //SLIMEMOLDSIMULATION_SETTINGS_H
