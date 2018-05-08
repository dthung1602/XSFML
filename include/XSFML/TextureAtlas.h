#ifndef XSFML_TEXTUREATLAS_H
#define XSFML_TEXTUREATLAS_H

#include <string>
#include <unordered_map>
#include <sstream>

#include "TextureRegion.h"

namespace xsf {

    class TextureManager;

    /**
     * @brief store texture and its regions
     */
    class TextureAtlas {

        friend class TextureManager;

    public:

        /**
         * @param atlasFile: relative path of atlas file
         * @param load: whether to load actual texture right after construction
         */
        explicit TextureAtlas(const std::string &atlasFile, bool load = true);

        /**
         * @return whether texture is loaded
         */
        bool isTextureLoaded() { return texture.getSize() != sf::Vector2u(); }

        /**
         * @brief Get texture region with given name
         *        \BadResourceNameExceoption or \ResourceNotLoadedException might be thrown
         * @param regionName : name of region
         * @return const reference to texture region
         */
        const TextureRegion &getTextureRegion(const std::string &regionName);

    private:

        std::string name;               /** name of atlas, used at TextureManager::load() and unload() */
        std::string texturePath;        /** relative path of texture file */
        sf::Texture texture;            /** texture object */
        std::unordered_map<std::string, xsf::TextureRegion> regions;     /** map region name to TextureRegion object */

        /**
         * @brief read content of atlas file and initialize \regions, \texturePath, \name fields
         * @param atlasFile; relative path of atlas file
         */
        void loadAtlasFile(const std::string &atlasFile);

        /**
         * @brief load texture to VRAM, do nothing if texture is loaded
         */
        void loadTexture();
    };

}

#endif //XSFML_TEXTUREATLAS_H
