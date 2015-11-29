//
// Created by Martin on 29. 11. 2015.
//

#ifndef POKEMON3D_SCENEMANAGER_HPP
#define POKEMON3D_SCENEMANAGER_HPP

#include "src/objects/Scene.hpp"
#include "src/objects/Terrain.h"
#include "src/objects/OtherCharacter.hpp"
#include "src/objects/StreetLamp.hpp"
#include "src/gui/Healthbar.hpp"
#include "src/objects/MainCharacter.h"
#include "src/objects/Ground.hpp"
#include "src/objects/Light.hpp"
#include "src/textures/TerrainTexturePack.hpp"

class SceneManager {

private:

    std::vector<Mesh *> meshes;
    std::vector<nsGround::Ground *> grounds;
    StaticShader *staticShader;
    GroundShader *groundShader;
    Camera *camera;
    std::vector<TerrainTexture *> terrainTextures;
    TerrainTexturePack *terrainTexturePack;
    std::vector<MeshWrapper *> wrappers;
    glm::mat4 projection;
    std::vector<StreetLamp *> lamps;
    nsMeshRenderer::MeshRenderer *meshRenderer;
    GroundRenderer *groundRenderer;
    Loader *guiLoader;
    Loader *loader;
    GuiShader *guiShader;
    Healthbar *healthbar;
    GuiRenderer *guiRenderer;
    SkyboxShader *skyboxShader;
    SkyboxRenderer *skyboxRenderer;
    Skybox *skybox;
    nsMaterRenderer::MasterRenderer *masterRenderer;
    Scene *currentScene;

    float fov = 45.0f;
    int screen_width;
    int screen_height;

    Scene* initStartingScene(GLFWwindow *window, InputManager *inpuManager);

public:
    SceneManager(GLFWwindow *window, InputManager *inputManager);
    void render();
    void animate(float delta);
    void clean();
};

#endif //POKEMON3D_SCENEMANAGER_HPP
