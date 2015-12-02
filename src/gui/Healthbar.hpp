//
// Created by Martin on 25. 11. 2015.
//

#ifndef POKEMON3D_HEALTHBAR_HPP
#define POKEMON3D_HEALTHBAR_HPP

#include "src/gui/Gui.hpp"

class Healthbar : public Gui {

private:
    std::vector<GLfloat> vertex_buffer = {-1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f, -1.0f};
    std::vector<GLfloat> texcoord_buffer = { 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f};

    float oneHealthProtion;
    int maxHp;
    GuiTexturePtr fill;
    GuiTexturePtr border;
//    GuiTexture *fill;
//    GuiTexture *border;

public:
    Healthbar(const std::string &fillImage, const std::string &borderImage, LoaderPtr loader, int maxHp);
    void takeDamage(int damage);
};

typedef std::shared_ptr<Healthbar> HealthbarPtr;

#endif //POKEMON3D_HEALTHBAR_HPP
