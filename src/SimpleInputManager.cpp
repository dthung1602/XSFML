#include <XSFML/Exception.h>
#include "XSFML/SimpleInputManager.h"

#include "XSFML/Util.h"

namespace xsf {
    const std::unordered_map<std::string, sf::Keyboard::Key> SimpleInputManager::keyNameToEnum = {
            {"A",         sf::Keyboard::Key::A},            ///< The A key
            {"B",         sf::Keyboard::Key::B},            ///< The B key
            {"C",         sf::Keyboard::Key::C},            ///< The C key
            {"D",         sf::Keyboard::Key::D},            ///< The D key
            {"E",         sf::Keyboard::Key::E},            ///< The E key
            {"F",         sf::Keyboard::Key::F},            ///< The F key
            {"G",         sf::Keyboard::Key::G},            ///< The G key
            {"H",         sf::Keyboard::Key::H},            ///< The H key
            {"I",         sf::Keyboard::Key::I},            ///< The I key
            {"J",         sf::Keyboard::Key::J},            ///< The J key
            {"K",         sf::Keyboard::Key::K},            ///< The K key
            {"L",         sf::Keyboard::Key::L},            ///< The L key
            {"M",         sf::Keyboard::Key::M},            ///< The M key
            {"N",         sf::Keyboard::Key::N},            ///< The N key
            {"O",         sf::Keyboard::Key::O},            ///< The O key
            {"P",         sf::Keyboard::Key::P},            ///< The P key
            {"Q",         sf::Keyboard::Key::Q},            ///< The Q key
            {"R",         sf::Keyboard::Key::R},            ///< The R key
            {"S",         sf::Keyboard::Key::S},            ///< The S key
            {"T",         sf::Keyboard::Key::T},            ///< The T key
            {"U",         sf::Keyboard::Key::U},            ///< The U key
            {"V",         sf::Keyboard::Key::V},            ///< The V key
            {"W",         sf::Keyboard::Key::W},            ///< The W key
            {"X",         sf::Keyboard::Key::X},            ///< The X key
            {"Y",         sf::Keyboard::Key::Y},            ///< The Y key
            {"Z",         sf::Keyboard::Key::Z},            ///< The Z key
            {"Num0",      sf::Keyboard::Key::Num0},         ///< The 0 key
            {"Num1",      sf::Keyboard::Key::Num1},         ///< The 1 key
            {"Num2",      sf::Keyboard::Key::Num2},         ///< The 2 key
            {"Num3",      sf::Keyboard::Key::Num3},         ///< The 3 key
            {"Num4",      sf::Keyboard::Key::Num4},         ///< The 4 key
            {"Num5",      sf::Keyboard::Key::Num5},         ///< The 5 key
            {"Num6",      sf::Keyboard::Key::Num6},         ///< The 6 key
            {"Num7",      sf::Keyboard::Key::Num7},         ///< The 7 key
            {"Num8",      sf::Keyboard::Key::Num8},         ///< The 8 key
            {"Num9",      sf::Keyboard::Key::Num9},         ///< The 9 key
            {"Escape",    sf::Keyboard::Key::Escape},       ///< The Escape key
            {"LControl",  sf::Keyboard::Key::LControl},     ///< The left Control key
            {"LShift",    sf::Keyboard::Key::LShift},       ///< The left Shift key
            {"LAlt",      sf::Keyboard::Key::LAlt},         ///< The left Alt key
            {"LSystem",   sf::Keyboard::Key::LSystem},      ///< The left OS specific key: window (Windows and Linux)", apple (MacOS X), ...
            {"RControl",  sf::Keyboard::Key::RControl},     ///< The right Control key
            {"RShift",    sf::Keyboard::Key::RShift},       ///< The right Shift key
            {"RAlt",      sf::Keyboard::Key::RAlt},         ///< The right Alt key
            {"RSystem",   sf::Keyboard::Key::RSystem},      ///< The right OS specific key: window (Windows and Linux)", apple (MacOS X), ...
            {"Menu",      sf::Keyboard::Key::Menu},         ///< The Menu key
            {"LBracket",  sf::Keyboard::Key::LBracket},     ///< The [ key
            {"RBracket",  sf::Keyboard::Key::RBracket},     ///< The ] key
            {"SemiColon", sf::Keyboard::Key::SemiColon},    ///< The ; key
            {"Comma",     sf::Keyboard::Key::Comma},        ///< The }, key
            {"Period",    sf::Keyboard::Key::Period},       ///< The . key
            {"Quote",     sf::Keyboard::Key::Quote},        ///< The ' key
            {"Slash",     sf::Keyboard::Key::Slash},        ///< The / key
            {"BackSlash", sf::Keyboard::Key::BackSlash},    ///< The \ key
            {"Tilde",     sf::Keyboard::Key::Tilde},        ///< The ~ key
            {"Equal",     sf::Keyboard::Key::Equal},        ///< The = key
            {"Dash",      sf::Keyboard::Key::Dash},         ///< The - key
            {"Space",     sf::Keyboard::Key::Space},        ///< The Space key
            {"Return",    sf::Keyboard::Key::Return},       ///< The Return key
            {"BackSpace", sf::Keyboard::Key::BackSpace},    ///< The Backspace key
            {"Tab",       sf::Keyboard::Key::Tab},          ///< The Tabulation key
            {"PageUp",    sf::Keyboard::Key::PageUp},       ///< The Page up key
            {"PageDown",  sf::Keyboard::Key::PageDown},     ///< The Page down key
            {"End",       sf::Keyboard::Key::End},          ///< The End key
            {"Home",      sf::Keyboard::Key::Home},         ///< The Home key
            {"Insert",    sf::Keyboard::Key::Insert},       ///< The Insert key
            {"Delete",    sf::Keyboard::Key::Delete},       ///< The Delete key
            {"Add",       sf::Keyboard::Key::Add},          ///< The + key
            {"Subtract",  sf::Keyboard::Key::Subtract},     ///< The - key
            {"Multiply",  sf::Keyboard::Key::Multiply},     ///< The * key
            {"Divide",    sf::Keyboard::Key::Divide},       ///< The / key
            {"Left",      sf::Keyboard::Key::Left},         ///< Left arrow
            {"Right",     sf::Keyboard::Key::Right},        ///< Right arrow
            {"Up",        sf::Keyboard::Key::Up},           ///< Up arrow
            {"Down",      sf::Keyboard::Key::Down},         ///< Down arrow
            {"Numpad0",   sf::Keyboard::Key::Numpad0},      ///< The numpad 0 key
            {"Numpad1",   sf::Keyboard::Key::Numpad1},      ///< The numpad 1 key
            {"Numpad2",   sf::Keyboard::Key::Numpad2},      ///< The numpad 2 key
            {"Numpad3",   sf::Keyboard::Key::Numpad3},      ///< The numpad 3 key
            {"Numpad4",   sf::Keyboard::Key::Numpad4},      ///< The numpad 4 key
            {"Numpad5",   sf::Keyboard::Key::Numpad5},      ///< The numpad 5 key
            {"Numpad6",   sf::Keyboard::Key::Numpad6},      ///< The numpad 6 key
            {"Numpad7",   sf::Keyboard::Key::Numpad7},      ///< The numpad 7 key
            {"Numpad8",   sf::Keyboard::Key::Numpad8},      ///< The numpad 8 key
            {"Numpad9",   sf::Keyboard::Key::Numpad9},      ///< The numpad 9 key
            {"F1",        sf::Keyboard::Key::F1},           ///< The F1 key
            {"F2",        sf::Keyboard::Key::F2},           ///< The F2 key
            {"F3",        sf::Keyboard::Key::F3},           ///< The F3 key
            {"F4",        sf::Keyboard::Key::F4},           ///< The F4 key
            {"F5",        sf::Keyboard::Key::F5},           ///< The F5 key
            {"F6",        sf::Keyboard::Key::F6},           ///< The F6 key
            {"F7",        sf::Keyboard::Key::F7},           ///< The F7 key
            {"F8",        sf::Keyboard::Key::F8},           ///< The F8 key
            {"F9",        sf::Keyboard::Key::F9},           ///< The F9 key
            {"F10",       sf::Keyboard::Key::F10},          ///< The F10 key
            {"F11",       sf::Keyboard::Key::F11},          ///< The F11 key
            {"F12",       sf::Keyboard::Key::F12},          ///< The F12 key
            {"F13",       sf::Keyboard::Key::F13},          ///< The F13 key
            {"F14",       sf::Keyboard::Key::F14},          ///< The F14 key
            {"F15",       sf::Keyboard::Key::F15},          ///< The F15 key
            {"Pause",     sf::Keyboard::Key::Pause}         ///< The Pause key
    };

    std::unordered_map<std::string, sf::Mouse::Button> SimpleInputManager::buttonNameToEnum = {
            {"Left",     sf::Mouse::Button::Left},       ///< The left mouse button
            {"Right",    sf::Mouse::Button::Right},      ///< The right mouse button
            {"Middle",   sf::Mouse::Button::Middle},     ///< The middle (wheel) mouse button
            {"XButton1", sf::Mouse::Button::XButton1},   ///< The first extra mouse button
            {"XButton2", sf::Mouse::Button::XButton2}    ///< The second extra mouse button
    };


    void SimpleInputManager::loadConfigFileName(const std::string &configFile) {
        // open file
        auto fileStream = openFile(configFile);
        if (!fileStream.is_open())
            throw ResourceLoadingException(configFile);

        // turn format errors to exceptions
        fileStream.exceptions();

        // read input bindings
        char type;
        int code;
        std::string name;

        try {
            while (fileStream >> type >> code >> name) {
                // each code is only bound once in config file
                if (isBinded(code))
                    throw KeyBindingConfigException();

                switch (type) {
                    case 'K': // keyboard binding
                        // translate name to enum
                        auto iterKey = keyNameToEnum.find(name);
                        // not found name
                        if (iterKey == keyNameToEnum.end())
                            throw KeyBindingConfigException();
                        // bind code to enum
                        keyBindings[code] = KeyStatus(iterKey->second);
                        break;

                    case 'M': // mouse button binding
                        // translate name to enum
                        auto iterButton = buttonNameToEnum.find(name);
                        // not found name
                        if (iterButton == buttonNameToEnum.end())
                            throw KeyBindingConfigException();
                        // bind code to enum
                        buttonBindings[code] = ButtonStatus(iterButton->second);
                        break;

                    default: // invalid binding
                        throw KeyBindingConfigException();
                }
            }
        } catch (std::ios_base::failure &failure) {
            throw KeyBindingConfigException();
        }
    }

    void SimpleInputManager::bind(int code, sf::Keyboard::Key key) {
        keyBindings[code] = KeyStatus(key);
    }

    void SimpleInputManager::bind(int code, sf::Mouse::Button button) {
        buttonBindings[code] = ButtonStatus(button);
    }

    bool SimpleInputManager::isBinded(int code) {
        return isBindedKeyBoard(code) || isBindedMouse(code);
    }

    bool SimpleInputManager::isBindedKeyBoard(int code) {
        return (keyBindings.find(code) == keyBindings.end());
    }

    bool SimpleInputManager::isBindedMouse(int code) {
        return (buttonBindings.find(code) == buttonBindings.end());
    }

    bool SimpleInputManager::actionHappened(int code) {
        // key is pressed
        if (auto iter = keyBindings.find(code); iter != keyBindings.end())
            return iter->second.pressed;

        // mouse button is pressed
        if (auto iter = buttonBindings.find(code); iter != buttonBindings.end())
            return iter->second.pressed;

        // invalid action code
        return false;
    }

    void SimpleInputManager::update() {
        // update keys pressed
        for (auto &iter : keyBindings)
            iter.second.pressed = sf::Keyboard::isKeyPressed(iter.second.key);

        // update button pressed
        for (auto &iter: buttonBindings)
            iter.second.pressed = sf::Mouse::isButtonPressed(iter.second.button);
    }
}