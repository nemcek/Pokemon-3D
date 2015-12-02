//
// Created by Martin on 22. 11. 2015.
//

#include "src/objects/Scene.hpp"

Scene::Scene() {

}

Scene::Scene(MasterRendererPtr masterRenderer, std::vector<LightPtr> lights,
             glm::mat4 projection, CameraPtr camera) {
    this->masterRenderer = masterRenderer;
    this->lights = lights;
    this->projection = projection;
    this->camera = camera;
}

void Scene::loadObject(MeshPtr mesh) {
    this->objects.push_back(mesh);
}

void Scene::loadGround(GroundPtr ground) {
    this->grounds.push_back(ground);
}

void Scene::animate(float delta) {
    for (auto objectLoop : this->objects) {
        objectLoop->animate(this, delta);
    }

    this->skybox->animate(delta);

    camera->move();
}

void Scene::update() {
    return;
}

void Scene::render() {

    for (auto meshLoop : this->objects) {
        masterRenderer->processMesh(meshLoop);
    }

    for (auto groundLoop : this->grounds) {
        masterRenderer->processGround(groundLoop);
    }

    for (auto wrapperLoop : this->wrappers) {
        masterRenderer->processWrapper(wrapperLoop);
    }

    for (auto guiLoop : this->guis) {
        masterRenderer->processGui(guiLoop);
    }

    masterRenderer->render(this->projection, this->camera->getViewMatrix(), this->lights);
}

void Scene::clean() {
    this->masterRenderer->clean();
}

void Scene::loadWrapper(MeshWrapperPtr wrapper) {
    this->wrappers.push_back(wrapper);
    this->masterRenderer->processWrapper(wrapper);
}

void Scene::loadGui(GuiPtr gui) {
    this->guis.push_back(gui);
    this->masterRenderer->processGui(gui);
}

void Scene::loadSkybox(SkyboxPtr skybox) {
    this->skybox = skybox;
    this->masterRenderer->processSkybox(skybox);
}

void Scene::loadMasterRenderer(MasterRendererPtr masterRenderer) {
    this->masterRenderer = masterRenderer;
}

void Scene::loadLights(std::vector<LightPtr> lights) {
    this->lights = lights;
}

void Scene::loadLight(LightPtr light) {
    this->lights.push_back(light);
}

void Scene::loadCamera(CameraPtr camera) {
    this->camera = camera;
}

void Scene::loadProjection(glm::mat4 projection) {
    this->projection = projection;
}

void Scene::loadGrounds(std::vector<GroundPtr> grounds) {
    for (auto groundLoop : grounds) {
        loadGround(groundLoop);
    }
}