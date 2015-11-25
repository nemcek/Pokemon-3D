//
// Created by Martin on 16. 11. 2015.
//

#ifndef POKEMON3D_STATICSHADER_H
#define POKEMON3D_STATICSHADER_H

#include "src/shaders/ShaderProgram.hpp"
#include "src/objects/Light.hpp"

class StaticShader : public nsShaderProgram::ShaderProgram {

private:

    const int number_of_lights = 4;

    GLint modelMatrix;
    GLint texture;
    GLint projection;
    GLint view;
    GLint *lightPosition;
    GLint *lightColor;
    GLint reflectivity;
    GLint shineDamper;
    GLint skyColor;

public:
    StaticShader();
    void bindAttributes() override;
    void getAllUniformLocations() override;
    void loadModelMatrix(glm::mat4 matrix);
    void loadTextureUni(GLint texture_id);
    void loadProjectionMatrix(glm::mat4 projection);
    void loadViewMatrix(glm::mat4 view);
    void loadLights(std::vector<Light *> lights);
    void loadShining(float reflectivity, float shineDamper);
    void loadSkyColor(glm::vec3 skyColor);
};

#endif //POKEMON3D_STATICSHADER_H
