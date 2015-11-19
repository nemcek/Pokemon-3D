//
// Created by Martin on 16. 11. 2015.
//

#include "StaticShader.hpp"

StaticShader::StaticShader() : ShaderProgram("src/shaders/gl_pokemon.vert", "src/shaders/gl_pokemon.frag") {
    getAllUniformLocations();
}

void StaticShader::bindAttributes() {
    this->bindAttribute(0, "FragmentColor");
    this->bindAttribute(2, "Normal");
}

void StaticShader::getAllUniformLocations() {
    this->modelMatrix = getUniformLocation("ModelMatrix");
    this->texture = getUniformLocation("Texture");
    this->projection = getUniformLocation("ProjectionMatrix");
    this->view = getUniformLocation("ViewMatrix");
    this->lightPosition = getUniformLocation("lightPosition");
    this->lightColor = getUniformLocation("lightColor");
    this->reflectivity = getUniformLocation("reflectivity");
    this->shineDamper = getUniformLocation("shineDamper");
    this->skyColor = getUniformLocation("skyColor");
}

void StaticShader::loadModelMatrix(glm::mat4 matrix) {
    loadMatrix(this->modelMatrix, matrix);
}

void StaticShader::loadTextureUni(GLint texture_id) {
    loadTexture(this->texture, texture_id);
}

void StaticShader::loadProjectionMatrix(glm::mat4 projection) {
    loadMatrix(this->projection, projection);
}

void StaticShader::loadViewMatrix(glm::mat4 view) {
    loadMatrix(this->view, view);
}

void StaticShader::loadLight(Light *light) {
    loadVector(this->lightPosition, light->position);
    loadVector(this->lightColor, light->color);
}

void StaticShader::loadShining(float reflectivity, float shineDamper) {
    loadFloat(this->reflectivity, reflectivity);
    loadFloat(this->shineDamper, shineDamper);
}

void StaticShader::loadSkyColor(glm::vec3 skyColor) {
    loadVector(this->skyColor, skyColor);
}