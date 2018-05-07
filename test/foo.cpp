#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>
#include <utility>

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

class A {
public:
    int a, b, c;
    string s;

    explicit A(string s) : a(2), b(3), c(2), s(std::move(s)) {}
};

int main() {
    cout << sizeof(TextureRegion) << endl;
    A a{};

    cout << a.a << a.b << a.c << a.s << endl;

    return 0;
}