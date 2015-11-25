//
// Created by Martin on 17. 11. 2015.
//

#ifndef POKEMON3D_GROUNDSHADER_H
#define POKEMON3D_GROUNDSHADER_H

#include "src/shaders/ShaderProgram.hpp"
#include "src/objects/Light.hpp"

class GroundShader : public nsShaderProgram::ShaderProgram {

private:

    GLint modelMatrix;
    GLint texture;
    GLint projection;
    GLint view;
    GLint lightPosition;
    GLint lightColor;
    GLint skyColor;


public:
    GLint backgroundTexture;
    GLint rTexture;
    GLint gTexture;
    GLint bTexture;
    GLint blendMap;

    GroundShader();

    void bindAttributes() override;
    void getAllUniformLocations() override;
    void loadModelMatrix(glm::mat4 matrix);
    void loadTextureUni(GLint texture_id);
    void loadProjectionMatrix(glm::mat4 projection);
    void loadViewMatrix(glm::mat4 view);
    void loadLight(Light *light);
    void loadSkyColor(glm::vec3 skyColor);
    void connectTextureUnits();

};
#endif //POKEMON3D_GROUNDSHADER_H