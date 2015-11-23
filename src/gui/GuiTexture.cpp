//
// Created by Martin on 23. 11. 2015.
//

#include "src/gui/GuiTexture.hpp"

GuiTexture::GuiTexture(int textureId, glm::vec2 position, glm::vec2 scale) {
    this->textureId = textureId;
    this->position = position;
    this->scale = scale;
}