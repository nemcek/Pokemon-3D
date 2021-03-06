//
// Created by Martin on 22. 11. 2015.
//

#ifndef POKEMON3D_RAWMODEL_HPP
#define POKEMON3D_RAWMODEL_HPP

#include <memory>

#include <GL/glew.h>

class RawModel {

public:
    GLuint vbo, tbo;
    GLuint ibo;
    GLuint vao;
    GLuint nbo;
    int mesh_indices_count;
    int mesh_vertex_count;

    RawModel();

};

typedef std::shared_ptr<RawModel> RawModelPtr;

#endif //POKEMON3D_RAWMODEL_HPP
