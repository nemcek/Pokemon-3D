//
// Created by Martin on 22. 11. 2015.
//

#ifndef POKEMON3D_LOADER_HPP
#define POKEMON3D_LOADER_HPP

#include <memory>

#include <vector>
#include <stdio.h>
#include <GL/glew.h>
#include "src/models/RawModel.hpp"
#include "src/loaders/FileLoader.h"

class Loader {

private:

    GLuint programId;

    void setVertexPositions(RawModelPtr rawModel, std::vector<GLfloat> vertex_buffer);
    void setVertexPositions(RawModelPtr rawModel, std::vector<GLfloat> vertex_buffer, int size);
    void setTextureCoords(RawModelPtr rawModel, std::vector<GLfloat> texcoord_buffer, int size);
    void setIndices(RawModelPtr rawModel, std::vector<GLuint> index_data);
    void setNormals(RawModelPtr rawModel, std::vector<GLfloat> normals_data);
    RawModelPtr initLoading();
    void clean();

public:
    Loader(GLuint programId);
    RawModelPtr load(std::vector<GLfloat> vertex_buffer, std::vector<GLfloat> texcoord_buffer, std::vector<GLuint> index_data,
                  std::vector<GLfloat> normals_data);
    RawModelPtr load(std::vector<GLfloat> vertex_buffer, std::vector<GLfloat> texcoord_buffer, int size);
    GLuint loadTexture(const std::string &image_file);
    GLuint loadCubeMap(std::vector<std::string> files);
};

typedef std::shared_ptr<Loader> LoaderPtr;

#endif //POKEMON3D_LOADER_HPP
