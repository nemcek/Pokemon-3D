//
// Created by Martin on 29. 11. 2015.
//

#include "src/skybox/Skybox.hpp"

Skybox::Skybox(Loader *loader) {
    this->cube = loader->load(this->vertices, this->vertices, 3);
    this->textureId = loader->loadCubeMap(this->file_paths);
}

void Skybox::animate(float delta) {
    this->rotation += rotationSpeed * delta;
}
