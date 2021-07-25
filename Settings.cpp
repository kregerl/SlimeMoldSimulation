#include <glm/vec3.hpp>
#include "Settings.h"


Settings::Settings(Window *window) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void) io;

    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window->getWindow(), true);
    ImGui_ImplOpenGL3_Init(GLSL_VERSION);
    std::fill(this->m_agentColor, this->m_agentColor + PICKER_SIZE, 1);
    std::fill(this->m_effectColor, this->m_effectColor + PICKER_SIZE, 0);

}


void Settings::init() {

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // Add content to window
    if (this->m_showWindow) {
        ImGui::Begin("Settings", &this->m_showWindow);

        ImGui::ColorEdit3("Color", this->m_agentColor);

        ImGui::Button("Play");
        ImGui::SameLine();
        ImGui::Button("Pause");
        ImGui::SameLine();
        ImGui::Button("Reset");

        if (ImGui::CollapsingHeader("Effect Settings")) {
            ImGui::Checkbox("Blur", &this->m_blur);
            ImGui::SliderFloat("Diffuse Speed", &this->m_diffuseSpeed, 0.0f, 25.0f);
            ImGui::SliderFloat("Evaporate Speed", &this->m_evaporateSpeed, 0.0f, 2.0f);
            if (this->m_blur && this->m_diffuseSpeed > 0 && this->m_evaporateSpeed > 0) {
                ImGui::ColorEdit3("Color Mod", this->m_effectColor,
                                  ImGuiColorEditFlags_NoPicker | ImGuiColorEditFlags_Float);
            }
        }


        if (ImGui::CollapsingHeader("Agent Settings")) {
            ImGui::SliderFloat("Speed", &this->m_simulationSpeed, 0.0f, 300.0f);
            ImGui::SliderFloat("Turn Speed", &this->m_turnSpeed, 0.0f, 300.0f);
            ImGui::SliderFloat("Sensor Offset", &this->m_sensorOffsetDistance, 0.0f, 50.0f);
            ImGui::SliderFloat("Sensor Angle", &this->m_sensorAngle, 0.0f, 2.0f);
            ImGui::SliderInt("Sensor Size", &this->m_sensorSize, 0, 10);
        }


        if (ImGui::Button("Close Me"))
            this->m_showWindow = false;
        ImGui::End();
    }

    // Rendering
    ImGui::Render();
}

void Settings::draw() {
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Settings::shutdown() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

glm::vec3 Settings::getColor() const {
    return glm::vec3(this->m_agentColor[0], this->m_agentColor[1], this->m_agentColor[2]);
};

glm::vec3 Settings::getColorMod() const {
    return glm::vec3(this->m_effectColor[0], this->m_effectColor[1], this->m_effectColor[2]);
}

float Settings::getSpeed() const {
    return this->m_simulationSpeed;
}

float Settings::getSensorAngle() const {
    return this->m_sensorAngle;
}

float Settings::getSensorOffsetDistance() const {
    return this->m_sensorOffsetDistance;
}

float Settings::getTurnSpeed() const {
    return this->m_turnSpeed;
}

float Settings::getDiffuseSpeed() const {
    return this->m_diffuseSpeed;
}

float Settings::getEvaporateSpeed() const {
    return this->m_evaporateSpeed;
}

int Settings::getSensorSize() const {
    return this->m_sensorSize;
}

bool Settings::shouldBlur() const {
    return this->m_blur;
}
