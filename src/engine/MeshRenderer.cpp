//
// Created by Martin on 16. 11. 2015.
//

#include "src/engine/MeshRenderer.hpp"

namespace nsMeshRenderer {

    MeshRenderer::MeshRenderer(StaticShader *shader) {
        this->shader = shader;
    };

    void MeshRenderer::render(std::vector<Mesh> meshes, glm::mat4 projection, glm::mat4 view) {
        for ( std::vector<Mesh>::iterator it = meshes.begin(); it != meshes.end(); it++ ) {
            render(&(*it), projection, view);
        }
    }

    void MeshRenderer::render(Mesh *mesh, glm::mat4 projection, glm::mat4 view) {
        loadTexturedModel(mesh->texturedModel, projection, view);

        loadVAO(mesh->texturedModel);
        loadMatrixAndDraw(mesh->createTransformationMatrix(), mesh->texturedModel->rawModel->mesh_indices_count);

        unbindMesh();
    }

    void MeshRenderer::render(std::vector<MeshWrapper *> wrappers, glm::mat4 projection, glm::mat4 view) {
        for (std::vector<MeshWrapper *>::iterator it = wrappers.begin(); it != wrappers.end(); it++) {
            this->render(*it, projection, view);
        }
    }

    void MeshRenderer::render(MeshWrapper *wrapper, glm::mat4 projection, glm::mat4 view) {
        loadTexturedModel(wrapper->mesh->texturedModel, projection, view);
        loadVAO(wrapper->mesh->texturedModel);

        for (std::vector<glm::mat4>::iterator it = wrapper->matrixes.begin(); it != wrapper->matrixes.end(); it++) {
            loadMatrixAndDraw(*it, wrapper->mesh->texturedModel->rawModel->mesh_indices_count);
        }

        unbindMesh();
    }

    void MeshRenderer::loadTexturedModel(const TexturedModel *model, glm::mat4 projection, glm::mat4 view) {
        shader->loadProjectionMatrix(projection);
        shader->loadViewMatrix(view);

        shader->loadTextureUni(model->texture->textureId);
        shader->loadShining(model->texture->reflectivity, model->texture->shineDamper);
    }

    void MeshRenderer::unbindMesh() {
        glBindVertexArray(0);
    }

    void MeshRenderer::loadMatrixAndDraw(glm::mat4 matrix, int count) {
        shader->loadModelMatrix(matrix);
        glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, 0);
    }

    void MeshRenderer::loadVAO(TexturedModel *model) {
        glBindVertexArray(model->rawModel->vao);
    }
}