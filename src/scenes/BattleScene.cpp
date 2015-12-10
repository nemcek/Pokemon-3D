//
// Created by Martin on 30. 11. 2015.
//

#include <gui/Healthbar.hpp>
#include "src/scenes/BattleScene.hpp"

BattleScene::BattleScene(MasterRendererPtr masterRenderer, CameraPtr camera, LoaderPtr loader, InputManager *inputManager,
                         PlayerPokemonPtr playersPokemon, EnemyPokemonPtr enemyPokemon, std::vector<GroundPtr> grounds,
                         SkyboxPtr skybox) {

    this->sceneType = SceneType::BATTLE_SCEEN;
    this->projection = glm::perspective(45.0f, GLfloat(1600) / GLfloat(900), 0.1f, 750.0f);
    this->inputManager = inputManager;
    this->playersPokemon = playersPokemon;
    this->enemyPokemon = enemyPokemon;

    preparePokemon(playersPokemon, &this->playersPokemonData);
    preparePokemon(enemyPokemon, &this->enemyPokemonData);
    initLights();

    camera->setFollowTarget(&cameraPosition, &cameraRotX, &cameraRotY, &cameraRotZ);

    this->loadCamera(camera);
    this->loadMasterRenderer(masterRenderer);
    this->loadProjection(this->projection);

    this->loadObject(playersPokemon);
    this->loadObject(enemyPokemon);
    this->loadSkybox(skybox);
    this->loadGrounds(grounds);
    this->loadGui(HealthbarPtr(new Healthbar(playersPokemon,"models/textures/HealthbarFill.tga", "models/textures/Healthbar.tga"
            , loader, HealthbarPosition::BOTTOM_RIGHT)));
    this->loadGui(HealthbarPtr(new Healthbar(enemyPokemon,"models/textures/HealthbarFill.tga", "models/textures/Healthbar.tga"
            , loader, HealthbarPosition::TOP_LEFT)));
}

void BattleScene::preparePokemon(PokemonPtr pokemon, PokemonData *pokemonData) {
    pokemon->setPosition(pokemonData->position);
    pokemon->startingPos = pokemonData->position;
    pokemon->setRotation(pokemonData->rotation);
    pokemon->setScale(pokemonData->scale);
    pokemon->maxHp = pokemonData->maxHp;
    pokemon->currentHp = pokemonData->maxHp;
}

void BattleScene::initLights() {
    auto light1 = LightPtr(new Light(glm::vec3(-20.0f, 50.0f, 50.0f), glm::vec3(0.7f)));
    auto light2 = LightPtr(new Light(glm::vec3(30.0f, 50.0f, -40.0f), glm::vec3(0.7f)));

    this->loadLight(light1);
    this->loadLight(light2);
}

void BattleScene::update() {
//    if (this->inputManager->isTPressed()) {
//        this->playersPokemon->attack(*this);
//    }
}