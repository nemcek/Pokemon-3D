//
// Created by Martin on 17. 11. 2015.
//

#ifndef POKEMON3D_TEXTURE_H
#define POKEMON3D_TEXTURE_H

#include <memory>

class Texture {

private:

public:

    int textureId;
    float reflectivity = 0.5f;
    float shineDamper = 50.0f;

    Texture(int textureId);

};

typedef std::shared_ptr<Texture> TexturePtr;

#endif //POKEMON3D_TEXTURE_H
