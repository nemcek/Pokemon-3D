//
// Created by Martin on 23. 11. 2015.
//

#ifndef POKEMON3D_GUISHADER_HPP
#define POKEMON3D_GUISHADER_HPP

#include <glm/glm.hpp>

#include "src/shaders/ShaderProgram.hpp"

class GuiShader : public nsShaderProgram::ShaderProgram {

private:
    GLint matrix;
    GLint texture;

public:
    GuiShader();
    void loadModelMatrix(glm::mat4 matix);
    void getAllUniformLocations() override;
    void bindAttributes() override;
    void loadTextureUni(GLint texture_id);
};

#endif //POKEMON3D_GUISHADER_HPP
