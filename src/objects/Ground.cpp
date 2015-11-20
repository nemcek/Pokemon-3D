//
// Created by Martin on 17. 11. 2015.
//

#include "src/objects/Ground.hpp"

namespace nsGround {

    Ground::Ground(GLint program_id, int gridX, int gridZ, const std::string &image_file, TerrainTexturePack *texturePack,
                    TerrainTexture *blendMap) {
        this->mesh = new Mesh(program_id, image_file);

        this->x = gridX * size;
        this->z = gridZ * size;
        this->texturePack = texturePack;
        this->blendMap = blendMap;

        this->generateGround();
    }

    void Ground::generateGround() {
        int count = vertex_count * vertex_count;

        std::vector<GLfloat> vertices(count * 3);
        std::vector<GLfloat> normals(count * 3);
        std::vector<GLfloat> textureCoords(count * 2);
        std::vector<GLuint> indices(6 * ((int)vertex_count - 1) * ((int)vertex_count - 1));

        int vertexPointer = 0;

        for (int i = 0; i < vertex_count; i++) {
            for (int j = 0; j < vertex_count; j++) {
                vertices[vertexPointer * 3] = -(float)j/((float)vertex_count - 1) * size;
                vertices[vertexPointer * 3 + 1] = 0;
                vertices[vertexPointer * 3 + 2] = -(float)i/((float)vertex_count - 1) * size;
                normals[vertexPointer * 3] = 0;
                normals[vertexPointer * 3 + 1] = 1;
                normals[vertexPointer * 3 + 2] = 0;
                textureCoords[vertexPointer * 2] = (float)j/((float)vertex_count - 1);
                textureCoords[vertexPointer * 2 + 1] = (float)i/((float)vertex_count - 1);
                vertexPointer++;
            }
        }

        int pointer = 0;
        for (int gz = 0; gz < vertex_count - 1; gz++) {
            for (int gx = 0; gx < vertex_count - 1; gx++) {
                int topLeft = (gz * vertex_count) + gx;
                int topRight = (topLeft + 1);
                int bottomLeft = ((gz + 1) * vertex_count) + gx;
                int bottomRight = (bottomLeft + 1);
                indices[pointer++] = topLeft;
                indices[pointer++] = bottomLeft;
                indices[pointer++] = topRight;
                indices[pointer++] = topRight;
                indices[pointer++] = bottomLeft;
                indices[pointer++] = bottomRight;
            }

        }

        // Activate the program
        glUseProgram(this->mesh->program_id);

        // Generate a vertex array object
        glGenVertexArrays(1, &this->mesh->texturedModel->vao);
        glBindVertexArray(this->mesh->texturedModel->vao);

        // Generate and upload a buffer with vertex positions to GPU
        glGenBuffers(1, &this->mesh->texturedModel->vbo);
        glBindBuffer(GL_ARRAY_BUFFER, this->mesh->texturedModel->vbo);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);

        // Bind the buffer to "Position" attribute in program
        GLint position_attrib = glGetAttribLocation(this->mesh->program_id, "Position");
        glEnableVertexAttribArray(position_attrib);
        glVertexAttribPointer(position_attrib, 3, GL_FLOAT, GL_FALSE, 0, 0);

        // Generate and upload a buffer with texture coordinates to GPU
        glGenBuffers(1, &this->mesh->texturedModel->tbo);
        glBindBuffer(GL_ARRAY_BUFFER, this->mesh->texturedModel->tbo);
        glBufferData(GL_ARRAY_BUFFER, textureCoords.size() * sizeof(GLfloat), textureCoords.data(), GL_STATIC_DRAW);

        GLint texcoord_attrib = glGetAttribLocation(this->mesh->program_id, "TexCoord");
        glEnableVertexAttribArray(texcoord_attrib);
        glVertexAttribPointer(texcoord_attrib, 2, GL_FLOAT, GL_FALSE, 0, 0);

        // --- Indices (define which triangles consists of which vertices) ---
        std::vector<GLuint> index_data;
        this->mesh->texturedModel->mesh_indices_count = 6 * ((int)vertex_count - 1) * ((int)vertex_count - 1);

        // Generate and upload a buffer with indices to GPU
        glGenBuffers(1, &this->mesh->texturedModel->ibo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->mesh->texturedModel->ibo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

        glGenBuffers(1, &this->mesh->texturedModel->nbo);
        glBindBuffer(GL_ARRAY_BUFFER, this->mesh->texturedModel->nbo);
        glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(GLfloat), normals.data(), GL_STATIC_DRAW );

        GLint normal_attrib = glGetAttribLocation(this->mesh->program_id, "Normal");
        glEnableVertexAttribArray(normal_attrib);
        glVertexAttribPointer(normal_attrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
    }
}