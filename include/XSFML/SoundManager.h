#ifndef XSFML_SOUNDMANAGER_H
#define XSFML_SOUNDMANAGER_H

#include <SFML/Audio.hpp>

#include "BaseResourceManager.h"

namespace xsf {
/**
 * ogg, wav, flac, aiff, au, raw, paf, svx, nist, voc, ircam, w64, mat4, mat5 pvf, htk, sds, avr, sd2, caf, wve, mpc2k, rf64
 */
    class SoundManager : public BaseResourceManager<sf::SoundBuffer, sf::Sound> {

    public:

        explicit SoundManager(const std::string &configFileName);

        sf::Sound get(const std::string &name) override;

    private:

        ResourcePtr getRawResource(const std::string &fileName) override;

    };
}


#endif //XSFML_SOUNDMANAGER_H
