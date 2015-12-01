#include <src/loaders/tiny_obj_loader.h>
#include <loaders/tiny_obj_loader.h>
#include "src/objects/Mesh.h"

Mesh::Mesh(const std::string &image_file)
        : image_name(image_file),
          object_name(""){
    this->texturedModel = new TexturedModel();
    this->texturedModel->rawModel = new RawModel();

    this->initTexture(image_file);

    this->position = glm::vec3(0.0f);
    this->rotX = 0.0f;
    this->rotY = 0.0f;
    this->rotZ = 0.0f;
    this->scale = 1.0f;
    this->radius = calculateRadius();
}

Mesh::Mesh(Loader *loader, const std::string &obj_file ,const std::string &image_file)
        : image_name(image_file),
          object_name(obj_file) {
    this->texturedModel = new TexturedModel();
    this->loader = loader;

    //this->texturedModel->rawModel = new RawModel();

    this->initTexture(image_file);
    this->initGeometry(obj_file);

    this->position = glm::vec3(0.0f);
    this->rotX = 0.0f;
    this->rotY = 0.0f;
    this->rotZ = 0.0f;
    this->scale = 1.0f;
    this->radius = calculateRadius();
}

Mesh::Mesh(Loader *loader, const std::string & obj_file, const std::string &image_file, glm::vec3 position, float rotX, float rotY, float rotZ,
           float scale)
        : image_name(image_file),
          object_name(obj_file) {

    this->texturedModel = new TexturedModel();
    this->loader = loader;

    //this->texturedModel->rawModel = new RawModel();

    this->initGeometry(obj_file);
    this->initTexture(image_file);
    this->position = position;
    this->rotX = rotX;
    this->rotY = rotY;
    this->rotZ = rotZ;
    this->scale = scale;
    this->radius = calculateRadius();
}

Mesh::Mesh(Loader *loader, const std::string & obj_file, const std::string &image_file, glm::vec3 position, float rotX, float rotY, float rotZ,
           float scale, float reflectivity, float shineDamper)
        : image_name(image_file),
          object_name(obj_file) {

    this->texturedModel = new TexturedModel();
    this->loader = loader;

    //this->texturedModel->rawModel = new RawModel();

    this->initGeometry(obj_file);
    this->initTexture(image_file);
    this->position = position;
    this->rotX = rotX;
    this->rotY = rotY;
    this->rotZ = rotZ;
    this->scale = scale;
    this->texturedModel->texture->reflectivity = reflectivity;
    this->texturedModel->texture->shineDamper = shineDamper;
    this->radius = calculateRadius();

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

    this->texturedModel->rawModel = this->loader->load(mesh.positions, mesh.texcoords, mesh.indices, mesh.normals);
    this->texturedModel->rawModel->mesh_indices_count = (int) mesh.indices.size();
}

// Load a new image from a raw RGB file directly into OpenGL memory
void Mesh::initTexture(const std::string &image_file) {
    // Create new texture object
    GLuint texture_id;
    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);

    this->texturedModel->texture = new nsTexture::Texture(texture_id);

    // Set mipmaps
    glGenerateMipmap(GL_TEXTURE_2D);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, -0.4f);

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

center_t Mesh::calculateCenter() {
    return center_t {( this->center_point.X_min + this->center_point.X_max ) / 2.0f,
                  ( this->center_point.Y_min + this->center_point.Y_max ) / 2.0f,
                  ( this->center_point.Z_min + this->center_point.Z_max ) / 2.0f };
}

glm::mat4 Mesh::createTransformationMatrix() {

    this->texturedModel->matrix = Transformations::createTransformationMatrix(this->position,
                        this->rotX, this->rotY, this->rotZ, this->scale);

    return this->texturedModel->matrix;
}

glm::vec3 Mesh::getCenter() {
    return glm::vec3(this->texturedModel->matrix[3].x, this->center.y, this->texturedModel->matrix[3].z);
}

void Mesh::animate(Scene *scene, float delta) { return; }

float Mesh::calculateRadius() {
    center_t c = calculateCenter();

    if (this->center_point.X_max - c.x < this->center_point.Z_max - c.z) {
        return (this->center_point.Z_max - c.z) * scale;
    } else {
        return (this->center_point.X_max - c.x) * scale;
    }
}

void Mesh::setPosition(glm::vec3 position) {
    this->position = position;
}

void Mesh::setRotation(glm::vec3 rotation) {
    this->rotX = rotation.x;
    this->rotY = rotation.y;
    this->rotZ = rotation.z;
}

void Mesh::setScale(float scale) {
    this->scale = scale;
}
