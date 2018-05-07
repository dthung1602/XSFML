#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>

using namespace std;


class TextureRegion {

public:
    template<typename StringType>
    TextureRegion(StringType &&name, const sf::Texture &texture, int top, int left, int width, int height)
            : name(std::forward<StringType>(name)), texture(texture), rect(top, left, width, height) {};

    void updateSprite(sf::Sprite &sprite) {
        sprite.setTexture(texture);
        sprite.setTextureRect(rect);
    };

    std::string getName() { return name; }

private:
    const std::string name;
    const sf::Texture &texture;
    const sf::IntRect rect;
};

int main() {
    cout << sizeof(TextureRegion) << endl;

    return 0;
}