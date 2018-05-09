#ifndef XSFML_INPUTMANAGER_H
#define XSFML_INPUTMANAGER_H

#include <string>
#include <unordered_map>

#include <SFML/Graphics.hpp>
#include <random>

namespace xsf {

    /**
     * Reference https://github.com/Pinkii-/SFML-Input-Manager
     * Do not support joystick and multiple concurrent input event binding to a single action
     */
    class SimpleInputManager {

    public:

        SimpleInputManager() = default;

        explicit SimpleInputManager(const std::string &configFile) { loadConfigFileName(configFile); };

        void loadConfigFileName(const std::string &configFile);

        void bind(int code, sf::Keyboard::Key key);

        void bind(int code, sf::Mouse::Button button);

        bool isBinded(int code);

        bool isBindedKeyBoard(int code);

        bool isBindedMouse(int code);

        bool actionHappened(int code);

        void update();

    private:

        struct KeyStatus {
            bool pressed;
            sf::Keyboard::Key key;

            explicit KeyStatus(sf::Keyboard::Key key) : pressed(false), key(key) {}
        };

        struct ButtonStatus {
            bool pressed;
            sf::Mouse::Button button;

            explicit ButtonStatus(sf::Mouse::Button button) : pressed(false), button(button) {}
        };

        std::unordered_map<int, KeyStatus> keyBindings;
        std::unordered_map<int, ButtonStatus> buttonBindings;

        std::unordered_map<std::string, sf::Keyboard::Key> keyNameToEnum;
        std::unordered_map<std::string, sf::Mouse::Button> buttonNameToEnum;
    };

}

#endif //XSFML_INPUTMANAGER_H
