//
// Created by Martin on 22. 11. 2015.
//

#ifndef POKEMON3D_SCENE_HPP
#define POKEMON3D_SCENE_HPP

#include "src/objects/Mesh.h"
#include "src/objects/Ground.hpp"
#include "src/engine/MasterRenderer.hpp"
#include "src/camera/ThirdPersonCamera.h"
#include "src/wrappers/MeshWrapper.hpp"
#include "src/gui/Gui.hpp"
#include "src/skybox/Skybox.hpp"

class Scene {

private:
    std::vector<nsGround::Ground *> grounds;
    nsMaterRenderer::MasterRenderer *masterRenderer;
    std::vector<Light *> lights;
    glm::mat4 projection;
    nsThirdPersonCamera::ThirdPersonCamera *camera;
    Skybox *skybox;

public:
    std::vector<Mesh *> objects;
    std::vector<MeshWrapper *> wrappers;
    std::vector<Gui *> guis;

    Scene(nsMaterRenderer::MasterRenderer *masterRenderer, std::vector<Light *> lights, glm::mat4 projection,
          nsThirdPersonCamera::ThirdPersonCamera *camera);
    void addObjectToScene(Mesh *mesh);
    void addGroundToScene(nsGround::Ground *ground);
    void animate(float delta);
    void render();
    void processWrapper(MeshWrapper *wrapper);
    void processGui(Gui *gui);
    void processSkybox(Skybox *skybox);
};

#endif //POKEMON3D_SCENE_HPP
