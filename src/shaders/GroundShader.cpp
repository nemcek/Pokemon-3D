//
// Created by Martin on 17. 11. 2015.
//

#include "src/shaders/GroundShader.hpp"


GroundShader::GroundShader() : ShaderProgram("src/shaders/ground.vert", "src/shaders/ground.frag") {
    getAllUniformLocations();
}

void GroundShader::bindAttributes() {
    this->bindAttribute(0, "FragmentColor");
}

void GroundShader::getAllUniformLocations() {
    this->modelMatrix = getUniformLocation("ModelMatrix");
    this->texture = getUniformLocation("Texture");
    this->projection = getUniformLocation("ProjectionMatrix");
    this->view = getUniformLocation("ViewMatrix");
    this->lightPosition = getUniformLocation("lightPosition");
    this->lightColor = getUniformLocation("lightColor");
    this->skyColor = getUniformLocation("skyColor");
}

void GroundShader::loadModelMatrix(glm::mat4 matrix) {
    loadMatrix(this->modelMatrix, matrix);
}

void GroundShader::loadTextureUni(GLint texture_id) {
    loadTexture(this->texture, texture_id);
}

void GroundShader::loadProjectionMatrix(glm::mat4 projection) {
    loadMatrix(this->projection, projection);
}

void GroundShader::loadViewMatrix(glm::mat4 view) {
    loadMatrix(this->view, view);
}

void GroundShader::loadLight(Light *light) {
    loadVector(this->lightPosition, light->position);
    loadVector(this->lightColor, light->color);
}

void GroundShader::loadSkyColor(glm::vec3 skyColor) {
    loadVector(this->skyColor, skyColor);
}