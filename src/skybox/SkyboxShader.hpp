//
// Created by Martin on 28. 11. 2015.
//

#ifndef POKEMON3D_SKYBOXSHADER_HPP
#define POKEMON3D_SKYBOXSHADER_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "src/shaders/ShaderProgram.hpp"

class SkyboxShader : public nsShaderProgram::ShaderProgram {

private:
    const float rotationSpeed = 0.3f;

    float rotation = 0.0f;
    float *delta;

    GLint projectionMatrix;
    GLint viewMatrix;
    GLint fogColor;

public:
    GLint cube;

    SkyboxShader(float *delta);
    void loadProjectionMatrix(glm::mat4 matrix);
    void loadViewMatrix(glm::mat4 matrix);
    void getAllUniformLocations() override;
    void loadFogColor(glm::vec3 color);

};

#endif //POKEMON3D_SKYBOXSHADER_HPP
