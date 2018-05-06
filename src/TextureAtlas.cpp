//
// Created by hung on 04/05/18.
//

#include "XSFML/TextureAtlas.h"

namespace xsf {

    TextureAtlas::TextureAtlas(const std::string &aliasFile) {
        // open atlas file
        auto fileStream = openFile(aliasFile);
        // turn stream reading errors to exception
        fileStream.exceptions();

        // load texture
        std::string textureFile;
        fileStream.ignore(15, ' '); // ignore "texture: " at the beginning of file
        fileStream >> textureFile;
        if (!texture.loadFromFile(textureFile))
            throw ResourceLoadingException(textureFile);

        // read regions data
        std::string regionName;
        int x, y;
        int width, height;
        int xOffset, yOffset;
        int origW, origH;
        try {
            while (!fileStream.eof()) {
                fileStream >> regionName >> x >> y >> width >> height
                           >> xOffset >> yOffset >> origW>> origH;
                fileStream.ignore(15, ' '); // todo currently do not support rotate
                regions[regionName] = TextureRegion(regionName, texture, x, y, width, height); // todo offset...
            }
        } catch (std::ios_base::failure &failure) {
            throw BadConfigFileException();
        }
    }

    const TextureRegion &TextureAtlas::getTextureRegion(const std::string &regionName) {
        auto iter = regions.find(regionName);
        if (iter == regions.end())
            throw BadResourceNameException(regionName);
        return iter->second;
    }

}