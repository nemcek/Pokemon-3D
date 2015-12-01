//
// Created by Martin on 17. 11. 2015.
//

#ifndef POKEMON3D_GROUND_H
#define POKEMON3D_GROUND_H

#include "src/objects/Mesh.h"
#include "src/textures/TerrainTexturePack.hpp"

class Ground {

private:
    const float size = 800;
    const float vertex_count = 128;

    void generateGround();

public:
    Mesh *mesh;
    float x;
    float z;
    TerrainTexturePack *texturePack;
    TerrainTexture *blendMap;
    float reflectivity = 0.1f;
    float shineDamper = 50.0f;
    GLuint programId;

    Ground(GLint program_id, int gridX, int gridZ, const std::string &image_file, TerrainTexturePack *texturePack,
                TerrainTexture *blendMap);

};

typedef std::shared_ptr<Ground> GroundPtr;

#endif //POKEMON3D_GROUND_H
