//
// Created by hung on 04/05/18.
//

#ifndef XSFML_TEXTUREATLAS_H
#define XSFML_TEXTUREATLAS_H

#include <string>
#include <unordered_map>
#include <sstream>

#include <SFML/Graphics.hpp>

#include "TextureRegion.h"
#include "Exception.h"
#include "Util.h"

namespace xsf {

    class TextureManager;

    class TextureAtlas {

        friend class TextureManager;

    public:

        explicit TextureAtlas(const std::string &atlasFile, bool load = true);

        bool isTextureLoaded() { return texture.getSize() != sf::Vector2u(); }

        const TextureRegion &getTextureRegion(const std::string &regionName);

    private:
        std::string name;
        std::string texturePath;
        sf::Texture texture;
        std::unordered_map<std::string, xsf::TextureRegion> regions;

        void loadAtlasFile(const std::string &atlasFile);

        void loadTexture();
    };


}

#endif //XSFML_TEXTUREATLAS_H
