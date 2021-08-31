#include "Settings.h"


Settings::Settings(Window *window, AgentSystem *system) : m_numSpecies("1"), m_agentSystem(system) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void) io;

    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window->getWindow(), true);
    ImGui_ImplOpenGL3_Init(GLSL_VERSION);
    std::fill(this->m_agentColor, this->m_agentColor + PICKER_SIZE, 1);
    std::fill(this->m_effectColor, this->m_effectColor + PICKER_SIZE, 0);

//    this->m_speciesColors.resize(3);
//    int index = 0;
//    for (int i = 0; i < 3; i++) {
//        this->m_speciesColors[i] = {0, 0, 0};
//        this->m_speciesColors[i][index++] = 1.0;
//    }

    this->m_playTexture = new Texture("/home/loucas/CLionProjects/SlimeMoldSimulation/images/play32xwhite.png",
                                      GL_READ_ONLY);
    this->m_pauseTexture = new Texture("/home/loucas/CLionProjects/SlimeMoldSimulation/images/pause32xwhite.png",
                                       GL_READ_ONLY);
    this->m_resetTexture = new Texture(
            "/home/loucas/CLionProjects/SlimeMoldSimulation/images/reset32xwhite.png",
            GL_READ_ONLY);

    this->m_currentTexture = this->m_playTexture;

    for (int i = 0; i < MAX_SPECIES; i++) {
        this->m_speciesItems[i] = strdup(std::to_string(i + 1).c_str());
    }

}


void Settings::init() {

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // Add content to window
    if (this->m_showWindow) {
        ImGui::Begin("Settings", &this->m_showWindow);


        this->m_currentTexture = this->m_playing ? this->m_pauseTexture : this->m_playTexture;

        if (ImGui::ImageButton(this->m_currentTexture->getImGuiTextureId(), IMAGE_BUTTON_SIZE)) {
            this->m_playing = !this->m_playing;
        }

        ImGui::SameLine();

        if (ImGui::ImageButton(this->m_resetTexture->getImGuiTextureId(), IMAGE_BUTTON_SIZE)) {
            this->m_shouldReset = !this->m_shouldReset;
        }


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
            if (ImGui::BeginCombo("Number of Species", this->m_numSpecies)) {
                for (auto &m_speciesItem : this->m_speciesItems) {
                    if (ImGui::Selectable(m_speciesItem)) {
                        this->m_numSpecies = m_speciesItem;
                        this->m_agentSystem->currentNumSpecies = *this->m_numSpecies - '0';
                    }
                }
                ImGui::EndCombo();
            }
            ImGui::Text("Species Settings");
            sscanf(this->m_numSpecies, "%d", &this->m_agentSystem->currentNumSpecies);
            for (int i = 0; i < this->m_agentSystem->currentNumSpecies; i++) {
                if (ImGui::CollapsingHeader(std::to_string(i + 1).c_str())) {
                    std::string speed = "Speed";
                    std::string turnSpeed = "Turn Speed";
                    std::string sensorOffset = "Sensor Offset";
                    std::string sensorAngle = "Sensor Angle";
                    std::string sensorSize = "Sensor Size";
                    std::string speciesColor = "Species Color";
                    ImGui::SliderFloat(speed.append(i, ' ').c_str(), &this->m_agentSystem->speciesSpecs[i].speed, 0.0f,
                                       300.0f);
                    ImGui::SliderFloat(turnSpeed.append(i, ' ').c_str(),
                                       &this->m_agentSystem->speciesSpecs[i].turnSpeed, 0.0f, 300.0f);
                    ImGui::SliderFloat(sensorOffset.append(i, ' ').c_str(),
                                       &this->m_agentSystem->speciesSpecs[i].sensorOffsetDistance,
                                       0.0f, 50.0f);
                    ImGui::SliderFloat(sensorAngle.append(i, ' ').c_str(),
                                       &this->m_agentSystem->speciesSpecs[i].sensorAngleOffset, 0.0f,
                                       2.0f);
                    ImGui::SliderInt(sensorSize.append(i, ' ').c_str(),
                                     &this->m_agentSystem->speciesSpecs[i].sensorSize, 0, 10);
                    ImGui::ColorEdit3(speciesColor.append(i, ' ').c_str(),
                                      i == 0 ? &speciesColor1[0] : i == 1 ? &speciesColor2[0] : &speciesColor3[0]);
                }
            }


//            ImGui::SliderFloat("Speed", &this->m_simulationSpeed, 0.0f, 300.0f);
//            ImGui::SliderFloat("Turn Speed", &this->m_turnSpeed, 0.0f, 300.0f);
//            ImGui::SliderFloat("Sensor Offset", &this->m_sensorOffsetDistance, 0.0f, 50.0f);
//            ImGui::SliderFloat("Sensor Angle", &this->m_sensorAngle, 0.0f, 2.0f);
//            ImGui::SliderInt("Sensor Size", &this->m_sensorSize, 0, 10);
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
    return {this->m_agentColor[0], this->m_agentColor[1], this->m_agentColor[2]};
};


glm::vec3 Settings::getColorMod() const {
    return {this->m_effectColor[0], this->m_effectColor[1], this->m_effectColor[2]};
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

bool Settings::isRunning() const {
    return this->m_playing;
}

void Settings::setPlaying(bool playing) {
    this->m_playing = playing;
}

bool Settings::shouldReset() const {
    return this->m_shouldReset;
}
