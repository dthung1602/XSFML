#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>

//#include "XSFML/BaseResourceManager.h"
//#include "XSFML/Util.h"

using namespace std;

class Foo {
public:
    Foo() { cout << "begin" << endl; }

    ~Foo() { cout << "end" << endl; }
};

int main() {
    sf::Texture texture;
    texture.loadFromFile("abc");
    sf::Sprite sprite(texture, sf::IntRect(13, 43, 54, 34));

    sf::RenderWindow renderWindow;
    renderWindow.draw(sprite);
//    sprite.set


    char c[] = "This is ok?";
    string s(c);
    s[2] = 'X';
    cout << s << endl << c << endl;
    return 0;
}