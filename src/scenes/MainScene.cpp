//
// Created by Martin on 30. 11. 2015.
//

#include "src/scenes/MainScene.hpp"

MainScene::MainScene(MasterRendererPtr masterRenderer, CameraPtr camera, LoaderPtr loader,
                     PokemonRepositoryPtr pokemonRepository, std::vector<GroundPtr> grounds,
                     SkyboxPtr skybox, std::vector<MeshWrapperPtr> trees, MainCharacterPtr mainCharacter,
                     std::vector<TerrainPtr> terrains) : Scene() {

    this->sceneType = SceneType::MAIN_SCEEN;
    this->projection = glm::perspective(45.0f, GLfloat(1600) / GLfloat(900), 0.1f, 750.0f);
    this->loadMasterRenderer(masterRenderer);
    this->loadCamera(camera);
    this->loadProjection(this->projection);

    // load pokemons with specified data
    for (auto pokemonDataLoop : this->pokemonData) {
        auto pokemon = pokemonRepository->findPokemon(pokemonDataLoop.id);

        pokemon->setPosition(pokemonDataLoop.position);
        pokemon->setRotation(pokemonDataLoop.rotation);
        pokemon->setScale(pokemonDataLoop.scale);

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

    auto light1 = LightPtr(new Light(glm::vec3(150.0f, 50.0f, 150.0f), glm::vec3(0.7f)));
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

    // load main character
    this->loadObject(mainCharacter);
    camera->setFollowTarget(mainCharacter);

    // load terrains
    for (auto terrainLoop : terrains) {
        this->loadObject(terrainLoop);
    }
    this->loadSkybox(skybox);
}
