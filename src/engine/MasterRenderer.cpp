//
// Created by Martin on 17. 11. 2015.
//

#include "src/engine/MasterRenderer.hpp"

namespace nsMaterRenderer {

    MasterRenderer::MasterRenderer(nsMeshRenderer::MeshRenderer *renderer, GroundRenderer *groundRenderer)
        : staticShader(renderer->shader),
          renderer(renderer),
          groundShader(groundRenderer->shader),
          groundRenderer(groundRenderer){

        // Enable Z-buffer
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);

        // Enable polygon culling
        //glEnable(GL_CULL_FACE);
        glFrontFace(GL_CCW);
        glCullFace(GL_BACK);
    }

    void MasterRenderer::render(glm::mat4 projection, glm::mat4 camera, Light *light) {
        prepare();
        this->staticShader->start();
        this->staticShader->loadSkyColor(skyColor);
        this->staticShader->loadLight(light);
        this->renderer->render(this->meshes, projection, camera);
        this->renderer->render(this->wrappers, projection, camera);
        this->staticShader->stop();

        this->groundShader->start();
        this->groundShader->loadSkyColor(skyColor);
        this->groundShader->loadLight(light);
        this->groundRenderer->render(this->grounds, projection, camera);
        this->groundShader->stop();

        this->meshes.clear();
        this->grounds.clear();
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
    }

    void MasterRenderer::processMesh(Mesh *mesh) {
        this->meshes.push_back(*mesh);
    }

    void MasterRenderer::processGround(nsGround::Ground *ground) {
        this->grounds.push_back(*ground);
    }

    void MasterRenderer::processWrapper(MeshWrapper *wrapper) {
        this->wrappers.push_back(*wrapper);
    }

}
