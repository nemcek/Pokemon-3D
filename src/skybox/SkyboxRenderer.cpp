//
// Created by Martin on 28. 11. 2015.
//

#include "src/skybox/SkyboxRenderer.hpp"

SkyboxRenderer::SkyboxRenderer(Loader *loader, SkyboxShader *shader) {
    this->shader = shader;
    this->cube = loader->load(this->vertices, this->vertices, 3);
    this->textureId = loader->loadCubeMap(this->file_paths);
}

void SkyboxRenderer::render(glm::mat4 viewMatrix, glm::mat4 projectionMatrix, glm::vec3 fogColor) {

    shader->start();
    shader->loadProjectionMatrix(projectionMatrix);

    shader->loadViewMatrix(viewMatrix);
    shader->loadFogColor(fogColor);
    glBindVertexArray(this->cube->vao);

    glActiveTexture(GL_TEXTURE0 + 0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, this->textureId);
    glDrawArrays(GL_TRIANGLES, 0, this->cube->mesh_vertex_count);

    glBindVertexArray(0);

    shader->stop();
}