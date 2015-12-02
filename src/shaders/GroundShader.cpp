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
    this->reflectivity = getUniformLocation("reflectivity");
    this->shineDamper = getUniformLocation("shineDamper");
    this->skyColor = getUniformLocation("skyColor");
    this->backgroundTexture = getUniformLocation("BackgroundTexture");
    this->rTexture = getUniformLocation("RTexture");
    this->gTexture = getUniformLocation("GTexture");
    this->bTexture = getUniformLocation("BTexture");
    this->blendMap = getUniformLocation("BlendMap");

    this->lightPosition = new int[number_of_lights];
    this->lightColor = new int[number_of_lights];
    this->attenuation = new int[number_of_lights];

    for (int i = 0; i < number_of_lights; i++) {
        this->lightPosition[i] = getUniformLocation("lightPosition[" + std::to_string(i) + "]");
        this->lightColor[i] = getUniformLocation("lightColor[" + std::to_string(i) + "]");
        this->attenuation[i] = getUniformLocation("attenuation[" + std::to_string(i) + "]");
    }
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

void GroundShader::loadLights(std::vector<LightPtr> lights) {
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

void GroundShader::loadShining(float reflectivity, float shineDamper) {
    loadFloat(this->reflectivity, reflectivity);
    loadFloat(this->shineDamper, shineDamper);
}