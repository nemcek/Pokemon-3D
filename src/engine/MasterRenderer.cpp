//
// Created by Martin on 17. 11. 2015.
//

#include "src/engine/MasterRenderer.hpp"

MasterRenderer::MasterRenderer(MeshRendererPtr renderer, GroundRendererPtr groundRenderer, GuiRendererPtr guiRenderer,
                                SkyboxRendererPtr skyboxRenderer)
    : staticShader(renderer->shader),
      renderer(renderer),
      groundShader(groundRenderer->shader),
      groundRenderer(groundRenderer),
      guiRenderer(guiRenderer),
      guiShader(guiRenderer->guiShader),
      skyboxRenderer(skyboxRenderer),
      skyboxShader(skyboxRenderer->shader){

    // Enable Z-buffer
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    // Enable polygon culling
//    enableCulling();
    glFrontFace(GL_CCW);
}

void MasterRenderer::render(glm::mat4 projection, glm::mat4 camera, std::vector<LightPtr> lights) {
    prepare();
    this->staticShader->start();
    this->staticShader->loadSkyColor(skyColor);
    this->staticShader->loadLights(lights);
    this->renderer->render(this->meshes, projection, camera);
    this->renderer->render(this->wrappers, projection, camera);
    this->staticShader->stop();

    this->groundShader->start();
    this->groundShader->loadSkyColor(skyColor);
    this->groundShader->loadLights(lights);
    this->groundRenderer->render(this->grounds, projection, camera);
    this->groundShader->stop();

    this->skyboxRenderer->render(this->skybox, camera, projection, fogColor);

    this->guiShader->start();
    this->guiRenderer->render(this->guis);
    this->guiShader->stop();

    this->meshes.clear();
    this->grounds.clear();
    this->wrappers.clear();
    this->guis.clear();
}

void MasterRenderer::prepare() {
    // Set gray background
    glClearColor(skyColor.x, skyColor.y, skyColor.z, 0);
    // Clear depth and color buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void MasterRenderer::clean() {
    this->staticShader->clean();
    this->groundShader->clean();
    this->guiShader->clean();
    this->skyboxShader->clean();
}

void MasterRenderer::processMesh(MeshPtr mesh) {
    this->meshes.push_back(mesh);
}

void MasterRenderer::processGround(GroundPtr ground) {
    this->grounds.push_back(ground);
}

void MasterRenderer::processWrapper(MeshWrapperPtr wrapper) {
    this->wrappers.push_back(wrapper);
}

void MasterRenderer::processGui(GuiPtr gui) {
    this->guis.push_back(gui);
}

void MasterRenderer::processSkybox(SkyboxPtr skybox) {
    this->skybox = skybox;
}

void MasterRenderer::enableCulling() {
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
}

void MasterRenderer::disableCulling() {
    glDisable(GL_CULL_FACE);
}