//
// Created by Martin on 28. 11. 2015.
//

#include "src/skybox/SkyboxShader.hpp"

SkyboxShader::SkyboxShader(float *delta) : ShaderProgram("src/shaders/vert_skybox.glsl", "src/shaders/frag_skybox.glsl") {
    getAllUniformLocations();
    this->delta = delta;
}

void SkyboxShader::getAllUniformLocations() {
    this->projectionMatrix = getUniformLocation("ProjectionMatrix");
    this->viewMatrix = getUniformLocation("ViewMatrix");
    this->cube = getUniformLocation("CubeMap");
    this->fogColor = getUniformLocation("fogColor");
}

void SkyboxShader::loadProjectionMatrix(glm::mat4 matrix) {
    loadMatrix(this->projectionMatrix, matrix);
}

void SkyboxShader::loadViewMatrix(glm::mat4 matrix) {
    matrix[3].x = 0;
    matrix[3].y = 0;
    matrix[3].z = 0;
    this->rotation += rotationSpeed * *delta;

    matrix = glm::rotate(matrix, glm::radians(this->rotation), glm::vec3(0.0f, 1.0f, 0.0f));
    loadMatrix(this->viewMatrix, matrix);
}

void SkyboxShader::loadFogColor(glm::vec3 color) {
    loadVector(this->fogColor, color);
}