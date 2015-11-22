//
// Created by Martin on 22. 11. 2015.
//

#ifndef POKEMON3D_LOADER_HPP
#define POKEMON3D_LOADER_HPP

#include <vector>
#include <stdio.h>
#include <GL/glew.h>
#include "src/models/RawModel.hpp"

class Loader {

private:

    GLuint programId;

    void setVertexPositions(RawModel *rawModel, std::vector<GLfloat> vertex_buffer);
    void setTextureCoords(RawModel *rawModel, std::vector<GLfloat> texcoord_buffer);
    void setIndices(RawModel *rawModel, std::vector<GLuint> index_data);
    void setNormals(RawModel *rawModel, std::vector<GLfloat> normals_data);

public:
    Loader(GLuint programId);
    RawModel* load(std::vector<GLfloat> vertex_buffer, std::vector<GLfloat> texcoord_buffer, std::vector<GLuint> index_data,
                  std::vector<GLfloat> normals_data);
};

#endif //POKEMON3D_LOADER_HPP