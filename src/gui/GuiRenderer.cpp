//
// Created by Martin on 23. 11. 2015.
//

#include "src/gui/GuiRenderer.hpp"

GuiRenderer::GuiRenderer(RawModel *rawModel, GuiShader *shader) {
    this->rawModel = rawModel;
    this->guiShader = shader;
}

void GuiRenderer::render(std::vector<GuiTexture *> guis) {
    this->guiShader->start();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_DEPTH_TEST);
    loadVAO(this->rawModel);

    for (std::vector<GuiTexture *>::iterator guiLoop = guis.begin(); guiLoop != guis.end(); guiLoop++) {
        loadTexture(*guiLoop);
        loadMatrix(Transformations::createTransformationMatrix((*guiLoop)->position, (*guiLoop)->scale));
        glDrawArrays(GL_TRIANGLE_STRIP, 0, this->rawModel->mesh_vertex_count);
    }

    glEnable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);
    unbind();

    this->guiShader->stop();
}

void GuiRenderer::loadVAO(RawModel *model) {
    glBindVertexArray(model->vao);
}

void GuiRenderer::loadMatrix(glm::mat4 matrix) {
    guiShader->loadModelMatrix(matrix);
}

void GuiRenderer::loadTexture(GuiTexture *guiTexture) {
    guiShader->loadTextureUni(guiTexture->textureId);
}

void GuiRenderer::unbind() {
    glBindVertexArray(NULL);
}

void GuiRenderer::clean() {
    this->guiShader->clean();
}
