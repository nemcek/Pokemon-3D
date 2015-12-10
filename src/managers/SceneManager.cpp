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
    SceneType sceneType = this->currentScene->animate(delta);

    if (sceneType != this->currentScene->sceneType)
        changeScene(sceneType);
}

void SceneManager::clean() {
    this->currentScene->clean();
}

void SceneManager::changeScene(SceneType sceneType) {
    Scene *newScene;

    if (sceneType == SceneType::MAIN_SCEEN) {
        if (mainScene == nullptr) {
            newScene = new MainScene(this->masterRenderer, this->camera, this->loader,
                                     this->pokemonRepository, this->grounds, this->skybox, this->trees,
                                     this->mainCharacter,
                                     this->terrains, this->inputManager);
        } else {
            newScene = mainScene;
        }
    } else if (sceneType == SceneType::BATTLE_SCEEN) {

        PokemonPtr playerPokemon = this->pokemonRepository->findPokemon(25);
        PlayerPokemonPtr playerPokemonPtr = PlayerPokemonPtr(new PlayerPokemon(playerPokemon->id, loader, playerPokemon,
        playerPokemon->position, playerPokemon->rotX, playerPokemon->rotY, playerPokemon->rotZ, playerPokemon->scale,
        playerPokemon->texturedModel->texture->reflectivity, playerPokemon->texturedModel->texture->shineDamper, this->inputManager, "models/objects/Pikachu.obj",
                                                                               "models/textures/Pikachu.tga"));


        PokemonPtr enemyPokemon = this->pokemonRepository->findPokemon(7);
        EnemyPokemonPtr enemyPokemonPtr = EnemyPokemonPtr(new EnemyPokemon(enemyPokemon->id, loader, enemyPokemon,
                                                                            enemyPokemon->position, enemyPokemon->rotX, enemyPokemon->rotY, enemyPokemon->rotZ, enemyPokemon->scale,
                                                                            enemyPokemon->texturedModel->texture->reflectivity, enemyPokemon->texturedModel->texture->shineDamper, this->inputManager, "models/objects/Squirtle.obj",
                                                                               "models/textures/Squirtle.tga"));
        newScene = new BattleScene(this->masterRenderer, this->camera, this->loader, this->inputManager,
                                 playerPokemonPtr, enemyPokemonPtr,
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

    this->pokemonRepository = PokemonRepositoryPtr(new PokemonRepository());
    this->initMainCharacter(inputManager);
    this->initPokemons(inputManager);
    this->initGrounds(this->staticShader->programId);
    this->initWrappers();
    this->initCamera(window, inputManager);
    this->initTerrain(this->loader);
    this->initSkybox(this->loader);
}

void SceneManager::initStartingScene() {
    changeScene(SceneType::MAIN_SCEEN);
}

void SceneManager::initShaders() {
    this->staticShader = StaticShaderPtr(new StaticShader());
    this->groundShader = GroundShaderPtr(new GroundShader());
    this->guiShader = GuiShaderPtr(new GuiShader());
    this->skyboxShader = SkyboxShaderPtr(new SkyboxShader());
}

void SceneManager::initLoaders() {
    this->loader = LoaderPtr(new Loader(staticShader->programId));
    this->guiLoader = LoaderPtr(new Loader(guiShader->programId));
}

void SceneManager::initRenderers() {
    this->meshRenderer = MeshRendererPtr(new MeshRenderer(staticShader));
    this->groundRenderer = GroundRendererPtr(new GroundRenderer(groundShader));
    this->guiRenderer = GuiRendererPtr(new GuiRenderer(guiShader, guiLoader));
    this->skyboxRenderer = SkyboxRendererPtr(new SkyboxRenderer(skyboxShader));
    this->masterRenderer = MasterRendererPtr(new MasterRenderer(meshRenderer, groundRenderer, guiRenderer, skyboxRenderer));
}

void SceneManager::initPokemons(InputManager *inputManager) {

    auto squirtle = PokemonPtr(new Pokemon(
            7,
            this->loader,
            "models/objects/Squirtle.obj",
            "models/textures/Squirtle.tga",
            glm::vec3(-20.0f, 0.0f, -24.0f),
            0.0f, 0.0f, 0.0f, 0.15f,
            this->inputManager,
            "models/objects/Squirtle.obj",
            "models/textures/Squirtle.tga",
            false
    ));
    this->pokemonRepository->add(squirtle);
    this->pokemons.push_back(squirtle);

    auto pikachu = PokemonPtr(new Pokemon(
            25,
            this->loader,
            "models/objects/Pikachu.obj",
            "models/textures/Pikachu.tga",
            glm::vec3(5.0f, 0.0f, -100.0f),
            0.0f, 0.0f, 0.0f, 0.15f,
            this->inputManager,
            "models/objects/Pikachu.obj",
            "models/textures/Pikachu.tga",
            true
    ));
    this->pokemonRepository->add(pikachu);
    this->pokemons.push_back(pikachu);

}

void SceneManager::initGrounds(GLuint programId) {
    auto backgroundTexture = TerrainTexturePtr(new TerrainTexture(loader->loadTexture("models/textures/Ground_grass3.tga")));
    auto rTexture = TerrainTexturePtr(new TerrainTexture(loader->loadTexture("models/textures/Ground.tga")));
    auto gTexture = TerrainTexturePtr(new TerrainTexture(loader->loadTexture("models/textures/GrassFlowers.tga")));
    auto bTexture = TerrainTexturePtr(new TerrainTexture(loader->loadTexture("models/textures/Path.tga")));
    auto blendMap = TerrainTexturePtr(new TerrainTexture(loader->loadTexture("models/textures/BlendMap.tga")));
    this->terrainTextures.push_back(backgroundTexture);
    this->terrainTextures.push_back(rTexture);
    this->terrainTextures.push_back(gTexture);
    this->terrainTextures.push_back(bTexture);
    this->terrainTextures.push_back(blendMap);

    auto texturePack = TerrainTexturePackPtr(new TerrainTexturePack(backgroundTexture, rTexture, gTexture, bTexture));
    this->terrainTexturePack = texturePack;

    auto ground1 = GroundPtr(new Ground(programId, 0, 0, "models/textures/Ground_grass3.tga", texturePack, blendMap));
    auto ground2 = GroundPtr(new Ground(programId, 1, 0, "models/textures/Ground_grass3.tga", texturePack, blendMap));
    auto ground3 = GroundPtr(new Ground(programId, 0, 1, "models/textures/Ground_grass3.tga", texturePack, blendMap));
    auto ground4 = GroundPtr(new Ground(programId, 1, 1, "models/textures/Ground_grass3.tga", texturePack, blendMap));
    this->grounds.push_back(ground1);
    this->grounds.push_back(ground2);
    this->grounds.push_back(ground3);
    this->grounds.push_back(ground4);
}

void SceneManager::initWrappers() {
    auto treesWrapper = MeshWrapperPtr(new MeshWrapper(loader, "models/objects/Tree2.obj", "models/textures/Tree2.tga", 300,
                                               glm::vec3(50.0f, 75.0f, 1.0f)));
    auto treesWrapper2 = MeshWrapperPtr(new MeshWrapper(loader, "models/objects/Tree.obj", "models/textures/Tree.tga", 300,
                                                glm::vec3(4.0f, 2.0f, 100.f)));
    this->grassWrapper = GrassWrapperPtr(new GrassWrapper(loader, "models/objects/Grass.obj", "models/textures/Grass.tga",
    glm::vec3(0.0f), 0.0f, 0.0f, 0.0f, 1.0f));

    this->trees.push_back(treesWrapper);
    this->trees.push_back(treesWrapper2);
}

void SceneManager::initMainCharacter(InputManager *inputManager) {
    this->mainCharacter = MainCharacterPtr(new MainCharacter(
            loader,
            "models/objects/Trainer.obj",
            "models/textures/Trainer.tga",
            glm::vec3(0.0f),
            0.0f, 180.0f, 0.0f, 0.1f, 0.2f, 50.0f,
            inputManager
    ));
}

void SceneManager::initCamera(GLFWwindow *window, InputManager *inputManager) {
    this->camera = CameraPtr(new ThirdPersonCamera(mainCharacter, window, inputManager));
}

void SceneManager::initSkybox(LoaderPtr loader) {
    this->skybox = SkyboxPtr(new Skybox(loader));
}

void SceneManager::initTerrain(LoaderPtr loader) {
    this->terrains.push_back(TerrainPtr(new Terrain(
            loader,
            "models/objects/Pokecenter.obj",
            "models/textures/Pokecenter.tga",
            glm::vec3(30.0f, 0.0f, -50.0f),
            0.0f, 180.0f, 0.0f, 20.0f, 1.0f, 50.0f
    )));

    grassWrapper->generateGrass(glm::vec2(5.0f, 5.0f), glm::vec2(25.0f, 35.0f));

    for (auto grassLoop : grassWrapper->grassParts) {
        this->terrains.push_back(grassLoop);
    }

//    grassWrapper->grassParts.clear();
//
//    grassWrapper->generateGrass(glm::vec2(55.0f, 10.0f), glm::vec2(105.0f, 100.0f));
//
//    for (auto grassLoop : grassWrapper->grassParts) {
//        this->terrains.push_back(grassLoop);
//    }
}
