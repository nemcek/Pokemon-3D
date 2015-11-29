//
// Created by Martin on 28. 11. 2015.
//

#include "src/skybox/SkyboxShader.hpp"

SkyboxShader::SkyboxShader() : ShaderProgram("src/shaders/vert_skybox.glsl", "src/shaders/frag_skybox.glsl") {
    getAllUniformLocations();
}

void SkyboxShader::getAllUniformLocations() {
    this->projectionMatrix = getUniformLocation("ProjectionMatrix");
    this->viewMatrix = getUniformLocation("ViewMatrix");
    this->fogColor = getUniformLocation("fogColor");
}

void SkyboxShader::loadProjectionMatrix(glm::mat4 matrix) {
    loadMatrix(this->projectionMatrix, matrix);
}

void SkyboxShader::loadViewMatrix(glm::mat4 matrix, float rotation) {
    matrix[3].x = 0;
    matrix[3].y = 0;
    matrix[3].z = 0;
    matrix = rotate(matrix, rotation);

    loadMatrix(this->viewMatrix, matrix);
}

void SkyboxShader::loadFogColor(glm::vec3 color) {
    loadVector(this->fogColor, color);
}

glm::mat4 SkyboxShader::rotate(glm::mat4 matrix, float rotation) {
    return glm::rotate(matrix, glm::radians(rotation), this->rotationVec);
}