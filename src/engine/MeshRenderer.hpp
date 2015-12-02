//
// Created by Martin on 16. 11. 2015.
//

#ifndef POKEMON3D_RENDERER_H
#define POKEMON3D_RENDERER_H

#include <list>

#include "src/objects/Mesh.h"
#include "src/shaders/StaticShader.hpp"
#include "src/wrappers/MeshWrapper.hpp"

class MeshRenderer {

private:
    void loadTexturedModel(TexturedModelPtr model, glm::mat4 projection, glm::mat4 view);
    void loadMatrixAndDraw(glm::mat4, int count);
    void unbindMesh();
    void render(MeshWrapperPtr wrapper, glm::mat4 projection, glm::mat4 view);
    void loadVAO(TexturedModelPtr model);

public:
    StaticShaderPtr shader;
//        StaticShader *shader;

    MeshRenderer(StaticShaderPtr shader);
    void render(std::vector<MeshPtr> meshes, glm::mat4 projection, glm::mat4 view);
    void render(MeshPtr mesh, glm::mat4 projection, glm::mat4 view);
    void render(std::vector<MeshWrapperPtr> wrappers, glm::mat4 projection, glm::mat4 matrix);

};

typedef std::shared_ptr<MeshRenderer> MeshRendererPtr;

#endif //POKEMON3D_RENDERER_H
