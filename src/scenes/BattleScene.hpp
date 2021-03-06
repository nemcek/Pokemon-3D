//
// Created by Martin on 30. 11. 2015.
//

#ifndef POKEMON3D_BATTLESCENE_HPP
#define POKEMON3D_BATTLESCENE_HPP

#include "src/objects/Scene.hpp"
#include "src/objects/PlayerPokemon.hpp"
#include "src/objects/EnemyPokemon.hpp"
#include "src/repository/Repository.hpp"

class BattleScene : public Scene {

private:
    glm::vec3 cameraPosition = glm::vec3(0.0f);
    float cameraRotX = 0.0f;
    float cameraRotY = 180.0f;
    float cameraRotZ = 0.0f;

    PokemonData playersPokemonData {
        0,
        glm::vec3(0.0f, 180.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, 5.0f),
        0.15f,
        20
    };

    PokemonData enemyPokemonData {
        0,
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, -5.0f),
        0.15f,
        20
    };

    PokemonPtr playersPokemon;
    PokemonPtr enemyPokemon;
    std::vector<AttackPtr> attacks;

    void preparePokemon(PokemonPtr pokemon, PokemonData *pokemonData);
    void initLights();
public:
    BattleScene(MasterRendererPtr masterRenderer, CameraPtr camera, LoaderPtr loader, InputManager *inputManager,
                PlayerPokemonPtr playersPokemon, EnemyPokemonPtr enemyPokemon, std::vector<GroundPtr> grounds, SkyboxPtr skybox);
    void update() override;
};

#endif //POKEMON3D_BATTLESCENE_HPP
