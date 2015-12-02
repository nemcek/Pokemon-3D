//
// Created by Martin on 23. 11. 2015.
//

#ifndef POKEMON3D_GUISHADER_HPP
#define POKEMON3D_GUISHADER_HPP

#include <glm/glm.hpp>

#include "src/shaders/ShaderProgram.hpp"

class GuiShader : public ShaderProgram {

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

typedef std::shared_ptr<GuiShader> GuiShaderPtr;

#endif //POKEMON3D_GUISHADER_HPP
