//
// Created by Martin on 25. 11. 2015.
//

#ifndef POKEMON3D_HEALTHBAR_HPP
#define POKEMON3D_HEALTHBAR_HPP

#include "src/gui/Gui.hpp"
#include "src/objects/Pokemon.hpp"

enum HealthbarPosition {
    BOTTOM_RIGHT,
    TOP_LEFT
};

class Healthbar : public Gui {

private:
    std::vector<GLfloat> vertex_buffer = {-1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f, -1.0f};
    std::vector<GLfloat> texcoord_buffer = { 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f};

    float oneHealthProtion;
    float lastHp;
    GuiTexturePtr fill;
    GuiTexturePtr border;
    PokemonPtr pokemon;
    void init(LoaderPtr loader, HealthbarPosition position, const std::string &fillImage, const std::string &borderImage);
public:
    Healthbar(const std::string &fillImage, const std::string &borderImage, LoaderPtr loader, HealthbarPosition position);
    Healthbar(PokemonPtr pokemon, const std::string &fillImage, const std::string &borderImage, LoaderPtr loader, HealthbarPosition position);
    void takeDamage(int damage);
    bool animate() override;
};

typedef std::shared_ptr<Healthbar> HealthbarPtr;

#endif //POKEMON3D_HEALTHBAR_HPP
