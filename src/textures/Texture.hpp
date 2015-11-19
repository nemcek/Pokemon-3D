//
// Created by Martin on 17. 11. 2015.
//

#ifndef POKEMON3D_TEXTURE_H
#define POKEMON3D_TEXTURE_H

namespace nsTexture {

    class Texture {

    private:

    public:

        int textureId;
        float reflectivity = 0.5f;
        float shineDamper = 50.0f;

        Texture(int textureId);

    };

}

#endif //POKEMON3D_TEXTURE_H
