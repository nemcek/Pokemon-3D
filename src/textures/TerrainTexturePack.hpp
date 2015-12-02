//
// Created by Martin on 19. 11. 2015.
//

#ifndef POKEMON3D_TERRAINTEXTUREPACK_HPP
#define POKEMON3D_TERRAINTEXTUREPACK_HPP

#include "src/textures/TerrainTexture.hpp"

class TerrainTexturePack {

private:

public:
    TerrainTexturePtr backgroundTexture;
    TerrainTexturePtr rTexture;
    TerrainTexturePtr gTexture;
    TerrainTexturePtr bTexture;

//    TerrainTexture *backgroundTexture;
//    TerrainTexture *rTexture;
//    TerrainTexture *gTexture;
//    TerrainTexture *bTexture;

    TerrainTexturePack(TerrainTexture *backgroundTexture, TerrainTexture *rTexture, TerrainTexture *gTexture,
                       TerrainTexture *bTexture);
};

typedef std::shared_ptr<TerrainTexturePack> TerrainTexturePackPtr;

#endif //POKEMON3D_TERRAINTEXTUREPACK_HPP
