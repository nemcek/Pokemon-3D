//
// Created by Martin on 29. 11. 2015.
//

#ifndef POKEMON3D_SKYBOX_HPP
#define POKEMON3D_SKYBOX_HPP

#include <vector>
#include <string>

#include "src/loaders/Loader.hpp"
#include "src/models/RawModel.hpp"

class Skybox {

private:
    const float size = 500.0f;

    std::vector<float> vertices = {
            -size,  size, -size,
            -size, -size, -size,
            size, -size, -size,
            size, -size, -size,
            size,  size, -size,
            -size,  size, -size,

            -size, -size,  size,
            -size, -size, -size,
            -size,  size, -size,
            -size,  size, -size,
            -size,  size,  size,
            -size, -size,  size,

            size, -size, -size,
            size, -size,  size,
            size,  size,  size,
            size,  size,  size,
            size,  size, -size,
            size, -size, -size,

            -size, -size,  size,
            -size,  size,  size,
            size,  size,  size,
            size,  size,  size,
            size, -size,  size,
            -size, -size,  size,

            -size,  size, -size,
            size,  size, -size,
            size,  size,  size,
            size,  size,  size,
            -size,  size,  size,
            -size,  size, -size,

            -size, -size, -size,
            -size, -size,  size,
            size, -size, -size,
            size, -size, -size,
            -size, -size,  size,
            size, -size,  size
    };

    std::vector<std::string> file_paths = {
            "models/textures/left.tga",
            "models/textures/right.tga",
            "models/textures/top.tga",
            "models/textures/bottom.tga",
            "models/textures/back.tga",
            "models/textures/front.tga"
    };

    const float rotationSpeed = 0.3f;


public:
    GLint textureId;
    RawModel *cube;
    float rotation = 0.0f;

    Skybox(Loader *loader);
    void animate(float delta);
};

#endif //POKEMON3D_SKYBOX_HPP
