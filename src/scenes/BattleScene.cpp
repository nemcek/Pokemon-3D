//
// Created by Martin on 30. 11. 2015.
//

#include "src/scenes/BattleScene.hpp"

BattleScene::BattleScene(nsMaterRenderer::MasterRenderer *masterRenderer, Camera *camera, Loader *loader, InputManager *inputManager,
                         Pokemon *playersPokemon, Pokemon *enemyPokemon, std::vector<nsGround::Ground *> grounds,
                         Skybox *skybox) {

    this->sceneType = SceneType::BATTLE_SCEEN;
    this->projection = glm::perspective(45.0f, GLfloat(1600) / GLfloat(900), 0.1f, 750.0f);
    this->inputManager = inputManager;
    this->playersPokemon = playersPokemon;
    this->enemyPokemon = enemyPokemon;

    preparePokemon(playersPokemon, &this->playersPokemonData);
    preparePokemon(enemyPokemon, &this->enemyPokemonData);
    initLights();

    camera->setPosition(this->cameraPosition);

    this->loadCamera(camera);
    this->loadMasterRenderer(masterRenderer);
    this->loadProjection(this->projection);

    this->loadObject(playersPokemon);
    this->loadObject(enemyPokemon);
    this->loadSkybox(skybox);
    this->loadGrounds(grounds);

}

void BattleScene::preparePokemon(Pokemon *pokemon, PokemonData *pokemonData) {
    pokemon->setPosition(pokemonData->position);
    pokemon->setRotation(pokemonData->rotation);
    pokemon->setScale(pokemonData->scale);
}

void BattleScene::initLights() {
    Light *light1 = new Light(glm::vec3(-20.0f, 50.0f, 50.0f), glm::vec3(0.7f));
    Light *light2 = new Light(glm::vec3(30.0f, 50.0f, -40.0f), glm::vec3(0.7f));

    this->loadLight(light1);
    this->loadLight(light2);
}

void BattleScene::update() {
    if (this->inputManager->isTPressed()) {
//        for (auto attackLoop : this->playersPokemon->attack()) {
////        for (std::vector<Attack>::iterator it = attacks.begin(); it != attacks.end(); it++) {
//            this->loadObject(attackLoop);
////            this->attacks.push_back(attackLoop);
//        }
        this->playersPokemon->attack(this);
    }
}