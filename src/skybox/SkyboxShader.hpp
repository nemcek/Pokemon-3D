//
// Created by Martin on 28. 11. 2015.
//

#ifndef POKEMON3D_SKYBOXSHADER_HPP
#define POKEMON3D_SKYBOXSHADER_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "src/shaders/ShaderProgram.hpp"

class SkyboxShader : public ShaderProgram {

private:
    GLint projectionMatrix;
    GLint viewMatrix;
    GLint fogColor;

    glm::vec3 rotationVec = glm::vec3(0.0f, 1.0f, 0.0f);
public:
    SkyboxShader();
    void loadProjectionMatrix(glm::mat4 matrix);
    void loadViewMatrix(glm::mat4 matrix, float rotation);
    void getAllUniformLocations() override;
    void loadFogColor(glm::vec3 color);
    glm::mat4 rotate(glm::mat4 matrix, float rotation);
};

typedef std::shared_ptr<SkyboxShader> SkyboxShaderPtr;

#endif //POKEMON3D_SKYBOXSHADER_HPP
