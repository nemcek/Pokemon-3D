//
// Created by Martin on 30. 11. 2015.
//

#ifndef POKEMON3D_MAINSCENE_HPP
#define POKEMON3D_MAINSCENE_HPP

#include "src/objects/Scene.hpp"
#include "src/repository/PokemonRepository.hpp"
#include "src/engine/MasterRenderer.hpp"
#include "src/camera/Camera.hpp"
#include "src/objects/StreetLamp.hpp"

class MainScene : public Scene {

private:

    std::vector<PokemonData> pokemonData = {
        PokemonData {
            7,
            glm::vec3(0.0f),
            glm::vec3(-20.0f, 0.0f, -24.0f),
            0.15f
        },
        PokemonData {
            25,
            glm::vec3(0.0f),
            glm::vec3(15.0f, 0.0f, 0.0f),
            0.15f
        }
    };

public:
    MainScene(nsMaterRenderer::MasterRenderer *masterRenderer, Camera *camera, Loader *loader,
            PokemonRepository *pokemonRepository, std::vector<nsGround::Ground *> grounds, Skybox *skybox,
            std::vector<MeshWrapper *> trees, MainCharacter *mainCharacter, std::vector<Terrain *> terrains);
};

#endif //POKEMON3D_MAINSCENE_HPP
