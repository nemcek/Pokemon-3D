//
// Created by Martin on 16. 11. 2015.
//

#include "src/shaders/ShaderProgram.hpp"

ShaderProgram::ShaderProgram(const std::string &vertex_shader_file, const std::string &fragment_shader_file) {
    this->vertexShaderId = loadShader(vertex_shader_file, GL_VERTEX_SHADER);
    this->fragmentShaderId = loadShader(fragment_shader_file, GL_FRAGMENT_SHADER);

    // Create and link the program
//        this->programId = glCreateProgram();
//        glAttachShader(programId, vertexShaderId);
//        glAttachShader(programId, fragmentShaderId);
//        glBindFragDataLocation(programId, 0, "FragmentColor");
//        bindAttributes();
//        glLinkProgram(programId);

    this->programId = createProgram(vertexShaderId, fragmentShaderId);
}

void ShaderProgram::bindAttributes() {};

void ShaderProgram::start() {
    glUseProgram(programId);
}

void ShaderProgram::stop() {
    glUseProgram(0);
}

void ShaderProgram::clean() {
    stop();
    glDetachShader(programId, vertexShaderId);
    glDetachShader(programId, fragmentShaderId);

    glDeleteShader(vertexShaderId);
    glDeleteShader(fragmentShaderId);

    glDeleteProgram(programId);
}

void ShaderProgram::bindAttribute(int attribute, const std::string &varname) {
    glBindAttribLocation(programId, attribute, varname.c_str());
}

GLint ShaderProgram::getUniformLocation(const std::string uniformName) {
    return glGetUniformLocation(programId, uniformName.c_str());
}

void ShaderProgram::loadFloat(GLint location, float value) {
    glUniform1f(location, value);
}

void ShaderProgram::loadInt(GLint location, int value) {
    glUniform1i(location, value);
}

void ShaderProgram::loadVector(GLint location, glm::vec3 vector) {
    glUniform3f(location, vector.x, vector.y, vector.z);
}

void ShaderProgram::loadMatrix(GLint location, glm::mat4 matrix) {
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void ShaderProgram::loadBoolean(GLint location, bool value) {
    float load;
    if (value)
        load = 1;
    else
        load = 0;

    glUniform1f(location, load);
}

void ShaderProgram::loadTexture(GLint location, GLint texture_id) {
    // Bind the texture to "Texture" uniform in program
    glUniform1i(location, 0);
    glActiveTexture(GL_TEXTURE0 + 0);
    glBindTexture(GL_TEXTURE_2D, texture_id);
}

GLint ShaderProgram::loadShader(const std::string &shader_file, GLint type) {
    // Create shaders
    auto shader_id = glCreateShader(type);
    auto result = GL_FALSE;
    auto info_length = 0;

    // Load shader code
    std::ifstream shader_stream(shader_file);
    std::string shader_code((std::istreambuf_iterator<char>(shader_stream)), std::istreambuf_iterator<char>());

    // Compile shader
    std::cout << "Compiling Shader ..." << shader_file << std::endl;
    auto shader_code_ptr = shader_code.c_str();
    glShaderSource(shader_id, 1, &shader_code_ptr, NULL);
    glCompileShader(shader_id);

    // Check vertex shader log
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &info_length);
        std::string vertex_shader_log((unsigned int)info_length, ' ');
        glGetShaderInfoLog(shader_id, info_length, NULL, &vertex_shader_log[0]);
        std::cout << vertex_shader_log << std::endl;
    }

    return shader_id;
}

GLint ShaderProgram::createProgram(GLint vertex_shader_id, GLint fragment_shader_id) {
    auto result = GL_FALSE;
    auto info_length = 0;

    // Create and link the program
    std::cout << "Linking Shader Program ..." << std::endl;
    auto program_id = glCreateProgram();
    glAttachShader(program_id, vertex_shader_id);
    glAttachShader(program_id, fragment_shader_id);
    glBindFragDataLocation(program_id, 0, "FragmentColor");
    glLinkProgram(program_id);

    // Check program log
    glGetProgramiv(program_id, GL_LINK_STATUS, &result);
    if (result == GL_FALSE) {
        glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &info_length);
        std::string program_log((unsigned long)info_length, ' ');
        glGetProgramInfoLog(program_id, info_length, NULL, &program_log[0]);
        std::cout << program_log << std::endl;
    }

    glDeleteShader(vertex_shader_id);
    glDeleteShader(fragment_shader_id);

    return program_id;
}
