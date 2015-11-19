//
// Created by Martin on 16. 11. 2015.
//

#ifndef POKEMON3D_RENDERER_H
#define POKEMON3D_RENDERER_H

#include <list>

#include "src/objects/Mesh.h"
#include "src/shaders/StaticShader.hpp"
#include "src/wrappers/MeshWrapper.hpp"

namespace nsMeshRenderer {

    class MeshRenderer {

    private:
        void loadTexturedModel(const TexturedModel *model, glm::mat4 projection, glm::mat4 view);
        void loadMatrixAndDraw(glm::mat4, int count);
        void unbindMesh();
        void render(MeshWrapper *wrapper, glm::mat4 projection, glm::mat4 view);
        void loadVAO(TexturedModel *model);

    public:
        StaticShader *shader;

        MeshRenderer(StaticShader *shader);
        void render(std::vector<Mesh> meshes, glm::mat4 projection, glm::mat4 view);
        void render(Mesh *mesh, glm::mat4 projection, glm::mat4 view);
        void render(std::vector<MeshWrapper> wrappers, glm::mat4 projection, glm::mat4 matrix);

    };
}
#endif //POKEMON3D_RENDERER_H
