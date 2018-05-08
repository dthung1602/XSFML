#include "XSFML/SoundManager.h"

namespace xsf {

    SoundManager::SoundManager(const std::string &configFileName)
            : BaseResourceManager(configFileName) {
        loadAutoResources();
    }

    sf::Sound SoundManager::get(const std::string &name) {
        // find sound with given name
        auto iter = resources.find(name);

        // not found
        if (iter == resources.end())
            throw BadResourceNameException(name);

        // not loaded
        if (!iter->second.isLoaded())
            throw ResourceNotLoadedException(name);

        // return sound object
        auto soundBufferPtr = iter->second.ptr;
        return sf::Sound(*soundBufferPtr);
    }

    BaseResourceManager<sf::SoundBuffer, sf::Sound>::ResourcePtr
    xsf::SoundManager::getRawResource(const std::string &fileName) {
        // sound buffer object
        auto soundBuffer = new sf::SoundBuffer();

        // load from file
        if (!soundBuffer->loadFromFile(fileName)) {
            // unsuccessful loading
            delete soundBuffer;
            throw ResourceLoadingException(fileName);
        }

        return soundBuffer;
    }

}