//
// Created by Martin on 28. 11. 2015.
//

#ifndef POKEMON3D_SKYBOXRENDERER_HPP
#define POKEMON3D_SKYBOXRENDERER_HPP

#include <vector>
#include <string>

#include "src/models/RawModel.hpp"
#include "src/skybox/SkyboxShader.hpp"
#include "src/loaders/Loader.hpp"

class SkyboxRenderer {

private:
    const float size = 500.0f;

    std::vector<float > vertices = {
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
//            "models/textures/top.tga",
//            "models/textures/top.tga",
//            "models/textures/top.tga",
//            "models/textures/top.tga",
//            "models/textures/top.tga",
//            "models/textures/top.tga"
//            "models/textures/Pikachu.tga",
//            "models/textures/Pikachu.tga",
//            "models/textures/Pikachu.tga",
//            "models/textures/Pikachu.tga",
//            "models/textures/Pikachu.tga",
//            "models/textures/Pikachu.tga"
    };

    RawModel *cube;
    int textureId;

public:
    SkyboxShader *shader;

    SkyboxRenderer(Loader *loader, SkyboxShader *shader);
    void render(glm::mat4 viewMatrix,glm::mat4 projectionMatrix, glm::vec3 fogColor);
};

#endif //POKEMON3D_SKYBOXRENDERER_HPP
