//
// Created by Martin on 30. 11. 2015.
//

#ifndef POKEMON3D_POKEMON_HPP
#define POKEMON3D_POKEMON_HPP

#include <random>

#include "src/objects/MainCharacter.h"
#include "src/objects/Attack.hpp"
#include "src/animations/Animation.hpp"

class Pokemon : public MainCharacter {
protected:

    // TODO: v MainCharacter zmenit funkciu checkInput() na virtualnu a vytvorit novu class Player pre hlavnu postavu
    void checkInputs();
    void generateAttacks(int count, Scene &scene);

    AttackPtr attackObj;
    float attackDelay = 0.0f;
    bool canAttack = true;
    bool wasAttacked = false;

public:
    unsigned short id;

    Pokemon(unsigned short id, LoaderPtr loader, const std::string &, const std::string &, glm::vec3 position, float rotX,
            float rotY, float rotZ, float scale, InputManager *inputManager, const std::string &attack_obj_file,
            const std::string &attack_image_name, bool canAttackAtStart);
    Pokemon(unsigned short id, LoaderPtr loader, const std::string &, const std::string &, glm::vec3 position, float rotX,
            float rotY, float rotZ, float scale, float reflectivity, float shineDamper, InputManager *inputManager,
            const std::string &attack_obj_file, const std::string &attack_image_name, bool canAttackAtStart);
    Pokemon(unsigned short id, LoaderPtr loader, MeshPtr, glm::vec3 position, float rotX,
            float rotY, float rotZ, float scale, float reflectivity, float shineDamper, InputManager *inputManager,
            const std::string &attack_obj_file, const std::string &attack_image_name, bool canAttackAtStart);
    SceneType animate(Scene &scene, float delta) override;
    void attack(Scene &scene);

    int maxHp = 1;
    int currentHp = 1;
    glm::vec3 startingPos;
    AnimationPtr animation;

    ~Pokemon(){}
};

typedef std::shared_ptr<Pokemon> PokemonPtr;

#endif //POKEMON3D_POKEMON_HPP
