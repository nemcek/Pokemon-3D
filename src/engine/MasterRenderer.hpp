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

class MasterRenderer {
private:
    glm::vec3 skyColor = glm::vec3(0.5444f, 0.62f, 0.69f);
    glm::vec3 fogColor = glm::vec3(0.5444f, 0.62f, 0.69f);

    StaticShaderPtr staticShader;
    GroundShaderPtr groundShader;
    GuiShaderPtr guiShader;
    SkyboxShaderPtr skyboxShader;

    MeshRendererPtr renderer;
    GroundRendererPtr groundRenderer;
    GuiRendererPtr guiRenderer;
    SkyboxRendererPtr skyboxRenderer;

    std::vector<MeshPtr> meshes;
    std::vector<GroundPtr> grounds;
    std::vector<MeshWrapperPtr> wrappers;
    std::vector<GuiPtr> guis;
    SkyboxPtr skybox;

    void prepare();
public:

    MasterRenderer(MeshRendererPtr renderer, GroundRendererPtr groundRenderer, GuiRendererPtr guiRenderer, SkyboxRendererPtr skyboxRenderer);
    void clean();
    void render(glm::mat4 projection, glm::mat4 camera, std::vector<LightPtr> lights);
    void processMesh(MeshPtr mesh);
    void processGround(GroundPtr ground);
    void processWrapper(MeshWrapperPtr wrapper);
    void processGui(GuiPtr gui);
    void processSkybox(SkyboxPtr skybox);
};

typedef std::shared_ptr<MasterRenderer> MasterRendererPtr;

#endif //POKEMON3D_MASTERRENDERER_H
