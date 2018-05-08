#include "XSFML/TextureManager.h"

namespace xsf {

    namespace {
        using ResourcePtrType = BaseResourceManager<TextureAtlas, TextureRegion>::ResourcePtr; // = TextureAtlas*
    }

    TextureManager::TextureManager(const std::string &configFile)
            : BaseResourceManager(configFile) {
        loadAutoResources();
    }

    TextureRegion xsf::TextureManager::get(const std::string &name) {
        // find name of atlas which region belongs to
        auto atlasIter = regionNameToAtlasName.find(name);
        if (atlasIter == regionNameToAtlasName.end())
            throw BadResourceNameException(name);

        // get atlas
        auto iter = resources.find(atlasIter->second);
        if (iter == resources.end())
            throw ResourceNotLoadedException(name);

        // check if atlas is loaded
        auto &resource = iter->second;
        if (!resource.isLoaded()) // todo
            throw ResourceNotLoadedException(name);

        return resource.ptr->getTextureRegion(name);
    }

    ResourcePtrType xsf::TextureManager::getRawResource(const std::string &atlasFileName) {
        return new TextureAtlas(atlasFileName);
    }

    void TextureManager::loadAutoResources() {
        for (auto &resourceIter : resources) {
            // add region -> atlas map
            auto atlas = new TextureAtlas(resourceIter.second.path, false); // todo consider share_ptr
            for (auto &regionIter : atlas->regions)
                regionNameToAtlasName[regionIter.second.name] = atlas->name;

            // load auto resource
            if (resourceIter.second.loadTime == ResourceLoadTime::AUTO) {
                resourceIter.second.ptr = atlas;
                atlas->loadTexture();
            } else {
                // release memory
                delete atlas;
            }
        }
    }
}

