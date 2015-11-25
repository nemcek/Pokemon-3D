//
// Created by Martin on 23. 11. 2015.
//

#ifndef POKEMON3D_GUIRENDERER_HPP
#define POKEMON3D_GUIRENDERER_HPP

#include <vector>

#include "src/models/RawModel.hpp"
#include "src/gui/GuiTexture.hpp"
#include "src/gui/GuiShader.hpp"
#include "src/extensions/Transformations.hpp"
#include "src/gui/Gui.hpp"
#include "src/loaders/Loader.hpp"

class GuiRenderer {

private:
    RawModel *rawModel;

    void loadVAO(RawModel *model);
    void loadMatrix(glm::mat4 matrix);
    void loadTexture(GuiTexture *guiTexture);
    void unbind();
    void render(Gui *gui);

public:
    GuiShader *guiShader;

    GuiRenderer(GuiShader *shader, Loader *loader);
    void render(std::vector<GuiTexture *> guis);
    void render(std::vector<Gui *> guis);
    void clean();
};

#endif //POKEMON3D_GUIRENDERER_HPP
