//
// Created by Martin on 17. 11. 2015.
//

#ifndef POKEMON3D_TEXTUREDMODEL_H
#define POKEMON3D_TEXTUREDMODEL_H

#include <memory>

#include "src/textures/Texture.hpp"
#include "src/models/RawModel.hpp"
#include <glm/glm.hpp>

class TexturedModel {

private:


public:
    glm::mat4 matrix;
    RawModelPtr rawModel;
//    RawModel *rawModel;
    TexturePtr texture;
//    nsTexture::Texture *texture;

    TexturedModel();

};

typedef std::shared_ptr<TexturedModel> TexturedModelPtr;

#endif //POKEMON3D_TEXTUREDMODEL_H
