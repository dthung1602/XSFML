#include<iostream>
#include "XSFML/SimpleInputManager.h"
#include <SFML/Graphics.hpp>
#include <chrono>
#include <thread>

using namespace std;
using namespace sf;
using namespace xsf;

void testInput(SimpleInputManager &manager) {
    RenderWindow window(VideoMode(200, 300), "Input");

    Event event{};
    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
            else {
                manager.update();

                for (int a = 0; a < 5; a++)
                    if (manager.actionHappened(a))
                        cout << "action " << a << " happened"  << endl;

                this_thread::sleep_for(chrono::milliseconds(20));
            }
        }
        window.clear();
        window.display();
    }
}

int main() {
    // load config from file
    SimpleInputManager m("../test/input_manager/config-simple.txt");
    testInput(m);

    // add config manually
    SimpleInputManager manager;
    manager.bind(0, Keyboard::Left);
    manager.bind(1, Keyboard::Right);
    manager.bind(2, Keyboard::Up);
    manager.bind(3, Mouse::Right);
    manager.bind(4, Mouse::Left);
    testInput(manager);

    return 0;
}