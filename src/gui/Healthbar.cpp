//
// Created by Martin on 25. 11. 2015.
//

#include "src/gui/Healthbar.hpp"

Healthbar::Healthbar(const std::string &fillImage, const std::string &borderImage, LoaderPtr loader, HealthbarPosition position)
        : Gui() {

    init(loader, position, fillImage, borderImage);

    this->guiTextures.push_back(fill);
    this->guiTextures.push_back(border);

    this->pokemon = pokemon;
    this->lastHp = pokemon->maxHp;
    this->oneHealthProtion = this->fill->scale.x / pokemon->maxHp;
}

Healthbar::Healthbar(PokemonPtr pokemon, const std::string &fillImage, const std::string &borderImage,
                     LoaderPtr loader, HealthbarPosition position)
        : Gui() {
    init(loader, position, fillImage, borderImage);

    this->guiTextures.push_back(fill);
    this->guiTextures.push_back(border);

    this->pokemon = pokemon;
    this->lastHp = pokemon->maxHp;
    this->oneHealthProtion = this->fill->scale.x / pokemon->maxHp;
}

void Healthbar::takeDamage(int damage) {

    float damageToTake = damage * this->oneHealthProtion;

    float xScale = fill->scale.x;
    float xPos = fill->position.x;

    // prevents from going to negative health
    if (xScale <= 0 || xScale - damageToTake <= 0) {
        fill->scale = glm::vec2(0.0f, fill->scale.y);
        return;
    }

    fill->scale = glm::vec2(xScale - damageToTake, fill->scale.y);
    fill->position = glm::vec2(xPos - damageToTake, fill->position.y);
}

bool Healthbar::animate() {
    this->takeDamage(this->lastHp - pokemon->currentHp);
    this->lastHp = pokemon->currentHp;
}

void Healthbar::init(LoaderPtr loader, HealthbarPosition position, const std::string &fillImage, const std::string &borderImage) {
    if (position == HealthbarPosition::BOTTOM_RIGHT) {
        this->fill = GuiTexturePtr(new GuiTexture(loader->loadTexture(fillImage), glm::vec2(0.65f, -0.75f), glm::vec2(0.25f, 0.025f)));
        this->border = GuiTexturePtr(new GuiTexture(loader->loadTexture(borderImage), glm::vec2(0.59f, -0.75f), glm::vec2(0.36f, 0.6)));
    } else if (position == HealthbarPosition::TOP_LEFT) {
        this->fill = GuiTexturePtr(new GuiTexture(loader->loadTexture(fillImage), glm::vec2(-0.53f, 0.75f), glm::vec2(0.25f, 0.025f)));
        this->border = GuiTexturePtr(new GuiTexture(loader->loadTexture(borderImage), glm::vec2(-0.59f, 0.75f), glm::vec2(0.36f, 0.6)));
    }
}