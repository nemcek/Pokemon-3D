//
// Created by Martin on 16. 11. 2015.
//

#ifndef POKEMON3D_SHADERPROGRAM_H
#define POKEMON3D_SHADERPROGRAM_H

#include <memory>

#include <vector>
#include <iostream>
#include <fstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class ShaderProgram {
private:
    GLint vertexShaderId;
    GLint fragmentShaderId;

    GLint loadShader(const std::string &shader_file, GLint type);
    GLint createProgram(GLint vertex_shader_id, GLint fragment_shader_id);

protected:
    virtual void bindAttributes();
    void bindAttribute(int attribute, const std::string &varname);
    GLint getUniformLocation(const std::string uniformName);
    virtual void getAllUniformLocations() = 0;
    void loadFloat(GLint location, float value);
    void loadVector(GLint location, glm::vec3 vector);
    void loadBoolean(GLint location, bool value);
    void loadMatrix(GLint location, glm::mat4 matrix);
    void loadTexture(GLint location, GLint texture_id);
    void loadInt(GLint location, int value);

public:
    GLint programId;

    ShaderProgram(const std::string &vertex_shader_file, const std::string &fragment_shader_file);
    void start();
    void stop();
    void clean();
};

typedef std::shared_ptr<ShaderProgram> ShaderProgramPtr;

#endif //POKEMON3D_SHADERPROGRAM_H
