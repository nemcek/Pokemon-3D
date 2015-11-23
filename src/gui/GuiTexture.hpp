//
// Created by Martin on 23. 11. 2015.
//

#ifndef POKEMON3D_GUITEXTURE_HPP
#define POKEMON3D_GUITEXTURE_HPP

#include <glm/glm.hpp>

class GuiTexture {

public:
    int textureId;
    glm::vec2 position;
    glm::vec2 scale;

    GuiTexture(int textureId, glm::vec2 position, glm::vec2 scale);

};

#endif //POKEMON3D_GUITEXTURE_HPP
