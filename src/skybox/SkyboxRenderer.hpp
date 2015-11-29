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
#include "src/skybox/Skybox.hpp"

class SkyboxRenderer {

private:

public:
    SkyboxShader *shader;

    SkyboxRenderer(SkyboxShader *shader);
    void render(Skybox *skybox, glm::mat4 viewMatrix, glm::mat4 projectionMatrix, glm::vec3 fogColor);
};

#endif //POKEMON3D_SKYBOXRENDERER_HPP
