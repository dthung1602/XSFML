//
// Created by hung on 04/05/18.
//

#include <SFML/Graphics.hpp>

#include "XSFML/TextureAtlas.h"
#include "XSFML/Util.h"

namespace xsf {

    TextureAtlas::TextureAtlas(const std::string &atlasFile, bool load) : name(extractResourceName(atlasFile)) {
        loadAtlasFile(atlasFile);
        if (load)
            loadTexture();
    }

    void TextureAtlas::loadAtlasFile(const std::string &atlasFile) {
        // open atlas file
        auto fileStream = openFile(atlasFile);
        if (!fileStream.is_open())
            throw ResourceLoadingException(atlasFile);

        // turn stream reading errors to exception
        fileStream.exceptions();

        // read texture path
        fileStream.ignore(15, ' '); // ignore "texture: " at the beginning of file
        fileStream >> texturePath;

        // read regions util eof
        std::string regionName;
        int x, y;
        int width, height;
        int xOffset, yOffset;
        int origW, origH;
        try {
            while (fileStream >> regionName >> x >> y >> width >> height
                              >> xOffset >> yOffset >> origW >> origH) {
                regionName = extractResourceName(regionName);
                regions[regionName] = TextureRegion(regionName, texture, x, y, width, height); // todo offset...
            }
        } catch (std::ios_base::failure &failure) {
            throw BadConfigFileException();
        }
    }

    void TextureAtlas::loadTexture() {
        if (!isTextureLoaded())
            if (!texture.loadFromFile(texturePath))
                throw ResourceLoadingException(texturePath);
    }

    const TextureRegion &TextureAtlas::getTextureRegion(const std::string &regionName) {
        auto iter = regions.find(regionName);
        if (iter == regions.end())
            throw BadResourceNameException(regionName);
        return iter->second;
    }
}