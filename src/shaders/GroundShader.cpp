//
// Created by Martin on 17. 11. 2015.
//

#include "src/shaders/GroundShader.hpp"


GroundShader::GroundShader() : ShaderProgram("src/shaders/vert_ground.glsl", "src/shaders/frag_ground.glsl") {
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
    this->backgroundTexture = getUniformLocation("BackgroundTexture");
    this->rTexture = getUniformLocation("RTexture");
    this->gTexture = getUniformLocation("GTexture");
    this->bTexture = getUniformLocation("BTexture");
    this->blendMap = getUniformLocation("BlendMap");
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

void GroundShader::connectTextureUnits() {
    loadInt(this->backgroundTexture, 0);
    loadInt(this->rTexture, 1);
    loadInt(this->gTexture, 2);
    loadInt(this->bTexture, 3);
    loadInt(this->blendMap, 4);
}