#include <cstring>
#include "Settings.h"


Settings::Settings(Window *window, AgentSystem *system) : m_numSpecies("1"), m_agentSystem(system),
                                                          m_spawnPosition(strdup(spawnPositionNames[0].c_str())),
                                                          m_window(window) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void) io;

    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window->getWindow(), true);
    ImGui_ImplOpenGL3_Init(GLSL_VERSION);
    std::fill(m_agentColor, m_agentColor + PICKER_SIZE, 1);
    std::fill(m_effectColor, m_effectColor + PICKER_SIZE, 0);

    m_playTexture = new Texture(".\\images\\play32xwhite.png",
                                GL_READ_ONLY);
    m_pauseTexture = new Texture(".\\images\\pause32xwhite.png",
                                 GL_READ_ONLY);
    m_resetTexture = new Texture(
            ".\\images\\reset32xwhite.png",
            GL_READ_ONLY);

    m_currentTexture = m_playTexture;

    for (int i = 0; i < MAX_SPECIES; i++) {
        m_speciesItems[i] = strdup(std::to_string(i + 1).c_str());
    }

}


void Settings::init() {

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // Add content to window
    if (m_window->showWindow) {
        if (m_randomizePresets && m_window->getTimePassed() >= m_randomInterval) {
            m_shouldReset = true;
            m_window->resetTimePassed();
            // TODO: Choose a random preset and set that as the active preset.
        }

        ImGui::Begin("Settings", &m_window->showWindow);


        m_currentTexture = m_playing ? m_pauseTexture : m_playTexture;

        // Hide play / reset button if randomize is on.
        if (!m_randomizePresets) {

            if (ImGui::ImageButton(m_currentTexture->getImGuiTextureId(), IMAGE_BUTTON_SIZE)) {
                m_playing = !m_playing;
            }

            ImGui::SameLine();

            if (ImGui::ImageButton(m_resetTexture->getImGuiTextureId(), IMAGE_BUTTON_SIZE)) {
                m_shouldReset = !m_shouldReset;
            }

            ImGui::SameLine();
        }


        ImGui::PushItemWidth(150.0f);
        if (ImGui::BeginCombo("Spawn Position", m_spawnPosition.c_str())) {
            for (int i = 0; i < spawnPositionNames->size(); i++) {
                std::string name = spawnPositionNames[i];
                if (ImGui::Selectable(name.c_str())) {
                    m_spawnPosition = strdup(name.c_str());
                    m_agentSystem->setSpawnPos(spawnPositions[i]);
                }
            }
            ImGui::EndCombo();
        }

        if (ImGui::Checkbox("Randomize Presets", &m_randomizePresets)) {
            m_playing = true;
            m_window->startTimer();
        }
        ImGui::SameLine();
        ImGui::DragInt("Reset Interval", &m_randomInterval, 1, 1, 300);


        if (ImGui::BeginCombo("Presets", m_preset.c_str())) {
            if (ImGui::Selectable("")) {
                m_preset = "";
                m_presetBuffer[0] = '\0';
            }
            for (auto &path: std::filesystem::directory_iterator(".\\settings")) {
                std::filesystem::path fileName = path.path().filename();
                if (ImGui::Selectable(fileName.string().c_str())) {
                    m_preset = fileName.string();
                    m_presetBuffer[0] = '\0';
                }
            }

            ImGui::EndCombo();
        }

        ImGui::InputText("Preset Name", m_presetBuffer, IM_ARRAYSIZE(m_presetBuffer));

        if (ImGui::Button("Export Settings")) {
            exportSettings();
        }
        ImGui::PopItemWidth();


        if (ImGui::CollapsingHeader("Effect Settings")) {
            ImGui::Checkbox("Blur", &m_blur);
            ImGui::SliderFloat("Diffuse Speed", &m_diffuseSpeed, 0.0f, 25.0f);
            ImGui::SliderFloat("Evaporate Speed", &m_evaporateSpeed, 0.0f, 2.0f);
            if (m_blur && m_diffuseSpeed > 0 && m_evaporateSpeed > 0) {
                ImGui::ColorEdit3("Color Mod", m_effectColor,
                                  ImGuiColorEditFlags_NoPicker | ImGuiColorEditFlags_Float);
            }
        }


        if (ImGui::CollapsingHeader("Agent Settings")) {
            if (ImGui::BeginCombo("Number of Species", m_numSpecies)) {
                std::cout << m_numSpecies << std::endl;
                for (auto &m_speciesItem: m_speciesItems) {
                    if (ImGui::Selectable(m_speciesItem)) {
                        m_numSpecies = m_speciesItem;
                        m_agentSystem->currentNumSpecies = *m_numSpecies - '0';
                    }
                }
                ImGui::EndCombo();
            }
            ImGui::Text("Species Settings");
            sscanf(m_numSpecies, "%d", &m_agentSystem->currentNumSpecies);
            for (int i = 0; i < m_agentSystem->currentNumSpecies; i++) {
                if (ImGui::CollapsingHeader(std::to_string(i + 1).c_str())) {
                    std::string speed = "Speed";
                    std::string turnSpeed = "Turn Speed";
                    std::string sensorOffset = "Sensor Offset";
                    std::string sensorAngle = "Sensor Angle";
                    std::string sensorSize = "Sensor Size";
                    std::string speciesColor = "Species Color";
                    ImGui::SliderFloat(speed.append(i, ' ').c_str(), &m_agentSystem->speciesSpecs[i].speed, 0.0f,
                                       300.0f);
                    ImGui::SliderFloat(turnSpeed.append(i, ' ').c_str(),
                                       &m_agentSystem->speciesSpecs[i].turnSpeed, 0.0f, 300.0f);
                    ImGui::SliderFloat(sensorOffset.append(i, ' ').c_str(),
                                       &m_agentSystem->speciesSpecs[i].sensorOffsetDistance,
                                       0.0f, 50.0f);
                    ImGui::SliderFloat(sensorAngle.append(i, ' ').c_str(),
                                       &m_agentSystem->speciesSpecs[i].sensorAngleOffset, 0.0f,
                                       2.0f);
                    ImGui::SliderInt(sensorSize.append(i, ' ').c_str(),
                                     &m_agentSystem->speciesSpecs[i].sensorSize, 0, 10);
                    ImGui::ColorEdit3(speciesColor.append(i, ' ').c_str(),
                                      glm::value_ptr(m_agentSystem->speciesSpecs[i].color));
                }
            }

        }
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

void Settings::parseYAML() {
    if (!m_preset.empty()) {
        YAML::Node settings = YAML::LoadFile(std::string("settings\\").append(m_preset));
        YAML::Node effectSettings = settings["Effect Settings"];
        YAML::Node agentSettings = settings["Agent Settings"];

        // Load the spawn pos
        m_spawnPosition = settings["Spawn Position"].as<std::string>();
        m_agentSystem->setSpawnPos(spawnPositions[spawnPositionNames->find(m_spawnPosition)]);

        // Load effect Settings
        m_blur = effectSettings["Blur"].as<bool>();
        m_diffuseSpeed = effectSettings["Diffuse Speed"].as<float>();
        m_evaporateSpeed = effectSettings["Evaporate Speed"].as<float>();
        YAML::Node colorMod = effectSettings["Color Mod"];
        for (YAML::detail::iterator_value num: colorMod) {
            for (int i = 0; i < PICKER_SIZE; i++) {
                m_effectColor[i] = num[i].as<float>();
            }
        }
        int numSpecies = agentSettings["Number of Species"].as<int>();
        m_numSpecies = m_speciesItems[numSpecies - 1];
        m_agentSystem->currentNumSpecies = numSpecies;

        for (int i = 0; i < numSpecies; i++) {
            YAML::Node speciesSettings = agentSettings[std::string("Species ").append(m_speciesItems[i])];
            SpeciesSpec spec;
            spec.speed = speciesSettings["Speed"].as<float>();
            spec.turnSpeed = speciesSettings["Turn Speed"].as<float>();
            spec.sensorOffsetDistance = speciesSettings["Sensor Offset"].as<float>();
            spec.sensorAngleOffset = speciesSettings["Sensor Angle"].as<float>();
            spec.sensorSize = speciesSettings["Sensor Size"].as<int>();
            YAML::Node specColor = speciesSettings["Color"];
            for (YAML::detail::iterator_value num: specColor) {
                for (int j = 0; j < PICKER_SIZE; j++) {
                    spec.color[j] = num[j].as<float>();
                }
            }
            m_agentSystem->speciesSpecs.at(i) = spec;
        }
    }


}

void Settings::exportSettings() {
    std::vector<int> effectColor(m_effectColor, m_effectColor + PICKER_SIZE);

    YAML::Emitter emitter;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "Spawn Position" << YAML::Value << m_spawnPosition;
    emitter << YAML::Key << "Effect Settings" << YAML::BeginMap;
    emitter << YAML::Key << "Blur" << YAML::Value << m_blur;
    emitter << YAML::Key << "Diffuse Speed" << YAML::Value << m_diffuseSpeed;
    emitter << YAML::Key << "Evaporate Speed" << YAML::Value << m_evaporateSpeed;
    emitter << YAML::Key << "Color Mod" << YAML::Value << YAML::BeginSeq << YAML::Flow << effectColor << YAML::EndSeq;
    emitter << YAML::EndMap;
    emitter << YAML::Key << "Agent Settings" << YAML::BeginMap;
    emitter << YAML::Key << "Number of Species" << YAML::Value << m_agentSystem->currentNumSpecies;
    for (int i = 0; i < m_agentSystem->currentNumSpecies; i++) {
        emitter << YAML::Key << "Species " + std::to_string(i + 1);
        emitter << YAML::Value << m_agentSystem->speciesSpecs.at(i);
    }

    emitter << YAML::EndMap;


    emitter << YAML::EndMap;
    create_directory(std::filesystem::current_path().append("settings"));
    if (!std::string(m_presetBuffer).empty()) {
        std::basic_ofstream<char> fout(std::filesystem::current_path().append(
                std::string("settings\\").append(m_presetBuffer).append(".yaml")).string());
        fout << emitter.c_str();
    }


}


glm::vec3 Settings::getColor() const {
    return {m_agentColor[0], m_agentColor[1], m_agentColor[2]};
};


glm::vec3 Settings::getColorMod() const {
    return {m_effectColor[0], m_effectColor[1], m_effectColor[2]};
}


float Settings::getSpeed() const {
    return m_simulationSpeed;
}

float Settings::getSensorAngle() const {
    return m_sensorAngle;
}

float Settings::getSensorOffsetDistance() const {
    return m_sensorOffsetDistance;
}

float Settings::getTurnSpeed() const {
    return m_turnSpeed;
}

float Settings::getDiffuseSpeed() const {
    return m_diffuseSpeed;
}

float Settings::getEvaporateSpeed() const {
    return m_evaporateSpeed;
}

int Settings::getSensorSize() const {
    return m_sensorSize;
}

bool Settings::shouldBlur() const {
    return m_blur;
}

bool Settings::isRunning() const {
    return m_playing;
}

void Settings::setPlaying(bool playing) {
    m_playing = playing;
}

bool Settings::shouldReset() const {
    return m_shouldReset;
}

bool Settings::shouldRandomizePresets() const {
    return m_randomizePresets;
}
