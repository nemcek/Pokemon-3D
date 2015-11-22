//
// Created by Martin on 19. 11. 2015.
//

#ifndef POKEMON3D_INPUTMANAGER_HPP
#define POKEMON3D_INPUTMANAGER_HPP

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class InputManager {

private:

    int *keys;
    glm::vec3 currentCursorPosition;
    glm::vec3 lastCursorPosition;
    int windowWidth;
    int windowHeight;
    double previousWheelOffset;
    double currentWheerlOffset;

    glm::vec3 toScreenCoord(double x , double y);

public:

    InputManager(int windowWidth, int widowHeight);
    bool isWPressed();
    bool isSPressed();
    bool isAPressed();
    bool isDPressed();
    bool isRightMouseButtonPressed();
    bool isLeftMouseButtonPressed();
    void mouseButtonCallback( GLFWwindow * window, int button, int action, int mods );
    void cursorCallback( GLFWwindow *, double x, double y );
    void wheelCallBack( GLFWwindow *, double, double yoffset );
    void onKeyPress( GLFWwindow *, int key, int scancode, int action, int mods);
    float getDistanceY();
    float getDistanceX();
    double getDistanceZoom();
};

#endif //POKEMON3D_INPUTMANAGER_HPP
