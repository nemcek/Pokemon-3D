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
    void prepareGround(GroundPtr model, glm::mat4 projection, glm::mat4 view);
    void unbindMesh();
    void prepareInstance(GroundPtr ground);
    void render(MeshPtr mesh, glm::mat4 projection, glm::mat4 view);
    void loadModelMatrix(GroundPtr ground);
    void bindTextures(GroundPtr ground);

public:
    GroundShaderPtr shader;
//    GroundShader *shader;

    GroundRenderer(GroundShaderPtr shader);
    void render(std::vector<GroundPtr> grounds, glm::mat4 projection, glm::mat4 view);

};

typedef std::shared_ptr<GroundRenderer> GroundRendererPtr;

#endif //POKEMON3D_GROUNDRENDERER_H