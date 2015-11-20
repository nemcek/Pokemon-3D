//
// Created by Martin on 17. 11. 2015.
//

#ifndef POKEMON3D_GROUND_H
#define POKEMON3D_GROUND_H

#include "src/objects/Mesh.h"
#include "src/textures/TerrainTexturePack.hpp"

namespace nsGround {

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

        Ground(GLint program_id, int gridX, int gridZ, const std::string &image_file, TerrainTexturePack *texturePack,
                    TerrainTexture *blendMap);

    };

}

#endif //POKEMON3D_GROUND_H
