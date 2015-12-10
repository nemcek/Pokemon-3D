//
// Created by Martin on 7. 12. 2015.
//

#ifndef POKEMON3D_MAINPOKEMON_HPP
#define POKEMON3D_MAINPOKEMON_HPP

#include "src/objects/Pokemon.hpp"

class PlayerPokemon : public Pokemon {

private:

public:
    PlayerPokemon(unsigned short id, LoaderPtr loader, const std::string &, const std::string &, glm::vec3 position, float rotX,
            float rotY, float rotZ, float scale, InputManager *inputManager, const std::string &attack_obj_file,
            const std::string &attack_image_name);
    PlayerPokemon(unsigned short id, LoaderPtr loader, const std::string &, const std::string &, glm::vec3 position, float rotX,
            float rotY, float rotZ, float scale, float reflectivity, float shineDamper, InputManager *inputManager,
            const std::string &attack_obj_file, const std::string &attack_image_name);
    PlayerPokemon(unsigned short id, LoaderPtr loader, MeshPtr mesh, glm::vec3 position, float rotX,
                  float rotY, float rotZ, float scale, float reflectivity, float shineDamper, InputManager *inputManager,
                  const std::string &attack_obj_file, const std::string &attack_image_name);

    SceneType animate(Scene &scene, float delta) override;
};

typedef std::shared_ptr<PlayerPokemon> PlayerPokemonPtr;

#endif //POKEMON3D_MAINPOKEMON_HPP
