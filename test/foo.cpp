#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>

using namespace std;


int main() {
    sf::Sprite sprite;
    sf::RenderWindow window;
    string s = "lkasdjflkasd jasd fjsadlkf jlkasd jfkls dlkflksafkjslkfjlksa df;klsjdlkfjasdlk;fjlksjd";
    cout << sizeof(s) + sizeof(sf::IntRect) + sizeof(int*) << endl;
    return 0;
}