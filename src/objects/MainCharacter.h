//
// Created by Martin on 15. 11. 2015.
//

#ifndef POKEMON3D_MAINCHARACTER_H
#define POKEMON3D_MAINCHARACTER_H

#include "MovableCharacter.hpp"
#include "src/enums/Enums.hpp"

class MainCharacter: public MovableCharacter {

private:

protected:
    InputManager *inputManager;
    float runSpeed = 20.0f;
    float turnSpeed = 160.0f;

    void checkInputs();

public:

    MainCharacter(LoaderPtr loader, const std::string &, const std::string &, glm::vec3 position, float rotX, float rotY,
                  float rotZ, float scale, InputManager *inputManager);
    MainCharacter(LoaderPtr loader, const std::string &, const std::string &, glm::vec3 position, float rotX, float rotY, float rotZ,
                  float scale, float reflectivity, float shineDamper, InputManager *inputManager);
    MainCharacter(LoaderPtr loader, MeshPtr mesh, glm::vec3 position, float rotX, float rotY, float rotZ,
                  float scale, float reflectivity, float shineDamper, InputManager *inputManager);
    SceneType animate(Scene &scene, float delta) override;
};

typedef std::shared_ptr<MainCharacter> MainCharacterPtr;

#endif //POKEMON3D_MAINCHARACTER_H
