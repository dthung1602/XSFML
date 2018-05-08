#ifndef XSFML_TEXTUREREGION_H
#define XSFML_TEXTUREREGION_H

#include <SFML/Graphics.hpp>

namespace xsf {

    class TextureManager;

    /**
     * @brief holds info of a region of a texture
     */
    class TextureRegion {

        friend class TextureManager;

    public:

        TextureRegion() : name(), texture(nullptr), rect() {};

        /**
         * @tparam StringType: char * or std::string, will be perfect forward to name's constructor
         * @param name       : name of region
         * @param texture    : texture which region belongs to
         * @param top        : x coordinate of top of region
         * @param left       : y coordinate of left of region
         * @param width      : region's width
         * @param height     : region's height
         */
        template<typename StringType>
        TextureRegion(StringType &&name, sf::Texture &texture, int top, int left, int width, int height)
                : name(std::forward<StringType>(name)), texture(&texture), rect(top, left, width, height) {};

        /**
         * @brief set sprite to render this texture region
         */
        void updateSprite(sf::Sprite &sprite) {
            sprite.setTexture(*texture);
            sprite.setTextureRect(rect);
        };

    private:

        std::string name;           /** texture region's name */
        sf::Texture *texture;       /** raw pointer to texture */
        sf::IntRect rect;           /** store info of regions: position within texture, dimensions */
    };

}

#endif //XSFML_TEXTUREREGION_H
