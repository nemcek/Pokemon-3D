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
    std::vector<GroundPtr> grounds;
    MasterRendererPtr masterRenderer;
    std::vector<LightPtr> lights;
    CameraPtr camera;
    SkyboxPtr skybox;

protected:
    glm::mat4 projection;

public:
//    std::vector<Mesh *> objects;
    std::vector<MeshPtr> objects;
    std::vector<MeshWrapperPtr> wrappers;
    std::vector<GuiPtr> guis;
    SceneType sceneType;

    Scene();
    Scene(MasterRendererPtr masterRenderer, std::vector<LightPtr> lights, glm::mat4 projection,
          CameraPtr camera);
//    void loadObject(Mesh *mesh);
    void loadObject(MeshPtr meshPtr);
    void loadGround(GroundPtr ground);
    virtual void update();
    void animate(float delta);
    void render();
    void clean();
    void loadWrapper(MeshWrapperPtr wrapper);
    void loadGui(GuiPtr gui);
    void loadSkybox(SkyboxPtr skybox);
    void loadMasterRenderer(MasterRendererPtr masterRenderer);
    void loadLights(std::vector<LightPtr> lights);
    void loadLight(LightPtr light);
    void loadCamera(CameraPtr camera);
    void loadProjection(glm::mat4 projection);
    void loadGrounds(std::vector<GroundPtr> grounds);
};

typedef std::shared_ptr<Scene> ScenePtr;

#endif //POKEMON3D_SCENE_HPP
