//
// Created by Martin on 17. 11. 2015.
//

#ifndef POKEMON3D_TEXTUREDMODEL_H
#define POKEMON3D_TEXTUREDMODEL_H

#include "src/objects/Mesh.h"
#include "src/textures/Texture.hpp"


    class TexturedModel {

    private:


    public:
        GLuint vbo, tbo;
        GLuint ibo;
        GLuint vao;
        GLuint nbo;
        int mesh_indices_count;
        glm::mat4 matrix;
        tinyobj::mesh_t *mesh_t;

        nsTexture::Texture *texture;

        TexturedModel();

        bool operator<( const TexturedModel& r ) const;
    };


#endif //POKEMON3D_TEXTUREDMODEL_H
