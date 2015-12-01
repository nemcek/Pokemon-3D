//
// Created by Martin on 29. 11. 2015.
//

#ifndef POKEMON3D_SCENEMANAGER_HPP
#define POKEMON3D_SCENEMANAGER_HPP

#include "src/objects/Scene.hpp"
#include "src/scenes/MainScene.hpp"
#include "src/scenes/BattleScene.hpp"
#include "src/objects/Terrain.h"
#include "src/objects/OtherCharacter.hpp"
#include "src/objects/StreetLamp.hpp"
#include "src/gui/Healthbar.hpp"
#include "src/objects/MainCharacter.h"
#include "src/objects/Ground.hpp"
#include "src/objects/Light.hpp"
#include "src/textures/TerrainTexturePack.hpp"
#include "src/repository/PokemonRepository.hpp"

class SceneManager {

private:

    std::vector<Terrain *> terrains;
    std::vector<nsGround::Ground *> grounds;
    StaticShader *staticShader;
    GroundShader *groundShader;
    Camera *camera;
    std::vector<TerrainTexture *> terrainTextures;
    TerrainTexturePack *terrainTexturePack;
    std::vector<MeshWrapper *> trees;
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
    MainCharacter *mainCharacter;
    InputManager *inputManager;

    Scene *currentScene;
    Scene *previousScene;
    PokemonRepository *pokemonRepository;

    int screen_width;
    int screen_height;

    void initStartingScene();
    void initPokemons(InputManager *inputManager);
    void initGrounds(GLuint programId);
    void initWrappers();
    void initMainCharacter(InputManager *inputManager);
    void initCamera(GLFWwindow *window, InputManager *inputManager);
    void initSkybox(Loader *loader);
    void initTerrain(Loader *loader);
    void initShaders();
    void initLoaders();
    void initRenderers();
    void init(GLFWwindow *window, InputManager *inputManager);
public:
    SceneManager(GLFWwindow *window, InputManager *inputManager);
    void render();
    void animate(float delta);
    void clean();
    void changeScene(SceneType sceneType);
};

#endif //POKEMON3D_SCENEMANAGER_HPP