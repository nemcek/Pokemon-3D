//
// Created by Martin on 29. 11. 2015.
//

#include "src/managers/SceneManager.hpp"

SceneManager::SceneManager(GLFWwindow *window, InputManager *inputManager) {
    this->currentScene = this->initStartingScene(window, inputManager);
}

void SceneManager::render() {
    this->currentScene->render();
}

void SceneManager::animate(float delta) {
    this->currentScene->animate(delta);
}

void SceneManager::clean() {
    this->currentScene->clean();
}

Scene* SceneManager::initStartingScene(GLFWwindow *window, InputManager *inputManager) {

    this->staticShader = new StaticShader();
    this->groundShader = new GroundShader();
    this->loader = new Loader(staticShader->programId);
    GLuint program_id = staticShader->programId;

    MainCharacter *mainCharacter = new MainCharacter(
            program_id,
            loader,
            "models/objects/Trainer.obj",
            "models/textures/Trainer.tga",
            glm::vec3(0.0f),
            0.0f, 180.0f, 0.0f, 0.1f, 0.2f, 50.0f,
            inputManager
    );
    nsThirdPersonCamera::ThirdPersonCamera *personCam = new nsThirdPersonCamera::ThirdPersonCamera(mainCharacter, window, inputManager);
    this->camera = personCam;
//    Terrain *pokecenter = new Terrain(
//            program_id,
//            loader,
//            "models/objects/Pokecenter.obj",
//            "models/textures/Pokecenter.tga",
//            glm::vec3(30.0f, 0.0f, -50.0f),
//            0.0f, 180.0f, 0.0f, 20.0f, 1.0f, 50.0f
//    );

    OtherCharacter *squirle = new OtherCharacter(
            program_id,
            loader,
            "models/objects/Squirtle.obj",
            "models/textures/Squirtle.tga",
            glm::vec3(-20.0f, 0.0f, -24.0f),
            0.0f, 0.0f, 0.0f, 0.15f
    );

    Terrain *pikachu = new Terrain(
            program_id,
            loader,
            "models/objects/Pikachu.obj",
            "models/textures/Pikachu.tga",
            glm::vec3(5.0f, 0.0f, -100.0f),
            0.0f, 0.0f, 0.0f, 0.15f
    );

//    this->meshes.push_back(mainCharacter);
//    this->meshes.push_back(pokecenter);
    this->meshes.push_back(squirle);
    this->meshes.push_back(pikachu);

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

    MeshWrapper *meshWrapper = new MeshWrapper(program_id, loader, "models/objects/Tree2.obj", "models/textures/Tree2.tga", 300,
                                               glm::vec3(50.0f, 75.0f, 1.0f));
    MeshWrapper *meshWrapper2 = new MeshWrapper(program_id, loader, "models/objects/Tree.obj", "models/textures/Tree.tga", 300,
                                                glm::vec3(4.0f, 2.0f, 100.f));
    this->wrappers.push_back(meshWrapper);
    this->wrappers.push_back(meshWrapper2);

    nsGround::Ground *ground1 = new nsGround::Ground(program_id, 0, 0, "models/textures/Ground_grass3.tga", texturePack, blendMap);
    nsGround::Ground *ground2 = new nsGround::Ground(program_id, 1, 0, "models/textures/Ground_grass3.tga", texturePack, blendMap);
    nsGround::Ground *ground3 = new nsGround::Ground(program_id, 0, 1, "models/textures/Ground_grass3.tga", texturePack, blendMap);
    nsGround::Ground *ground4 = new nsGround::Ground(program_id, 1, 1, "models/textures/Ground_grass3.tga", texturePack, blendMap);
    this->grounds.push_back(ground1);
    this->grounds.push_back(ground2);
    this->grounds.push_back(ground3);
    this->grounds.push_back(ground4);

//    lastFrameTime = getCurrentTime();
    this->projection = glm::perspective(fov, GLfloat(1600) / GLfloat(900), 0.1f, 750.0f);

    Light *light1 = new Light(glm::vec3(150.0f, 50.0f, 150.0f), glm::vec3(0.7f));
    StreetLamp *lamp1 = new StreetLamp(program_id, loader, glm::vec3(50.0f, 0.0f, 0.0f));
    StreetLamp *lamp2 = new StreetLamp(program_id, loader, glm::vec3(-100.0f, 0.0f, 50.0f));
    StreetLamp *lamp3 = new StreetLamp(program_id, loader, glm::vec3(-50.0f, 0.0f, -100.0f));
    this->lamps.push_back(lamp1);
    this->lamps.push_back(lamp2);
    this->lamps.push_back(lamp3);

    this->meshRenderer= new nsMeshRenderer::MeshRenderer(staticShader);
    this->groundRenderer = new GroundRenderer(groundShader);

    this->guiShader = new GuiShader();
    this->guiLoader = new Loader(guiShader->programId);

    this->healthbar = new Healthbar("models/textures/HealthbarFill.tga", "models/textures/Healthbar.tga", guiLoader, 100);

    this->guiRenderer = new GuiRenderer(guiShader, guiLoader);

    this->skyboxShader = new SkyboxShader();
    this->skyboxRenderer = new SkyboxRenderer(skyboxShader);

    this->skybox = new Skybox(loader);

    this->masterRenderer = new nsMaterRenderer::MasterRenderer(meshRenderer, groundRenderer, guiRenderer, skyboxRenderer);

//    Scene *scene = new Scene(&masterRenderer, lights, projection, personCam);

    Scene *scene = new Scene();
    scene->loadCamera(personCam);
    scene->loadProjection(projection);
//    scene->loadLights(lights);
    scene->loadMasterRenderer(masterRenderer);

    scene->loadLight(light1);
    scene->loadLight(lamp1->light);
    scene->loadLight(lamp2->light);
    scene->loadLight(lamp3->light);

    scene->loadWrapper(meshWrapper);
    scene->loadWrapper(meshWrapper2);

    scene->loadGui(healthbar);

    scene->loadObject(MainCharacterPtr(mainCharacter));
//    scene->loadObject(pokecenter);
    scene->loadObject(pikachu);
    scene->loadObject(squirle);
    scene->loadObject(lamp1);
    scene->loadObject(lamp2);
    scene->loadObject(lamp3);

    scene->loadSkybox(skybox);

    scene->loadGround(ground1);
    scene->loadGround(ground2);
    scene->loadGround(ground3);
    scene->loadGround(ground4);

//    for (std::vector<nsGround::Ground>::iterator it = grounds.begin(); it != grounds.end(); it++) {
//        scene->loadGround(&(*it));
//    }

    return scene;
}