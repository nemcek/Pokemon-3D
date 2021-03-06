//
// Created by Martin on 23. 11. 2015.
//

#include "src/gui/GuiRenderer.hpp"

GuiRenderer::GuiRenderer(GuiShaderPtr shader, LoaderPtr loader) {
    std::vector<GLfloat> vertex_buffer = {-1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f, -1.0f};
    std::vector<GLfloat> texcoord_buffer = { 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f};
    auto guiRawModel = loader->load(vertex_buffer, texcoord_buffer, 2);

    this->rawModel = guiRawModel;
    this->guiShader = shader;
}

void GuiRenderer::render(std::vector<GuiTexturePtr> guis) {
    this->guiShader->start();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_DEPTH_TEST);
    loadVAO(this->rawModel);

    for (std::vector<GuiTexturePtr>::iterator guiLoop = guis.begin(); guiLoop != guis.end(); guiLoop++) {
        loadTexture(*guiLoop);
        loadMatrix(Transformations::createTransformationMatrix((*guiLoop)->position, (*guiLoop)->scale));
        glDrawArrays(GL_TRIANGLE_STRIP, 0, this->rawModel->mesh_vertex_count);
    }

    glEnable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);
    unbind();

    this->guiShader->stop();
}

void GuiRenderer::render(std::vector<GuiPtr> guis) {

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_DEPTH_TEST);
    loadVAO(this->rawModel);

    for (auto guiLoop : guis) {
        render(guiLoop);
    }

    glEnable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);
    unbind();
}

void GuiRenderer::render(GuiPtr gui) {
    for (auto guiTextureLoop : gui->guiTextures) {
        loadTexture(guiTextureLoop);
        loadMatrix(Transformations::createTransformationMatrix((guiTextureLoop)->position, (guiTextureLoop)->scale));
        glDrawArrays(GL_TRIANGLE_STRIP, 0, this->rawModel->mesh_vertex_count);
    }
}

void GuiRenderer::loadVAO(RawModelPtr model) {
    glBindVertexArray(model->vao);
}

void GuiRenderer::loadMatrix(glm::mat4 matrix) {
    guiShader->loadModelMatrix(matrix);
}

void GuiRenderer::loadTexture(GuiTexturePtr guiTexture) {
    guiShader->loadTextureUni(guiTexture->textureId);
}

void GuiRenderer::unbind() {
    glBindVertexArray(0);
}

void GuiRenderer::clean() {
    this->guiShader->clean();
}
