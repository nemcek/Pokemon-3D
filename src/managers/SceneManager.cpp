//
// Created by Martin on 29. 11. 2015.
//

#include "src/managers/SceneManager.hpp"

SceneManager::SceneManager(GLFWwindow *window, InputManager *inputManager) {
    this->inputManager = inputManager;

    init(window, inputManager);
    initStartingScene();
}

void SceneManager::render() {
    this->currentScene->render();
}

void SceneManager::animate(float delta) {
    this->currentScene->update();
    this->currentScene->animate(delta);
}

void SceneManager::clean() {
    this->currentScene->clean();
}

void SceneManager::changeScene(SceneType sceneType) {
    Scene *newScene;

    if (sceneType == SceneType::MAIN_SCEEN) {

        newScene = new MainScene(this->masterRenderer, this->camera, this->loader,
                                 this->pokemonRepository, this->grounds, this->skybox, this->trees, this->mainCharacter,
                                 this->terrains);
    } else if (sceneType == SceneType::BATTLE_SCEEN) {
        newScene = new BattleScene(this->masterRenderer, this->camera, this->loader, this->inputManager,
                                 this->pokemonRepository->findPokemon(25), this->pokemonRepository->findPokemon(7),
                                 this->grounds, this->skybox);
    }
    this->previousScene = this->currentScene;
    this->currentScene = newScene;
}

void SceneManager::init(GLFWwindow *window, InputManager *inputManager) {
    initShaders();
    initLoaders();
    initRenderers();

    glfwGetWindowSize(window, &screen_width, &screen_height);

    this->pokemonRepository = new PokemonRepository();
    this->initPokemons(inputManager);
    this->initGrounds(this->staticShader->programId);
    this->initWrappers();
    this->initMainCharacter(inputManager);
    this->initCamera(window, inputManager);
    this->initTerrain(this->loader);
    this->initSkybox(this->loader);
}

void SceneManager::initStartingScene() {
    changeScene(SceneType::MAIN_SCEEN);
}

void SceneManager::initShaders() {
    this->staticShader = new StaticShader();
    this->groundShader = new GroundShader();
    this->guiShader = new GuiShader();
    this->skyboxShader = new SkyboxShader();
}

void SceneManager::initLoaders() {
    this->loader = new Loader(staticShader->programId);
    this->guiLoader = new Loader(guiShader->programId);
}

void SceneManager::initRenderers() {
    this->meshRenderer= new nsMeshRenderer::MeshRenderer(staticShader);
    this->groundRenderer = new GroundRenderer(groundShader);
    this->guiRenderer = new GuiRenderer(guiShader, guiLoader);
    this->skyboxRenderer = new SkyboxRenderer(skyboxShader);
    this->masterRenderer = new nsMaterRenderer::MasterRenderer(meshRenderer, groundRenderer, guiRenderer, skyboxRenderer);
}

void SceneManager::initPokemons(InputManager *inputManager) {

    Pokemon *squirtle = new Pokemon(
            7,
            this->loader,
            "models/objects/Squirtle.obj",
            "models/textures/Squirtle.tga",
            glm::vec3(-20.0f, 0.0f, -24.0f),
            0.0f, 0.0f, 0.0f, 0.15f,
            inputManager,
            "models/objects/Squirtle.obj",
            "models/textures/Squirtle.tga"
    );
    this->pokemonRepository->add(squirtle);

    Pokemon *pikachu = new Pokemon(
            25,
            this->loader,
            "models/objects/Pikachu.obj",
            "models/textures/Pikachu.tga",
            glm::vec3(5.0f, 0.0f, -100.0f),
            0.0f, 0.0f, 0.0f, 0.15f,
            inputManager,
            "models/objects/Pikachu.obj",
            "models/textures/Pikachu.tga"
    );
    this->pokemonRepository->add(pikachu);

}

void SceneManager::initGrounds(GLuint programId) {
    TerrainTexture *backgroundTexture = new TerrainTexture(loader->loadTexture("models/textures/Ground_grass3.tga"));
    TerrainTexture *rTexture = new TerrainTexture(loader->loadTexture("models/textures/Ground.tga"));
    TerrainTexture *gTexture = new TerrainTexture(loader->loadTexture("models/textures/GrassFlowers.tga"));
    TerrainTexture *bTexture = new TerrainTexture(loader->loadTexture("models/textures/Path.tga"));
    TerrainTexture *blendMap = new TerrainTexture(loader->loadTexture("models/textures/BlendMap.tga"));
    this->terrainTextures.push_back(backgroundTexture);
    this->terrainTextures.push_back(rTexture);
    this->terrainTextures.push_back(gTexture);
    this->terrainTextures.push_back(bTexture);
    this->terrainTextures.push_back(blendMap);

    TerrainTexturePack *texturePack = new TerrainTexturePack(backgroundTexture, rTexture, gTexture, bTexture);
    this->terrainTexturePack = texturePack;

    nsGround::Ground *ground1 = new nsGround::Ground(programId, 0, 0, "models/textures/Ground_grass3.tga", texturePack, blendMap);
    nsGround::Ground *ground2 = new nsGround::Ground(programId, 1, 0, "models/textures/Ground_grass3.tga", texturePack, blendMap);
    nsGround::Ground *ground3 = new nsGround::Ground(programId, 0, 1, "models/textures/Ground_grass3.tga", texturePack, blendMap);
    nsGround::Ground *ground4 = new nsGround::Ground(programId, 1, 1, "models/textures/Ground_grass3.tga", texturePack, blendMap);
    this->grounds.push_back(ground1);
    this->grounds.push_back(ground2);
    this->grounds.push_back(ground3);
    this->grounds.push_back(ground4);
}

void SceneManager::initWrappers() {
    MeshWrapper *treesWrapper = new MeshWrapper(loader, "models/objects/Tree2.obj", "models/textures/Tree2.tga", 300,
                                               glm::vec3(50.0f, 75.0f, 1.0f));
    MeshWrapper *treesWrapper2 = new MeshWrapper(loader, "models/objects/Tree.obj", "models/textures/Tree.tga", 300,
                                                glm::vec3(4.0f, 2.0f, 100.f));
    this->trees.push_back(treesWrapper);
    this->trees.push_back(treesWrapper2);
}

void SceneManager::initMainCharacter(InputManager *inputManager) {
    this->mainCharacter = new MainCharacter(
            loader,
            "models/objects/Trainer.obj",
            "models/textures/Trainer.tga",
            glm::vec3(0.0f),
            0.0f, 180.0f, 0.0f, 0.1f, 0.2f, 50.0f,
            inputManager
    );
}

void SceneManager::initCamera(GLFWwindow *window, InputManager *inputManager) {
    this->camera = new nsThirdPersonCamera::ThirdPersonCamera(mainCharacter, window, inputManager);
}

void SceneManager::initSkybox(Loader *loader) {
    this->skybox = new Skybox(loader);
}

void SceneManager::initTerrain(Loader *loader) {
//    this->terrains.push_back(new Terrain(
//            loader,
//            "models/objects/Pokecenter.obj",
//            "models/textures/Pokecenter.tga",
//            glm::vec3(30.0f, 0.0f, -50.0f),
//            0.0f, 180.0f, 0.0f, 20.0f, 1.0f, 50.0f
//    ));
}