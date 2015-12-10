//
// Created by Martin on 8. 12. 2015.
//

#include "src/wrappers/GrassWrapper.hpp"

GrassWrapper::GrassWrapper(LoaderPtr loader, const std::string &object_name, const std::string &file_name, glm::vec3 position,
             float rotX, float rotY, float rotZ, float scale) {
    this->loader = loader;
    this->mainGrass = GrassPtr(new Grass(loader, object_name, file_name, position, rotX, rotY, rotZ, scale));
    initGrassAnimation();
}

GrassWrapper::GrassWrapper(LoaderPtr loader, const std::string &object_name, const std::string &file_name, glm::vec3 position,
             float rotX, float rotY, float rotZ, float scale, float reflectivity, float shineDamper) {
    this->loader = loader;
    this->mainGrass = GrassPtr(new Grass(loader, object_name, file_name, position, rotX, rotY, rotZ, scale, reflectivity, shineDamper));
    initGrassAnimation();
}

void GrassWrapper::generateGrass(glm::vec2 bottomLeft, glm::vec2 topRight) {

    for (int z = bottomLeft.y; z <= topRight.y; z++) {
        for (int x = bottomLeft.x; x < topRight.x; x++) {
            float rotation = Math::random(0.0f, 359.9f);
            float size = Math::random(0.5f, 1.5f);

            GrassPtr grass = GrassPtr(new Grass(loader, "models/objects/Grass.obj", "models/textures/Grass.tga", glm::vec3(GLfloat(x), 0.0f, GLfloat(z)), 0.0f,
                                       rotation, 0.0f, size, this->mainGrass->texturedModel->texture->reflectivity,
                                        this->mainGrass->texturedModel->texture->shineDamper));

            grass->texturedModel->texture->hasTransparency = true;
            grass->texturedModel->texture->useFakeLighting = true;
            grass->animation = this->grassAnimation;
            grass->useAnimation = false;

            this->grassParts.push_back(grass);
        }
    }

}

void GrassWrapper::initGrassAnimation() {
    grassAnimation = AnimationPtr(new Animation());

    grassAnimation->add(KeyframePtr(new Keyframe(0, glm::vec3(0.0f))));
    grassAnimation->add(KeyframePtr(new Keyframe(1, glm::vec3(90.0f, 0.0f, 0.0f))));
    grassAnimation->add(KeyframePtr(new Keyframe(2, glm::vec3(0.0f))));

    grassAnimation->repeat = false;
}