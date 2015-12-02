//
// Created by Martin on 28. 11. 2015.
//

#include "src/skybox/SkyboxRenderer.hpp"

SkyboxRenderer::SkyboxRenderer(SkyboxShaderPtr shader) {
    this->shader = shader;
}

void SkyboxRenderer::render(SkyboxPtr skybox, glm::mat4 viewMatrix, glm::mat4 projectionMatrix, glm::vec3 fogColor) {

    shader->start();
    shader->loadProjectionMatrix(projectionMatrix);

    shader->loadViewMatrix(viewMatrix, skybox->rotation);
    shader->loadFogColor(fogColor);
    glBindVertexArray(skybox->cube->vao);

    glActiveTexture(GL_TEXTURE0 + 0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, skybox->textureId);
    glDrawArrays(GL_TRIANGLES, 0, skybox->cube->mesh_vertex_count);

    glBindVertexArray(0);

    shader->stop();
}