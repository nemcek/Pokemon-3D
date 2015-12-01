//
// Created by Martin on 30. 11. 2015.
//

#ifndef POKEMON3D_BATTLESCENE_HPP
#define POKEMON3D_BATTLESCENE_HPP

#include "src/objects/Scene.hpp"
#include "src/objects/Pokemon.hpp"
#include "src/repository/Repository.hpp"

class BattleScene : public Scene {

private:
    glm::vec3 cameraPosition = glm::vec3(0.0f);
    PokemonData playersPokemonData {
        0,
        glm::vec3(0.0f, 180.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, 5.0f),
        0.15f
    };

    PokemonData enemyPokemonData {
        0,
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, -5.0f),
        0.15f
    };

    InputManager *inputManager;
    Pokemon *playersPokemon;
    Pokemon *enemyPokemon;
    std::vector<Attack *> attacks;

    void preparePokemon(Pokemon *pokemon, PokemonData *pokemonData);
    void initLights();
public:
    BattleScene(nsMaterRenderer::MasterRenderer *masterRenderer, Camera *camera, Loader *loader, InputManager *inputManager,
                Pokemon *playersPokemon, Pokemon *enemyPokemon, std::vector<nsGround::Ground *> grounds, Skybox *skybox);
    void update() override;
};

#endif //POKEMON3D_BATTLESCENE_HPP
