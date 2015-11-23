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

class GuiRenderer {

private:
    RawModel *rawModel;
    GuiShader *guiShader;

    void loadVAO(RawModel *model);
    void loadMatrix(glm::mat4 matrix);
    void loadTexture(GuiTexture *guiTexture);
    void unbind();

public:
    GuiRenderer(RawModel *rawModel, GuiShader *shader);
    void render(std::vector<GuiTexture *> guis);
    void clean();
};

#endif //POKEMON3D_GUIRENDERER_HPP
