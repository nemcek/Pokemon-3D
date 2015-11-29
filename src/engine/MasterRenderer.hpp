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
#include "src/gui/GuiRenderer.hpp"
#include "src/skybox/SkyboxRenderer.hpp"

namespace nsMaterRenderer {

    class MasterRenderer {
    private:
        glm::vec3 skyColor = glm::vec3(0.5444f, 0.62f, 0.69f);
        glm::vec3 fogColor = glm::vec3(0.5444f, 0.62f, 0.69f);

        StaticShader *staticShader;
        GroundShader *groundShader;
        GuiShader *guiShader;
        SkyboxShader *skyboxShader;

        nsMeshRenderer::MeshRenderer *renderer;
        GroundRenderer *groundRenderer;
        GuiRenderer *guiRenderer;
        SkyboxRenderer *skyboxRenderer;

        std::map<TexturedModel, std::list<Mesh>> meshesMap;
        std::vector<Mesh> meshes;
        std::vector<nsGround::Ground> grounds;
        std::vector<MeshWrapper *> wrappers;
        std::vector<Gui *> guis;
        Skybox *skybox;

        void prepare();
    public:

        MasterRenderer(nsMeshRenderer::MeshRenderer *renderer, GroundRenderer *groundRenderer, GuiRenderer *guiRenderer, SkyboxRenderer *skyboxRenderer);
        void clean();
        void render(glm::mat4 projection, glm::mat4 camera, std::vector<Light *> lights);
        void processMesh(Mesh *mesh);
        void processGround(nsGround::Ground *ground);
        void processWrapper(MeshWrapper *wrapper);
        void processGui(Gui *gui);
        void processSkybox(Skybox *skybox);
    };

}

#endif //POKEMON3D_MASTERRENDERER_H
