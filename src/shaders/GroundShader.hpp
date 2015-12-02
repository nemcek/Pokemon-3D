//
// Created by Martin on 17. 11. 2015.
//

#ifndef POKEMON3D_GROUNDSHADER_H
#define POKEMON3D_GROUNDSHADER_H

#include "src/shaders/ShaderProgram.hpp"
#include "src/objects/Light.hpp"

class GroundShader : public ShaderProgram {

private:

    const int number_of_lights = 4;

    GLint modelMatrix;
    GLint texture;
    GLint projection;
    GLint view;
    GLint *lightPosition;
    GLint *lightColor;
    GLint *attenuation;
    GLint skyColor;
    GLint reflectivity;
    GLint shineDamper;

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
    void loadLights(std::vector<LightPtr> lights);
    void loadSkyColor(glm::vec3 skyColor);
    void connectTextureUnits();
    void loadShining(float reflectivity, float shineDamper);

};

typedef std::shared_ptr<GroundShader> GroundShaderPtr;

#endif //POKEMON3D_GROUNDSHADER_H