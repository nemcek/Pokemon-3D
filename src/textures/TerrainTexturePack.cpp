//
// Created by Martin on 19. 11. 2015.
//

#include "src/textures/TerrainTexturePack.hpp"

TerrainTexturePack::TerrainTexturePack(TerrainTexturePtr backgroundTexture, TerrainTexturePtr rTexture, TerrainTexturePtr gTexture,
                                       TerrainTexturePtr bTexture) {
    this->backgroundTexture = TerrainTexturePtr(backgroundTexture);
    this->rTexture = TerrainTexturePtr(rTexture);
    this->gTexture = TerrainTexturePtr(gTexture);
    this->bTexture = TerrainTexturePtr(bTexture);
}
