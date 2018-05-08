#ifndef XSFML_SOUNDMANAGER_H
#define XSFML_SOUNDMANAGER_H

#include <SFML/Audio.hpp>

#include "BaseResourceManager.h"

namespace xsf {

    class SoundManager : public BaseResourceManager<sf::SoundBuffer, sf::Sound> {

    public:

        explicit SoundManager(const std::string &configFileName);

        sf::Sound get(const std::string &name) override;

    private:

        ResourcePtr getRawResource(const std::string &fileName) override;

    };
}


#endif //XSFML_SOUNDMANAGER_H
