#ifndef XSFML_TEXTUREMANAGER_H
#define XSFML_TEXTUREMANAGER_H

#include <SFML/Graphics.hpp>

#include "BaseResourceManager.h"
#include "TextureAtlas.h"

namespace xsf {

    class TextureManager : public BaseResourceManager<TextureAtlas, TextureRegion> {

    public:

        explicit TextureManager(const std::string &configFile);

        TextureRegion get(const std::string &name) override;

        ResourcePtr getRawResource(const std::string &atlasFileName) override;

    private:

        std::unordered_map<std::string, std::string> regionNameToAtlasName;

        void loadAutoResources() override;
    };

}

#endif //XSFML_TEXTUREMANAGER_H
