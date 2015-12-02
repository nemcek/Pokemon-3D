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
    RawModelPtr rawModel;
//    RawModel *rawModel;

    void loadVAO(RawModelPtr model);
    void loadMatrix(glm::mat4 matrix);
    void loadTexture(GuiTexturePtr guiTexture);
    void unbind();
    void render(GuiPtr gui);

public:
    GuiShaderPtr guiShader;
//    GuiShader *guiShader;

    GuiRenderer(GuiShaderPtr shader, LoaderPtr loader);
    void render(std::vector<GuiTexturePtr> guis);
    void render(std::vector<GuiPtr> guis);
    void clean();
};

typedef std::shared_ptr<GuiRenderer> GuiRendererPtr;

#endif //POKEMON3D_GUIRENDERER_HPP
