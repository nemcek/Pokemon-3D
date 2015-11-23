//
// Created by Martin on 18. 11. 2015.
//

#ifndef POKEMON3D_TRANSFORMATIONS_HPP
#define POKEMON3D_TRANSFORMATIONS_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Transformations {

public:
    static glm::mat4 createTransformationMatrix(glm::vec3 position, float rotX, float rotY, float rotZ, float scale);
    static glm::mat4 createTransformationMatrix(glm::vec2 position, glm::vec2 scale);
    static float getScaleFactor(glm::mat4 matrix);
    static glm::vec3 getPosition(glm::mat4 matrix);
};

#endif //POKEMON3D_TRANSFORMATIONS_HPP
