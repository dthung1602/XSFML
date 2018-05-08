#ifndef XSFML_TEXTUREREGION_H
#define XSFML_TEXTUREREGION_H

#include <SFML/Graphics.hpp>

namespace xsf {

    class TextureManager;

    class TextureRegion {

        friend class TextureManager;

    public:

        TextureRegion() : name(), texture(nullptr), rect() {};

        template<typename StringType>
        TextureRegion(StringType &&name, sf::Texture &texture, int top, int left, int width, int height)
                : name(std::forward<StringType>(name)), texture(&texture), rect(top, left, width, height) {};

        void updateSprite(sf::Sprite &sprite) {
            sprite.setTexture(*texture);
            sprite.setTextureRect(rect);
        };

        std::string getName() { return name; }

    private:
        std::string name;
        sf::Texture *texture;
        sf::IntRect rect;
    };

}

#endif //XSFML_TEXTUREREGION_H
