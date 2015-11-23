//
// Created by Martin on 23. 11. 2015.
//

#include "src/gui/GuiShader.hpp"

GuiShader::GuiShader() : ShaderProgram("src/shaders/vert_gui.glsl", "src/shaders/frag_gui.glsl") {
    getAllUniformLocations();
//    bindAttributes();
}

void GuiShader::getAllUniformLocations() {
    this->matrix = getUniformLocation("ModelMatrix");
    this->texture = getUniformLocation("Texture");
}

void GuiShader::loadModelMatrix(glm::mat4 matrix) {
    loadMatrix(this->matrix, matrix);
}

void GuiShader::bindAttributes() {
    bindAttribute(0, "Position");
}

void GuiShader::loadTextureUni(GLint texture_id) {
    loadTexture(this->texture, texture_id);
}
