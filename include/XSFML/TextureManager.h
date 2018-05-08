#ifndef XSFML_TEXTUREMANAGER_H
#define XSFML_TEXTUREMANAGER_H

#include <SFML/Graphics.hpp>

#include "BaseResourceManager.h"
#include "TextureAtlas.h"

namespace xsf {

    /**
     * @brief Manages textures
     *
     * Textures must be packed to atlas, using some tools like Cheetah-Texture-Packer
     *          https://github.com/scriptum/Cheetah-Texture-Packer
     *
     * Atlas file must have the form
     *      textures: atlas_image.png (image name with packed textures)
     *      Name     X pos  Y pos   Width  Height   Xoffset  Yoffset  Orig W  Orig H   Rot
     *      img1     0      0       0      0        3        14       3       14
     *      img2     90     36      5      7        1        4        7       14       r
     *      dir/img  0      41      5      9        1        2        7       14
     *
     * Currently rotation is NOT supported
     */
    class TextureManager : public BaseResourceManager<TextureAtlas, TextureRegion> {

    public:

        /**
         * @param atlasFile: relative path of atlas file
         */
        explicit TextureManager(const std::string &atlasFile);

        /**
         * @brief return TextureRegion with given name
         *        \BadResourceNameExceoption or \ResourceNotLoadedException might be thrown
         * @param name: name of texture region
         * @return a copy of TextureRegion object
         */
        TextureRegion get(const std::string &name) override;

    private:

        std::unordered_map<std::string, std::string> regionNameToAtlasName; /** map texture regions name to its atlas's */

        /**
         * @brief load TextureAtlas and its texture from file
         * @param atlasFileName: relative path of atlas file
         * @return raw pointer to a TextureAtlas object
         */
        ResourcePtr getRawResource(const std::string &atlasFileName) override;

        /**
         * @brief read all atlas file and populate \regionNameToAtlasName, then load AUTO resources
         */
        void loadAutoResources() override;
    };

}

#endif //XSFML_TEXTUREMANAGER_H
