//
// Created by Martin on 18. 11. 2015.
//

#include "src/extensions/Transformations.hpp"

glm::mat4 Transformations::createTransformationMatrix(glm::vec3 position, float rotX, float rotY, float rotZ,
                                                      float scale) {
    glm::mat4 matrix;

    matrix = glm::translate(matrix, position);
    matrix = glm::rotate(matrix, glm::radians(rotX), glm::vec3(1.0f, 0.0f, 0.0f));
    matrix = glm::rotate(matrix, glm::radians(rotY), glm::vec3(0.0f, 1.0f, 0.0f));
    matrix = glm::rotate(matrix, glm::radians(rotZ), glm::vec3(0.0f, 0.0f, 1.0f));

    matrix = glm::scale(matrix, glm::vec3(scale));

    return matrix;
}
