//
// Created by Martin on 16. 11. 2015.
//

#include "src/camera/ThirdPersonCamera.h"

namespace nsThirdPersonCamera {

    ThirdPersonCamera::ThirdPersonCamera(MainCharacter *mainCharacter, GLFWwindow * window)
            : mainCharacter(mainCharacter){
        this->pitch = 20.0f;
        this->angle = 0.0f;
        this->distance = 10.0f;
        this->leftButtonPressed = false;
        this->rightButtonPressed = false;
        this->position = this->mainCharacter->getCenter() + glm::vec3(0.0f, 0.0f, this->distance);

        glfwGetWindowSize(window, &this->windowWidth, &this->windowHeight);
    }

    void ThirdPersonCamera::calculateZoom() {
    }

    void ThirdPersonCamera::wheelCallBack(GLFWwindow *, double, double yoffset) {
        this->distance -= yoffset;
    }

    void ThirdPersonCamera::cursorCallback(GLFWwindow *, double x, double y) {
        if (leftButtonPressed || rightButtonPressed) {
            this->currPos = toScreenCoord(x, y);
        }
    }

    void ThirdPersonCamera::mouseButtonCallback(GLFWwindow *window, int button, int action, int mods) {
        if ((button == GLFW_MOUSE_BUTTON_LEFT || button == GLFW_MOUSE_BUTTON_RIGHT) && action == GLFW_PRESS) {

            double x, y;
            glfwGetCursorPos(window, &x, &y);
            this->prevPos = toScreenCoord(x, y);

            if (button == GLFW_MOUSE_BUTTON_LEFT) {
                leftButtonPressed = true;
            } else {
                rightButtonPressed = true;
            }
        }
        else {
            leftButtonPressed = false;
            rightButtonPressed = false;
        }
    }

    glm::vec3 ThirdPersonCamera::toScreenCoord( double x, double y ) {
        glm::vec3 coord(0.0f);

        coord.x =  (2 * x - windowWidth ) / windowWidth;

        coord.y = -(2 * y - windowHeight) / windowHeight;

        /* Clamp it to border of the windows, comment these codes to allow rotation when cursor is not over window */
        coord.x = glm::clamp( coord.x, -1.0f, 1.0f );
        coord.y = glm::clamp( coord.y, -1.0f, 1.0f );

        float length_squared = coord.x * coord.x + coord.y * coord.y;
        if( length_squared <= 1.0 )
            coord.z = sqrt( 1.0 - length_squared );
        else
            coord = glm::normalize( coord );

        return coord;
    }

    void ThirdPersonCamera::calculatePitch() {
        if (rightButtonPressed) {
            float pitchChange = this->prevPos.y - this->currPos.y;

            this->pitch -= pitchChange;

            if (this->pitch > 179.0f) {
                this->pitch = 179.0f;
            } else if (this->pitch < 1.0f) {
                this->pitch = 1.0f;
            }
        }
    }

    void ThirdPersonCamera::calculateAngle() {
        if (leftButtonPressed) {
            float angleChanged = this->prevPos.x - this->currPos.x;

            this->angle -= angleChanged;
        }
    }

    void ThirdPersonCamera::move() {
        calculateZoom();
        calculatePitch();
        calculateAngle();

        float horDist = calculateHorizontalDistance();
        float vertDist = calculateVerticalDistance();

        calculateCameraPosition(horDist, vertDist);

        this->yaw = 180 - (mainCharacter->rotY + angle);
    }

    float ThirdPersonCamera::calculateHorizontalDistance() {
        return distance * glm::cos(glm::radians(this->pitch));
    }

    float ThirdPersonCamera::calculateVerticalDistance() {
        return distance * glm::sin(glm::radians(this->pitch));
    }

    void ThirdPersonCamera::calculateCameraPosition(float horizntalDistance, float verticalDistance) {
        float theta = mainCharacter->rotY + angle;
        float offsetX = horizntalDistance * glm::sin(glm::radians(theta));
        float offsetZ = horizntalDistance * glm::cos(glm::radians(theta));

        position.x = mainCharacter->position.x - offsetX;
        position.z = mainCharacter->position.z - offsetZ;

        this->position.y = this->mainCharacter->position.y + verticalDistance;
    }

    glm::mat4 ThirdPersonCamera::getViewMatrix() {
        glm::mat4 viewMatrix;

        viewMatrix = glm::rotate(viewMatrix, glm::radians(this->pitch), glm::vec3(1.0f, 0.0f, 0.0f));
        viewMatrix = glm::rotate(viewMatrix, glm::radians(this->yaw), glm::vec3(0.0f, 1.0f, 0.0f));
        viewMatrix = glm::translate(viewMatrix, glm::vec3(-this->position.x, -this->position.y, -this->position.z));

        return  viewMatrix;
    }
}
