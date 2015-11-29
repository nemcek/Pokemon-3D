//
// Created by Martin on 22. 11. 2015.
//

#include "src/objects/Scene.hpp"

Scene::Scene() {

}

Scene::Scene(nsMaterRenderer::MasterRenderer *masterRenderer, std::vector<Light *> lights,
             glm::mat4 projection, Camera *camera) {
    this->masterRenderer = masterRenderer;
    this->lights = lights;
    this->projection = projection;
    this->camera = camera;
}

void Scene::loadObject(Mesh *mesh) {
    this->objects.push_back(mesh);
}

void Scene::loadObject(MeshPtr meshPtr) {
    this->objects2.push_back(meshPtr);
}

void Scene::loadGround(nsGround::Ground *ground) {
    this->grounds.push_back(ground);
}

void Scene::animate(float delta) {
    for (auto objectLoop : this->objects) {
        objectLoop->animate(this, delta);
    }

    this->skybox->animate(delta);

    camera->move();
}

void Scene::render() {

    for (auto meshLoop : this->objects) {
        masterRenderer->processMesh(meshLoop);
    }

    for (auto groundLoop : this->grounds) {
        masterRenderer->processGround(groundLoop);
    }

    for (auto mestPtrLoop : this->objects2) {
        masterRenderer->processMesh(mestPtrLoop.get());
    }

    masterRenderer->render(this->projection, this->camera->getViewMatrix(), this->lights);
}

void Scene::clean() {
    this->masterRenderer->clean();
}

void Scene::loadWrapper(MeshWrapper *wrapper) {
    this->wrappers.push_back(wrapper);
    this->masterRenderer->processWrapper(wrapper);
}

void Scene::loadGui(Gui *gui) {
    this->guis.push_back(gui);
    this->masterRenderer->processGui(gui);
}

void Scene::loadSkybox(Skybox *skybox) {
    this->skybox = skybox;
    this->masterRenderer->processSkybox(skybox);
}

void Scene::loadMasterRenderer(nsMaterRenderer::MasterRenderer *masterRenderer) {
    this->masterRenderer = masterRenderer;
}

void Scene::loadLights(std::vector<Light *> lights) {
    this->lights = lights;
}

void Scene::loadLight(Light *light) {
    this->lights.push_back(light);
}

void Scene::loadCamera(Camera *camera) {
    this->camera = camera;
}

void Scene::loadProjection(glm::mat4 projection) {
    this->projection = projection;
}