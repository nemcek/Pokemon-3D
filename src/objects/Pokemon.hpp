//
// Created by Martin on 30. 11. 2015.
//

#ifndef POKEMON3D_POKEMON_HPP
#define POKEMON3D_POKEMON_HPP

#include <iostream>
#include <random>

#include "src/objects/MainCharacter.h"
#include "Attack.hpp"

class Pokemon : public MainCharacter {
private:

    // TODO: v MainCharacter zmenit funkciu checkInput() na virtualnu a vytvorit novu class Player pre hlavnu postavu
    void checkInputs();
    std::vector<Attack *> generateAttacks(int count, Scene *scene);

    AttackPtr attackObj;
//    Attack *attackObj;
public:
    unsigned short id;
    std::vector<Attack *> attacks;

    Pokemon(unsigned short id, LoaderPtr loader, const std::string &, const std::string &, glm::vec3 position, float rotX,
            float rotY, float rotZ, float scale, InputManager *inputManager, const std::string &attack_obj_file,
            const std::string &attack_image_name);
    Pokemon(unsigned short id, LoaderPtr loader, const std::string &, const std::string &, glm::vec3 position, float rotX,
            float rotY, float rotZ, float scale, float reflectivity, float shineDamper, InputManager *inputManager,
            const std::string &attack_obj_file, const std::string &attack_image_name);
    void animate(Scene *scene, float delta) override;
    std::vector<Attack *> attack(Scene *scene);
};

typedef std::shared_ptr<Pokemon> PokemonPtr;

#endif //POKEMON3D_POKEMON_HPP
