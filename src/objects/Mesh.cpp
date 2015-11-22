#include <src/loaders/tiny_obj_loader.h>
#include "src/objects/Mesh.h"

Mesh::Mesh(GLuint program_id, const std::string &image_file) {
    this->program_id = program_id;
    this->texturedModel = new TexturedModel();
    this->initTexture(image_file);

    this->position = glm::vec3(0.0f);
    this->rotX = 0.0f;
    this->rotY = 0.0f;
    this->rotZ = 0.0f;
    this->scale = 1.0f;
}

Mesh::Mesh(GLuint program_id, const std::string &obj_file ,const std::string &image_file) {
    this->program_id = program_id;
    this->texturedModel = new TexturedModel();
    this->initTexture(image_file);
    this->initGeometry(obj_file);

    this->position = glm::vec3(0.0f);
    this->rotX = 0.0f;
    this->rotY = 0.0f;
    this->rotZ = 0.0f;
    this->scale = 1.0f;
}

Mesh::Mesh(GLuint program_id, const std::string & obj_file, const std::string &image_file, glm::vec3 position, float rotX, float rotY, float rotZ,
           float scale)  {
    this->program_id = program_id;

    this->texturedModel = new TexturedModel();

    this->initGeometry(obj_file);
    this->initTexture(image_file);
    this->position = position;
    this->rotX = rotX;
    this->rotY = rotY;
    this->rotZ = rotZ;
    this->scale = scale;
}

Mesh::Mesh(GLuint program_id, const std::string & obj_file, const std::string &image_file, glm::vec3 position, float rotX, float rotY, float rotZ,
           float scale, float reflectivity, float shineDamper)  {
    this->program_id = program_id;

    this->texturedModel = new TexturedModel();

    this->initGeometry(obj_file);
    this->initTexture(image_file);
    this->position = position;
    this->rotX = rotX;
    this->rotY = rotY;
    this->rotZ = rotZ;
    this->scale = scale;
    this->texturedModel->texture->reflectivity = reflectivity;
    this->texturedModel->texture->shineDamper = shineDamper;
}

void Mesh::initGeometry(const std::string &obj_file) {
    // Load OBJ file
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    tinyobj::center_point_t center_point = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};

    std::string err = tinyobj::LoadObj(shapes, materials, obj_file.c_str(), &center_point);

    this->center_point = center_point;

    if (!err.empty()) {
        std::cerr << err << std::endl;
        std::cerr << "Failed to load OBJ file " << obj_file << "!" << std::endl;
        return;
    }
    tinyobj::mesh_t mesh = shapes[0].mesh;
    this->texturedModel->mesh_t = &mesh;

    // Activate the program
    glUseProgram(this->program_id);

    // Generate a vertex array object
    glGenVertexArrays(1, &this->texturedModel->vao);
    glBindVertexArray(this->texturedModel->vao);

    // --- Vertex positions ---
    std::vector<GLfloat> vertex_buffer;
    for (int i = 0; i < (int) mesh.positions.size() / 3; i++) {
        vertex_buffer.push_back(mesh.positions[3 * i + 0]); // X
        vertex_buffer.push_back(mesh.positions[3 * i + 1]); // Y
        vertex_buffer.push_back(mesh.positions[3 * i + 2]); // Z
    }

    // Generate and upload a buffer with vertex positions to GPU
    glGenBuffers(1, &this->texturedModel->vbo);
    glBindBuffer(GL_ARRAY_BUFFER, this->texturedModel->vbo);
    glBufferData(GL_ARRAY_BUFFER, vertex_buffer.size() * sizeof(GLfloat), vertex_buffer.data(), GL_STATIC_DRAW);

    // Bind the buffer to "Position" attribute in program
    GLint position_attrib = glGetAttribLocation(this->program_id, "Position");
    glEnableVertexAttribArray(position_attrib);
    glVertexAttribPointer(position_attrib, 3, GL_FLOAT, GL_FALSE, 0, 0);

    // --- Texture coordinates ---
    std::vector<GLfloat> texcoord_buffer;
    for (int i = 0; i < (int) mesh.texcoords.size() / 2; i++) {
        texcoord_buffer.push_back(mesh.texcoords[2 * i + 0]); // U
        texcoord_buffer.push_back(mesh.texcoords[2 * i + 1]); // V
    }

    // Generate and upload a buffer with texture coordinates to GPU
    glGenBuffers(1, &this->texturedModel->tbo);
    glBindBuffer(GL_ARRAY_BUFFER, this->texturedModel->tbo);
    glBufferData(GL_ARRAY_BUFFER, texcoord_buffer.size() * sizeof(GLfloat), texcoord_buffer.data(), GL_STATIC_DRAW);

    // Bind the buffer to "TexCoord" attribute in program
    if (mesh.texcoords.size() > 0) {
        GLint texcoord_attrib = glGetAttribLocation(this->program_id, "TexCoord");
        glEnableVertexAttribArray(texcoord_attrib);
        glVertexAttribPointer(texcoord_attrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
    } else {
        std::cout << "Warning: OBJ file " << obj_file << " has no texture coordinates!" << std::endl;
    }

    // --- Indices (define which triangles consists of which vertices) ---
    std::vector<GLuint> index_data;
    this->texturedModel->mesh_indices_count = (int) mesh.indices.size();
    for (int i = 0; i < (int) mesh.indices.size(); i++) {
        index_data.push_back(mesh.indices[i]);
    }

    // Generate and upload a buffer with indices to GPU
    glGenBuffers(1, &this->texturedModel->ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->texturedModel->ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_data.size() * sizeof(GLuint), index_data.data(), GL_STATIC_DRAW);


    std::vector<GLfloat> normals_data;
    for (int i = 0; i < mesh.normals.size() / 3; i++ ) {
        normals_data.push_back(mesh.normals[3 * i + 0]); // X
        normals_data.push_back(mesh.normals[3 * i + 1]); // Y
        normals_data.push_back(mesh.normals[3 * i + 2]); // Z
    }

    glGenBuffers(1, &this->texturedModel->nbo);
    glBindBuffer(GL_ARRAY_BUFFER, this->texturedModel->nbo);
    glBufferData(GL_ARRAY_BUFFER, normals_data.size() * sizeof(GLfloat), normals_data.data(), GL_STATIC_DRAW );

    if (mesh.normals.size() > 0) {
        GLint normal_attrib = glGetAttribLocation(this->program_id, "Normal");
        glEnableVertexAttribArray(normal_attrib);
        glVertexAttribPointer(normal_attrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
    } else {
        std::cout << "object " << obj_file << " has no normals!" << std::endl;
    }
    // Complete the vertex array object
    glBindVertexArray(NULL);
}

// Load a new image from a raw RGB file directly into OpenGL memory
void Mesh::initTexture(const std::string &image_file) {
    // Create new texture object
    GLuint texture_id;
    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);

    this->texturedModel->texture = new nsTexture::Texture(texture_id);

    // Set mipmaps
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    FileLoader::TGAFILE_t tgafile;
    FileLoader::LoadTGAFile(image_file.c_str(), &tgafile);

    std::vector<char> buffer(tgafile.imageData, tgafile.imageData + tgafile.imageWidth * tgafile.imageHeight * (tgafile.bitCount / 8));

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tgafile.imageWidth, tgafile.imageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, buffer.data());
}

void Mesh::render() {
//    // Activate the program
//    glUseProgram(this->program_id);
//
//    // Bind the texture to "Texture" uniform in program
//    GLint texture_attrib = glGetUniformLocation(this->program_id, "Texture");
//    glUniform1i(texture_attrib, 0);
//    glActiveTexture(GL_TEXTURE0 + 0);
//    glBindTexture(GL_TEXTURE_2D, this->texture_id);
//
//    // Upload model matrix to GPU
//    GLint model_uniform = glGetUniformLocation(this->program_id, "ModelMatrix");
//    glUniformMatrix4fv(model_uniform, 1, GL_FALSE, glm::value_ptr(this->matrix));
//
//    // Draw object
//    glBindVertexArray(this->vao);
//    glDrawElements(GL_TRIANGLES, this->mesh_indices_count, GL_UNSIGNED_INT, 0);
//    glBindVertexArray(NULL);
}

glm::vec3 Mesh::calculateCenter() {
    return glm::normalize( glm::vec3( ( this->center_point.X_min + this->center_point.X_max ) / 2.0f,
                                      ( this->center_point.Y_min + this->center_point.Y_max ) / 2.0f,
                                      ( this->center_point.Z_min + this->center_point.Z_max ) / 2.0f) );
}

glm::mat4 Mesh::createTransformationMatrix() {

    this->texturedModel->matrix = Transformations::createTransformationMatrix(this->position,
                        this->rotX, this->rotY, this->rotZ, this->scale);

    return this->texturedModel->matrix;
}

glm::vec3 Mesh::getCenter() {
    return glm::vec3(this->texturedModel->matrix[3].x, this->center.y, this->texturedModel->matrix[3].z);
}

void Mesh::animate() { return; }
