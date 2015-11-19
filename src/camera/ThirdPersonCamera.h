//
// Created by Martin on 16. 11. 2015.
//

#ifndef POKEMON3D_THIRDPERSONCAMERA_H
#define POKEMON3D_THIRDPERSONCAMERA_H

#include "src/objects/MainCharacter.h"

namespace nsThirdPersonCamera {

    class ThirdPersonCamera {

    private:

        glm::vec3 position;
        float pitch;
        float yaw;
        float distance;
        float angle;
        glm::vec3 prevPos;
        glm::vec3 currPos;
        bool leftButtonPressed;
        bool rightButtonPressed;
        int windowHeight;
        int windowWidth;
        MainCharacter *mainCharacter;

        void calculateZoom();
        void calculatePitch();
        void calculateAngle();
        float calculateHorizontalDistance();
        float calculateVerticalDistance();
        void calculateCameraPosition(float horizntalDistance, float verticalDistance);

    public:
        ThirdPersonCamera(MainCharacter *mainCharacter, GLFWwindow * window);
        glm::vec3 getPosition();
        glm::vec3 getPitch();
        void mouseButtonCallback( GLFWwindow * window, int button, int action, int mods );
        void cursorCallback( GLFWwindow *, double x, double y );
        void wheelCallBack( GLFWwindow *, double, double yoffset );
        glm::vec3 toScreenCoord( double x, double y );
        void move();
        glm::mat4 getViewMatrix();

    };

}

#endif //POKEMON3D_THIRDPERSONCAMERA_H
