//
// Created by Martin on 16. 11. 2015.
//

#include "src/engine/MeshRenderer.hpp"
#include "MasterRenderer.hpp"


MeshRenderer::MeshRenderer(StaticShaderPtr shader) {
    this->shader = shader;
};

void MeshRenderer::render(std::vector<MeshPtr> meshes, glm::mat4 projection, glm::mat4 view) {
    for ( std::vector<MeshPtr>::iterator it = meshes.begin(); it != meshes.end(); it++ ) {
        render(*it, projection, view);
    }
}

void MeshRenderer::render(MeshPtr mesh, glm::mat4 projection, glm::mat4 view) {
    if (mesh->texturedModel->texture->hasTransparency)
        MasterRenderer::disableCulling();

    shader->loadUseFakeLighting(mesh->texturedModel->texture->useFakeLighting);

    loadTexturedModel(mesh->texturedModel, projection, view);

    loadVAO(mesh->texturedModel);
    loadMatrixAndDraw(mesh->createTransformationMatrix(), mesh->texturedModel->rawModel->mesh_indices_count);

    unbindMesh();
}

void MeshRenderer::render(std::vector<MeshWrapperPtr> wrappers, glm::mat4 projection, glm::mat4 view) {
    for (std::vector<MeshWrapperPtr>::iterator it = wrappers.begin(); it != wrappers.end(); it++) {
        this->render(*it, projection, view);
    }
}

void MeshRenderer::render(MeshWrapperPtr wrapper, glm::mat4 projection, glm::mat4 view) {
    if (wrapper->mesh->texturedModel->texture->hasTransparency)
        MasterRenderer::disableCulling();

    shader->loadUseFakeLighting(wrapper->mesh->texturedModel->texture->useFakeLighting);

    loadTexturedModel(wrapper->mesh->texturedModel, projection, view);
    loadVAO(wrapper->mesh->texturedModel);

    for (std::vector<glm::mat4>::iterator it = wrapper->matrixes.begin(); it != wrapper->matrixes.end(); it++) {
        loadMatrixAndDraw(*it, wrapper->mesh->texturedModel->rawModel->mesh_indices_count);
    }

    unbindMesh();
}

void MeshRenderer::loadTexturedModel(TexturedModelPtr model, glm::mat4 projection, glm::mat4 view) {
    shader->loadProjectionMatrix(projection);
    shader->loadViewMatrix(view);

    shader->loadTextureUni(model->texture->textureId);
    shader->loadShining(model->texture->reflectivity, model->texture->shineDamper);
}

void MeshRenderer::unbindMesh() {
//    MasterRenderer::enableCulling();
    glBindVertexArray(0);
}

void MeshRenderer::loadMatrixAndDraw(glm::mat4 matrix, int count) {
    shader->loadModelMatrix(matrix);
    glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, 0);
}

void MeshRenderer::loadVAO(TexturedModelPtr model) {
    glBindVertexArray(model->rawModel->vao);
}
