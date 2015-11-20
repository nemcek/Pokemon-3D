//
// Created by Martin on 19. 11. 2015.
//

#include "src/textures/TerrainTexturePack.hpp"

TerrainTexturePack::TerrainTexturePack(TerrainTexture *backgroundTexture, TerrainTexture *rTexture,
                                       TerrainTexture *gTexture, TerrainTexture *bTexture) {
    this->backgroundTexture = backgroundTexture;
    this->rTexture = rTexture;
    this->gTexture = gTexture;
    this->bTexture = bTexture;
}
