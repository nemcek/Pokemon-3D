//
// Created by Martin on 16. 11. 2015.
//

#include "StaticShader.hpp"

StaticShader::StaticShader() : ShaderProgram("src/shaders/vert_pokemon.glsl", "src/shaders/frag_pokemon.glsl") {
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
    this->reflectivity = getUniformLocation("reflectivity");
    this->shineDamper = getUniformLocation("shineDamper");
    this->skyColor = getUniformLocation("skyColor");

    this->lightPosition = new int[number_of_lights];
    this->lightColor = new int[number_of_lights];
    this->attenuation = new int[number_of_lights];

    for (int i = 0; i < number_of_lights; i++) {
        this->lightPosition[i] = getUniformLocation("lightPosition[" + std::to_string(i) + "]");
        this->lightColor[i] = getUniformLocation("lightColor[" + std::to_string(i) + "]");
        this->attenuation[i] = getUniformLocation("attenuation[" + std::to_string(i) + "]");
    }
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

void StaticShader::loadLights(std::vector<Light *> lights) {
    for (int i = 0; i < number_of_lights; i++) {
        if (i < lights.size()) {
            loadVector(this->lightPosition[i], lights[i]->position);
            loadVector(this->lightColor[i], lights[i]->color);
            loadVector(this->attenuation[i], lights[i]->attenuation);
        } else {
            loadVector(this->lightPosition[i], glm::vec3(0.0f));
            loadVector(this->lightColor[i], glm::vec3(0.0f));
            loadVector(this->attenuation[i], glm::vec3(1.0f, 0.0f, 0.0f));
        }
    }
}

void StaticShader::loadShining(float reflectivity, float shineDamper) {
    loadFloat(this->reflectivity, reflectivity);
    loadFloat(this->shineDamper, shineDamper);
}

void StaticShader::loadSkyColor(glm::vec3 skyColor) {
    loadVector(this->skyColor, skyColor);
}