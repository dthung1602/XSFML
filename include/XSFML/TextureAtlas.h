//
// Created by hung on 04/05/18.
//

#ifndef XSFML_TEXTUREALIAS_H
#define XSFML_TEXTUREALIAS_H

#include <string>
#include <unordered_map>
#include <sstream>

#include <SFML/Graphics.hpp>

#include "XSFML/TextureRegion.h"
#include "XSFML/Exception.h"
#include "XSFML/Util.h"

namespace xsf {

    class TextureManager;

    class TextureAtlas {

        friend class TextureManager;

    public:

        explicit TextureAtlas(const std::string &aliasFile);

        const TextureRegion &getTextureRegion(const std::string &regionName);

    private:
        std::string name;
        sf::Texture texture;
        std::unordered_map<std::string, xsf::TextureRegion> regions;
    };



}

#endif //XSFML_TEXTUREALIAS_H
