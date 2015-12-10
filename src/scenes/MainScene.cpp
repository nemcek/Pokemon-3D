//
// Created by Martin on 30. 11. 2015.
//

#include "src/scenes/MainScene.hpp"

MainScene::MainScene(MasterRendererPtr masterRenderer, CameraPtr camera, LoaderPtr loader,
                     PokemonRepositoryPtr pokemonRepository, std::vector<GroundPtr> grounds,
                     SkyboxPtr skybox, std::vector<MeshWrapperPtr> trees, MainCharacterPtr mainCharacter,
                     std::vector<TerrainPtr> terrains, InputManager *inputManager) : Scene() {

    AnimationPtr animation = AnimationPtr(new Animation());
    animation->add(KeyframePtr(new Keyframe(0, glm::vec3(15.0f, 0.0f, 0.0f), glm::vec3(0.0f))));
    animation->add(KeyframePtr(new Keyframe(1, glm::vec3(15.0f, 0.0f, 2.5f), glm::vec3(0.0f))));
    animation->add(KeyframePtr(new Keyframe(2, glm::vec3(10.0f, 0.0f, 2.5f), glm::vec3(0.0f, 90.0f, 0.0f))));
    animation->add(KeyframePtr(new Keyframe(3, glm::vec3(10.0f, 0.0f, -2.5f), glm::vec3(0.0f, 65.0f, 0.0f))));
    animation->add(KeyframePtr(new Keyframe(4, glm::vec3(15.0f, 0.0f, -2.5f), glm::vec3(0.0f, 270.0f, 0.0f))));
    animation->add(KeyframePtr(new Keyframe(5, glm::vec3(15.0f, 0.0f, 0.0f), glm::vec3(0.0f, 360.0f, 0.0f))));
    this->pokemonData[1].animation = animation;

    this->inputManager = inputManager;
    this->sceneType = SceneType::MAIN_SCEEN;
    this->projection = glm::perspective(45.0f, GLfloat(1600) / GLfloat(900), 0.1f, 750.0f);
    this->loadMasterRenderer(masterRenderer);
    this->loadCamera(camera);
    this->loadProjection(this->projection);

    // load main character
    this->loadObject(mainCharacter);
    camera->setFollowTarget(mainCharacter);
    this->mainCharacter = mainCharacter;

    // load pokemons with specified data
    for (auto pokemonDataLoop : this->pokemonData) {
        auto pokemon = pokemonRepository->findPokemon(pokemonDataLoop.id);

        pokemon->setPosition(pokemonDataLoop.position);
        pokemon->setRotation(pokemonDataLoop.rotation);
        pokemon->setScale(pokemonDataLoop.scale);
        pokemon->animation = pokemonDataLoop.animation;

        this->loadObject(pokemon);
    }

    // load grounds
    for (auto groundLoop : grounds) {
        this->loadGround(groundLoop);
    }

    // load trees
    for (auto treeLoop : trees) {
        this->loadWrapper(treeLoop);
    }

    auto light1 = LightPtr(new Light(glm::vec3(50.0f, 50.0f, 50.0f), glm::vec3(0.9f)));
    auto lamp1 = StreetLampPtr(new StreetLamp(loader, glm::vec3(50.0f, 0.0f, 0.0f)));
    auto lamp2 = StreetLampPtr(new StreetLamp(loader, glm::vec3(-100.0f, 0.0f, 50.0f)));
    auto lamp3 = StreetLampPtr(new StreetLamp(loader, glm::vec3(-50.0f, 0.0f, -100.0f)));

    this->loadLight(light1);
    this->loadLight(lamp1->light);
    this->loadLight(lamp2->light);
    this->loadLight(lamp3->light);

    this->loadObject(lamp1);
    this->loadObject(lamp2);
    this->loadObject(lamp3);

    this->loadProjection(glm::perspective(45.0f, GLfloat(1600) / GLfloat(900), 0.1f, 750.0f));

    // load terrains
    for (auto terrainLoop : terrains) {
        this->loadObject(terrainLoop);
    }
    this->loadSkybox(skybox);
}
