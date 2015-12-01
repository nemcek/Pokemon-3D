//
// Created by Martin on 19. 11. 2015.
//

#ifndef POKEMON3D_TERRAINTEXTURE_HPP
#define POKEMON3D_TERRAINTEXTURE_HPP

#include <memory>

class TerrainTexture {

public:

    int textureId;

    TerrainTexture(int texture_id);

};

typedef std::shared_ptr<TerrainTexture> TerrainTexturePtr;

#endif //POKEMON3D_TERRAINTEXTURE_HPP
