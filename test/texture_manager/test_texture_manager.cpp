#include<iostream>
#include <vector>
#include "XSFML/TextureManager.h"
#include "SFML/Graphics.hpp"

using namespace std;
using namespace xsf;
using namespace sf;

void renderWindow(vector<TextureRegion> &arr) {
    // render window
    RenderWindow window(VideoMode(300, 200), "abc");
    Event event;
    Sprite sprite;
    sprite.setPosition(50, 50);

    int i = 0;
    int count = 0;

    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }

        if (count++ % 5000 == 0) {
            count = 1;
            i = (i + 1) % (int) arr.size();
            arr[i].updateSprite(sprite);
        }

        window.clear(Color::Black);
        window.draw(sprite);
        window.display();
    }
}

int main() {
    TextureManager textureManager("../test/texture_manager/config.txt");

    // test get auto resource
    vector<TextureRegion> arr = {
            textureManager.get("life"),
            textureManager.get("standing-up-right"),
            textureManager.get("spike")
    };

    // get invalid res name
    try {
        auto a = textureManager.get("abc");
    } catch (BadResourceNameException &e) {
        cout << "bad res name caught" << endl;
    }

    // get not loaded res name
    try {
        auto a = textureManager.get("exit-portal-6");
    } catch (ResourceNotLoadedException &e) {
        cout << "res not loaded name caught" << endl;
    }

    // load
    cout << textureManager.load("test1") << endl; // print 1
    arr.push_back(textureManager.get("exit-portal-6"));
    renderWindow(arr);

    // unload
    cout << textureManager.unload("test1") << endl; // print 1
    renderWindow(arr); // white rect is rendered

    // get not loaded res name
    try {
        auto a = textureManager.get("exit-portal-6");
    } catch (ResourceNotLoadedException &e) {
        cout << "res not loaded name caught" << endl;
    }

    // unload multiple
    cout << textureManager.unloadMultiple({"test", "test1"}) << endl; // print 1
    renderWindow(arr); // white rect is rendered

    // get not loaded res name
    try {
        auto a = textureManager.get("spike");
    } catch (ResourceNotLoadedException &e) {
        cout << "res not loaded name caught" << endl;
    }

    // load multiple
    cout << textureManager.loadMultiple({"test1", "test"}) << endl; // print 2
    arr.clear();
    string names[] = {"life", "spike", "standing-up-right", "exit-portal-6"};
    for (auto &name: names)
        arr.push_back(textureManager.get(name));
    renderWindow(arr);

    cout << "end of main" << endl;
    return 0;
}