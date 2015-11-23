//
// Created by Martin on 22. 11. 2015.
//

#include <iostream>
#include "Loader.hpp"
#include "FileLoader.h"

Loader::Loader(GLuint programId) {
    this->programId = programId;
}

RawModel* Loader::initLoading() {
    RawModel *rawModel = new RawModel();

    // Activate the program
    glUseProgram(this->programId);

    // Generate a vertex array object
    glGenVertexArrays(1, &rawModel->vao);
    glBindVertexArray(rawModel->vao);

    return rawModel;
}

void Loader::clean() {
    // Complete the vertex array object
    glBindVertexArray(NULL);
}

RawModel* Loader::load(std::vector<GLfloat> vertex_buffer, std::vector<GLfloat> texcoord_buffer, std::vector<GLuint> index_data,
                      std::vector<GLfloat> normals_data) {
    RawModel *rawModel = initLoading();

    setVertexPositions(rawModel, vertex_buffer);
    setTextureCoords(rawModel, texcoord_buffer);
    setIndices(rawModel, index_data);
    setNormals(rawModel, normals_data);

    clean();

    return rawModel;
}

RawModel* Loader::load(std::vector<GLfloat> vertex_buffer, std::vector<GLfloat> texcoord_buffer) {
    RawModel *rawModel = initLoading();

    setVertexPositions(rawModel, vertex_buffer, 2);
    //setTextureCoords(rawModel, texcoord_buffer);
    rawModel->mesh_vertex_count = vertex_buffer.size() / 2;
    clean();

    return rawModel;
}

void Loader::setVertexPositions(RawModel *rawModel, std::vector<GLfloat> vertex_buffer) {
    setVertexPositions(rawModel, vertex_buffer, 3);
}

void Loader::setVertexPositions(RawModel *rawModel, std::vector<GLfloat> vertex_buffer, int size) {
    // Generate and upload a buffer with vertex positions to GPU
    glGenBuffers(1, &rawModel->vbo);
    glBindBuffer(GL_ARRAY_BUFFER, rawModel->vbo);
    glBufferData(GL_ARRAY_BUFFER, vertex_buffer.size() * sizeof(GLfloat), vertex_buffer.data(), GL_STATIC_DRAW);

    // Bind the buffer to "Position" attribute in program
    GLint position_attrib = glGetAttribLocation(this->programId, "Position");
    glEnableVertexAttribArray(position_attrib);
    glVertexAttribPointer(position_attrib, size, GL_FLOAT, GL_FALSE, 0, 0);

}

void Loader::setTextureCoords(RawModel *rawModel, std::vector<GLfloat> texcoord_buffer) {
    // Generate and upload a buffer with texture coordinates to GPU
    glGenBuffers(1, &rawModel->tbo);
    glBindBuffer(GL_ARRAY_BUFFER, rawModel->tbo);
    glBufferData(GL_ARRAY_BUFFER, texcoord_buffer.size() * sizeof(GLfloat), texcoord_buffer.data(), GL_STATIC_DRAW);

    // Bind the buffer to "TexCoord" attribute in program
    if (texcoord_buffer.size() > 0) {
        GLint texcoord_attrib = glGetAttribLocation(this->programId, "TexCoord");
        glEnableVertexAttribArray(texcoord_attrib);
        glVertexAttribPointer(texcoord_attrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
    } else {
        std::cout << "Warning: OBJ file has no texture coordinates!" << std::endl;
    }
}

void Loader::setIndices(RawModel *rawModel, std::vector<GLuint> index_data) {
    // Generate and upload a buffer with indices to GPU
    glGenBuffers(1, &rawModel->ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rawModel->ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_data.size() * sizeof(GLuint), index_data.data(), GL_STATIC_DRAW);
}

void Loader::setNormals(RawModel *rawModel, std::vector<GLfloat> normals_data) {
    glGenBuffers(1, &rawModel->nbo);
    glBindBuffer(GL_ARRAY_BUFFER, rawModel->nbo);
    glBufferData(GL_ARRAY_BUFFER, normals_data.size() * sizeof(GLfloat), normals_data.data(), GL_STATIC_DRAW );

    if (normals_data.size() > 0) {
        GLint normal_attrib = glGetAttribLocation(this->programId, "Normal");
        glEnableVertexAttribArray(normal_attrib);
        glVertexAttribPointer(normal_attrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
    } else {
        std::cout << "object has no normals!" << std::endl;
    }
}

GLuint Loader::loadTexture(const std::string &image_file) {
    // Create new texture object
    GLuint texture_id;
    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);

    // Set mipmaps
    glGenerateMipmap(GL_TEXTURE_2D);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, -0.4f);

    FileLoader::TGAFILE_t tgafile;
    FileLoader::LoadTGAFile(image_file.c_str(), &tgafile);

    std::vector<char> buffer(tgafile.imageData, tgafile.imageData + tgafile.imageWidth * tgafile.imageHeight * (tgafile.bitCount / 8));

    int imageType = (tgafile.bitCount / 8) == 3 ? GL_RGB : GL_RGBA;
    glTexImage2D(GL_TEXTURE_2D, 0, imageType, tgafile.imageWidth, tgafile.imageHeight, 0, imageType, GL_UNSIGNED_BYTE, buffer.data());

    return texture_id;
}