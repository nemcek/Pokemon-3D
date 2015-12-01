//
// Created by Martin on 19. 11. 2015.
//

#include "src/managers/InputManager.hpp"

InputManager::InputManager(int windowWidth, int windowHeight) {
    this->keys = new int[1024]{0};
    this->windowWidth = windowWidth;
    this->windowHeight = windowHeight;
    this->previousWheelOffset = 0.0f;
    this->currentWheerlOffset = 0.0f;
}

bool InputManager::isWPressed() {
    return keys[GLFW_KEY_W];
}

bool InputManager::isSPressed() {
    return keys[GLFW_KEY_S];
}

bool InputManager::isAPressed() {
    return keys[GLFW_KEY_A];
}

bool InputManager::isDPressed() {
    return keys[GLFW_KEY_D];
}

bool InputManager::isTPressed() {
    return keys[GLFW_KEY_T];
}

void InputManager::wheelCallBack(GLFWwindow *, double, double yoffset) {
    this->currentWheerlOffset -= yoffset;
}

void InputManager::cursorCallback(GLFWwindow *, double x, double y) {
    if (keys[GLFW_MOUSE_BUTTON_LEFT] || keys[GLFW_MOUSE_BUTTON_RIGHT]) {
        this->currentCursorPosition = toScreenCoord(x, y);
    }
}

void InputManager::mouseButtonCallback(GLFWwindow *window, int button, int action, int mods) {
    if ((button == GLFW_MOUSE_BUTTON_LEFT || button == GLFW_MOUSE_BUTTON_RIGHT) && action == GLFW_PRESS) {

        double x, y;
        glfwGetCursorPos(window, &x, &y);
        this->lastCursorPosition = toScreenCoord(x, y);

        if (button == GLFW_MOUSE_BUTTON_LEFT) {
            keys[GLFW_MOUSE_BUTTON_LEFT] = true;
        } else {
            keys[GLFW_MOUSE_BUTTON_RIGHT] = true;
        }
    }
    else {
        keys[GLFW_MOUSE_BUTTON_LEFT] = false;
        keys[GLFW_MOUSE_BUTTON_RIGHT] = false;
    }
}

glm::vec3 InputManager::toScreenCoord( double x, double y ) {
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

void InputManager::onKeyPress(GLFWwindow *window, int key, int , int action, int ) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);

    if (key >= 0 && key < 1024) {
        if (action == GLFW_PRESS)
            keys[key] = true;
        else if (action == GLFW_RELEASE)
            keys[key] = false;
    }
}

bool InputManager::isRightMouseButtonPressed() {
    return this->keys[GLFW_MOUSE_BUTTON_RIGHT];
}

bool InputManager::isLeftMouseButtonPressed() {
    return this->keys[GLFW_MOUSE_BUTTON_LEFT];
}

float InputManager::getDistanceX() {
    return this->lastCursorPosition.x - this->currentCursorPosition.x;
}

float InputManager::getDistanceY() {
    return this->lastCursorPosition.y - this->currentCursorPosition.y;
}

double InputManager::getDistanceZoom() {
    double retVal = this->previousWheelOffset - currentWheerlOffset;
    this->previousWheelOffset = currentWheerlOffset;

    return retVal;
}