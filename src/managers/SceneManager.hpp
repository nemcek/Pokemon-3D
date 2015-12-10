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
#include "src/wrappers/GrassWrapper.hpp"

class SceneManager {

private:

    std::vector<TerrainPtr > terrains;
    std::vector<GroundPtr> grounds;
    std::vector<GuiPtr> guis;
    StaticShaderPtr staticShader;
    GroundShaderPtr groundShader;
    CameraPtr camera;
    std::vector<TerrainTexturePtr > terrainTextures;
    TerrainTexturePackPtr terrainTexturePack;
    std::vector<MeshWrapperPtr> trees;
    glm::mat4 projection;
    std::vector<StreetLampPtr> lamps;
    MeshRendererPtr meshRenderer;
    GroundRendererPtr groundRenderer;
    LoaderPtr guiLoader;
    LoaderPtr loader;
    GuiShaderPtr guiShader;
    GuiRendererPtr guiRenderer;
    SkyboxShaderPtr skyboxShader;
    SkyboxRendererPtr skyboxRenderer;
    SkyboxPtr skybox;
    MasterRendererPtr masterRenderer;
    MainCharacterPtr mainCharacter;
    InputManager *inputManager;
    GrassWrapperPtr grassWrapper;

    Scene *mainScene = nullptr;
    Scene *previousScene;
    PokemonRepositoryPtr pokemonRepository;
    std::vector<PokemonPtr> pokemons;

    int screen_width;
    int screen_height;

    void initStartingScene();
    void initPokemons(InputManager *inputManager);
    void initGrounds(GLuint programId);
    void initWrappers();
    void initMainCharacter(InputManager *inputManager);
    void initCamera(GLFWwindow *window, InputManager *inputManager);
    void initSkybox(LoaderPtr loader);
    void initTerrain(LoaderPtr loader);
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

    Scene *currentScene;
};

#endif //POKEMON3D_SCENEMANAGER_HPP
