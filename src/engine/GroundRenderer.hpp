//
// Created by Martin on 17. 11. 2015.
//

#ifndef POKEMON3D_GROUNDRENDERER_H
#define POKEMON3D_GROUNDRENDERER_H

#include <src/objects/Ground.hpp>
#include "src/shaders/GroundShader.hpp"
#include "src/objects/Mesh.h"

class GroundRenderer {

private:
    void prepareGround(const nsGround::Ground *model, glm::mat4 projection, glm::mat4 view);
    void unbindMesh();
    void prepareInstance(nsGround::Ground *ground);
    void render(Mesh *mesh, glm::mat4 projection, glm::mat4 view);
    void loadModelMatrix(nsGround::Ground *ground);
    void bindTextures(nsGround::Ground *ground);

public:
    GroundShader *shader;

    GroundRenderer(GroundShader *shader);
    void render(std::vector<nsGround::Ground> grounds, glm::mat4 projection, glm::mat4 view);

};

#endif //POKEMON3D_GROUNDRENDERER_H