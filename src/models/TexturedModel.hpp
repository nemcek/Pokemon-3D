//
// Created by Martin on 17. 11. 2015.
//

#ifndef POKEMON3D_TEXTUREDMODEL_H
#define POKEMON3D_TEXTUREDMODEL_H

#include "src/textures/Texture.hpp"
#include "src/models/RawModel.hpp"
#include <glm/glm.hpp>

class TexturedModel {

private:


public:
    glm::mat4 matrix;
    RawModel *rawModel;
    nsTexture::Texture *texture;

    TexturedModel();

};


#endif //POKEMON3D_TEXTUREDMODEL_H
