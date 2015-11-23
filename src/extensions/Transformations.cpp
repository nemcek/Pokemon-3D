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

glm::mat4 Transformations::createTransformationMatrix(glm::vec2 position, glm::vec2 scale) {
    glm::mat4 matrix;

    matrix = glm::translate(matrix, glm::vec3(position, 0.0f));
    matrix = glm::scale(matrix, glm::vec3(scale.x, scale.y, 0.0f));

    return matrix;
}

float Transformations::getScaleFactor(glm::mat4 matrix) {
    return glm::sqrt(matrix[0].x * matrix[0].x + matrix[1].x * matrix[1].x + matrix[2].x * matrix[2].x);
}

glm::vec3 Transformations::getPosition(glm::mat4 matrix) {
    return glm::vec3(matrix[3].x, matrix[3].y, matrix[3].z);
}
