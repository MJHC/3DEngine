//
// Created by Magnus on 30-11-2023.
//


#include <iostream>
#include "Shader.h"
#include "utils.h"
#include "glad/glad.h"
#include <glm/gtc/type_ptr.hpp>



Shader::Shader(const char *vsPath, const char *fsPath) {
    std::string vs = loadFile(vsPath);
    std::string fs = loadFile(fsPath);
    _compile(vs, fs);
}

void Shader::_compile(const std::string &vs, const std::string &fs) {
    int success;
    char infoLog[512];

    unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
    const char* vShader = vs.c_str();

    glShaderSource(vertex, 1, &vShader, NULL);
    glCompileShader(vertex);
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success){
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILE_FAILED\n" << infoLog << std::endl;
    }

    unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);
    const char* fShader = fs.c_str();
    glShaderSource(fragment, 1, &fShader, NULL);
    glCompileShader(fragment);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success){
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILE_FAILED\n" << infoLog << std::endl;
    }

    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success){
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::use() {
    glUseProgram(ID);
}

void Shader::setBool(const std::string &name, bool val) {
    setInt(name, (int)val);
}

void Shader::setInt(const std::string &name, int val) {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), val);
}

void Shader::setFloat(const std::string &name, float val) {
    glUniform1f(glGetUniformLocation(ID, name.c_str()), val);
}

void Shader::setVec2f(const std::string &name, const glm::vec2 &vec) {
    glUniform2f(glGetUniformLocation(ID, name.c_str()), vec.x, vec.y);
}
void Shader::setVec3f(const std::string &name, const glm::vec3 &vec) {
    glUniform3f(glGetUniformLocation(ID, name.c_str()), vec.x, vec.y, vec.z);
}

void Shader::setVec4f(const std::string &name, const glm::vec4 &vec) {
    glUniform4f(glGetUniformLocation(ID, name.c_str()), vec.x, vec.y, vec.z, vec.w);
}

void Shader::setMat4(const std::string &name, const glm::mat4 &mat) {
    glUniformMatrix4fv(glGetUniformLocation(ID,name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
}

Shader::~Shader(){
    glDeleteShader(ID);
}