//
// Created by Martin on 25. 11. 2015.
//

#ifndef POKEMON3D_GUI_HPP
#define POKEMON3D_GUI_HPP

#include <vector>
#include <string>
#include <vector>
#include <GL/glew.h>

#include "src/gui/GuiTexture.hpp"
#include "src/loaders/Loader.hpp"

class Gui {

public:
    std::vector<GuiTexturePtr> guiTextures;
//    std::vector<GuiTexture *> guiTextures;

    Gui();
    virtual bool animate();
};

typedef std::shared_ptr<Gui> GuiPtr;

#endif //POKEMON3D_GUI_HPP
