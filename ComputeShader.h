#ifndef SLIMEMOLDSIMULATION_COMPUTESHADER_H
#define SLIMEMOLDSIMULATION_COMPUTESHADER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>


class ComputeShader {
    const std::string enumValues[2] = {"COMPUTE", "PROGRAM"};
    enum ComputeErrorType {
        COMPUTE, PROGRAM
    };

public:
    unsigned int ID;
    GLuint m_ssbo = 0;

    explicit ComputeShader(const char *computeShaderPath) {
        std::string computeShader;
        std::ifstream computeShaderFile;

        computeShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

        try {
            computeShaderFile.open(computeShaderPath);
            std::stringstream computeStream;
            computeStream << computeShaderFile.rdbuf();
            computeShaderFile.close();
            computeShader = computeStream.str();
        } catch (std::ifstream::failure &e) {
            std::cout << "ERROR: Could not read compute shader file: " << &e << std::endl;
        }
        const char *cShader = computeShader.c_str();
        uint compute;

        compute = glCreateShader(GL_COMPUTE_SHADER);
        glShaderSource(compute, 1, &cShader, NULL);
        glCompileShader(compute);
        checkCompileErrors(compute, ComputeErrorType::COMPUTE);

        ID = glCreateProgram();
        glAttachShader(ID, compute);
        glLinkProgram(ID);
        checkCompileErrors(ID, ComputeErrorType::PROGRAM);

        glDeleteShader(compute);
    }

    void use() {
        glUseProgram(ID);
    }

    void useSSBO(size_t size, void *data) {
        glGenBuffers(1, &m_ssbo);
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_ssbo);
        glBufferData(GL_SHADER_STORAGE_BUFFER, size, data, GL_DYNAMIC_COPY);
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, m_ssbo);
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
        std::cout << "Binding SSBO of size: " << std::to_string(size) << std::endl;
    }


    static void dispatch(unsigned int xGroup, unsigned int yGroup, unsigned int zGroup) {
        glDispatchCompute(xGroup, yGroup, zGroup);
    }

    [[maybe_unused]]
    void setBool(const std::string &name, bool value) const {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), (int) value);
    }

    void setFloat(const std::string &name, float value) const {
        glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
    }

    [[maybe_unused]]
    void setInt(const std::string &name, int value) const {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
    }

    [[maybe_unused]]
    void setUnsignedInt(const std::string &name, uint value) const {
        glUniform1ui(glGetUniformLocation(ID, name.c_str()), value);
    }

    [[maybe_unused]]
    void setVec4(const std::string &name, const glm::vec4 &value) const {
        glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
    }

    [[maybe_unused]]
    void setVec3(const std::string &name, const glm::vec3 &value) const {
        glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
    }

    [[maybe_unused]]
    void setVec3(const std::string &name, float x, float y, float z) const {
        glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
    }

private:

    void checkCompileErrors(GLuint shader, ComputeErrorType type) {
        GLint success;
        uint32_t logSize = 1024;
        GLchar infoLog[logSize];
        if (type != ComputeErrorType::PROGRAM) {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success) {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << enumValues[type] << "\n"
                          << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        } else {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success) {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << enumValues[type] << "\n"
                          << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
    }
};


#endif