//
// Created by Martin on 18. 11. 2015.
//

#include "src/wrappers/MeshWrapper.hpp"

MeshWrapper::MeshWrapper(LoaderPtr loader, const std::string &obj_file, const std::string &image_file, int count, glm::vec3 scale) {
    this->mesh = MeshPtr(new Mesh(loader, obj_file, image_file));

    createMatrixes(count, scale);
}

MeshWrapper::MeshWrapper(LoaderPtr loader, const std::string &obj_file, const std::string &image_file, int count, glm::vec3 scale,
                         float reflectivity, float shineDamper) {
    this->mesh = MeshPtr(new Mesh(loader, obj_file, image_file));
    this->mesh->texturedModel->texture->reflectivity = reflectivity;
    this->mesh->texturedModel->texture->shineDamper = shineDamper;

    createMatrixes(count, scale);
}

void MeshWrapper::createMatrixes(int count, glm::vec3 scale) {
    for (int i = 0; i < count; i++) {
        float scaling = (float)(rand() % (int)scale.x + scale.y) / (float)scale.z;
        glm::mat4 matrix = Transformations::createTransformationMatrix(
                glm::vec3((float)(rand() % 1000 - 500), 0.0f, (float)(rand() % 1000 - 500)),
                0.0f, (float)(rand() % 360), 0.0f,
                scaling
        );

        this->matrixes.push_back(matrix);
    }
}
