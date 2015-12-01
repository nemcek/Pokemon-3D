//
// Created by Martin on 22. 11. 2015.
//

#ifndef POKEMON3D_SCENE_HPP
#define POKEMON3D_SCENE_HPP

#include <list>

#include "src/objects/Mesh.h"
#include "src/objects/Ground.hpp"
#include "src/engine/MasterRenderer.hpp"
#include "src/camera/ThirdPersonCamera.h"
#include "src/wrappers/MeshWrapper.hpp"
#include "src/gui/Gui.hpp"
#include "src/skybox/Skybox.hpp"
#include "src/camera/Camera.hpp"

enum SceneType {
    MAIN_SCEEN,
    BATTLE_SCEEN
};

class Scene {

private:
    std::vector<nsGround::Ground *> grounds;
    nsMaterRenderer::MasterRenderer *masterRenderer;
    std::vector<Light *> lights;
    Camera *camera;
    Skybox *skybox;

protected:
    glm::mat4 projection;

public:
    std::vector<Mesh *> objects;
    std::vector<MeshWrapper *> wrappers;
    std::vector<Gui *> guis;
    SceneType sceneType;

    Scene();
    Scene(nsMaterRenderer::MasterRenderer *masterRenderer, std::vector<Light *> lights, glm::mat4 projection,
          Camera *camera);
    void loadObject(Mesh *mesh);
    void loadObject(MeshPtr meshPtr);
    void loadGround(nsGround::Ground *ground);
    virtual void update();
    void animate(float delta);
    void render();
    void clean();
    void loadWrapper(MeshWrapper *wrapper);
    void loadGui(Gui *gui);
    void loadSkybox(Skybox *skybox);
    void loadMasterRenderer(nsMaterRenderer::MasterRenderer *masterRenderer);
    void loadLights(std::vector<Light *> lights);
    void loadLight(Light *light);
    void loadCamera(Camera *camera);
    void loadProjection(glm::mat4 projection);
    void loadGrounds(std::vector<nsGround::Ground *> grounds);
};

#endif //POKEMON3D_SCENE_HPP
