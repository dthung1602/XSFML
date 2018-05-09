#ifndef XSFML_INPUTMANAGER_H
#define XSFML_INPUTMANAGER_H

#include <string>
#include <unordered_map>

#include <SFML/Graphics.hpp>
#include <random>

namespace xsf {

    /**
     * @brief a very simple input manager
     *        only support single key or mouse button pressed
     *        multiple concurrent input event binding to a single action is not supported
     *
     * Reference https://github.com/Pinkii-/SFML-Input-Manager
     */
    class SimpleInputManager {

    public:

        /**
         * @brief input manager with empty bindings
         */
        SimpleInputManager() = default;

        /**
         * @brief create input manager with bindings loaded from config file
         * @param configFile
         */
        explicit SimpleInputManager(const std::string &configFile) { loadConfigFileName(configFile); };

        /**
         * @brief read bindings from config file
         *        config file format:
         *              [M/K]     [code]      [name]
         *        M/K: M for mouse binding, K for keyboard binding
         *        code: and integer represent a unique action
         *        name: name of key or mouse button (valid names are enum listed in sf::Keyboard::Key and sf::Mouse::Button)
         * @param configFile: path of config file
         */
        void loadConfigFileName(const std::string &configFile);

        /**
         * @brief bind action to a key on keyboard
         * @param code: action's code
         * @param key: enum of the key
         * Note: rebinding is not checked
         */
        void bind(int code, sf::Keyboard::Key key);

        /**
         * @brief bind action to a mouse button
         * @param code: action's code
         * @param button: enum of the button
         * Note: rebinding is not checked
         */
        void bind(int code, sf::Mouse::Button button);

        /**
         * @param action's code
         * @return whether action has been binded to any key or button
         */
        bool isBinded(int code) { return isBindedKeyBoard(code) || isBindedMouse(code); };

        /**
         * @param action's code
         * @return whether action has been binded to any key
         */
        bool isBindedKeyBoard(int code);

        /**
         * @param action's code
         * @return whether action has been binded to any button
         */
        bool isBindedMouse(int code);

        /**
         * @param action's code
         * @return whether input binding of that action is satisfied
         */
        bool actionHappened(int code);

        /**
         * @brief update status of all keys and buttons
         *        must be called before checking actions by \actionHappend
         */
        void update();

    private:

        /**
         * @brief helper class for storing key status
         */
        struct KeyStatus {
            bool pressed;
            sf::Keyboard::Key key;

            KeyStatus() : pressed(false), key(sf::Keyboard::Key::Unknown) {}

            explicit KeyStatus(sf::Keyboard::Key key) : pressed(false), key(key) {}
        };

        /**
         * @brief helper class for storing mouse button status
         */
        struct ButtonStatus {
            bool pressed;
            sf::Mouse::Button button;

            ButtonStatus() : pressed(false), button(sf::Mouse::Button::ButtonCount) {}

            explicit ButtonStatus(sf::Mouse::Button button) : pressed(false), button(button) {}
        };

        std::unordered_map<int, KeyStatus> keyBindings;             /** store code to key bindings */
        std::unordered_map<int, ButtonStatus> buttonBindings;       /** store code to mouse button bindings */

    };

}

#endif //XSFML_INPUTMANAGER_H
