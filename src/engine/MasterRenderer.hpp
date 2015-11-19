//
// Created by Martin on 17. 11. 2015.
//

#ifndef POKEMON3D_MASTERRENDERER_H
#define POKEMON3D_MASTERRENDERER_H

#include <map>
#include <list>

#include "src/shaders/StaticShader.hpp"
#include "MeshRenderer.hpp"
#include "src/objects/Mesh.h"
#include "src/engine/GroundRenderer.hpp"
#include "src/objects/Light.hpp"
#include "src/wrappers/MeshWrapper.hpp"

namespace nsMaterRenderer {

    class MasterRenderer {
    private:
        glm::vec3 skyColor = glm::vec3(0.5f, 0.5f, 0.5f);

        StaticShader *staticShader;
        GroundShader *groundShader;
        nsMeshRenderer::MeshRenderer *renderer;
        GroundRenderer *groundRenderer;
        std::map<TexturedModel, std::list<Mesh>> meshesMap;
        std::vector<Mesh> meshes;
        std::vector<nsGround::Ground> grounds;
        std::vector<MeshWrapper> wrappers;

        void prepare();
    public:

        MasterRenderer(nsMeshRenderer::MeshRenderer *renderer, GroundRenderer *groundRenderer);
        void clean();
        void render(glm::mat4 projection, glm::mat4 camera, Light *light);
        void processMesh(Mesh *mesh);
        void processGround(nsGround::Ground *ground);
        void processWrapper(MeshWrapper *wrapper);
    };

}

#endif //POKEMON3D_MASTERRENDERER_H
