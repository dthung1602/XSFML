#include "XSFML/TextureManager.h"

namespace xsf {

    TextureManager::TextureManager(const std::string &configFile)
            : BaseResourceManager(configFile) {
        for (auto &resourceIter : resources) {
            ResourcePtr &ptr = resourceIter.second.ptr;
            for (auto &regionIter : ptr->regions)
                regionNameToAtlasName.insert({regionIter.second.name, ptr->name});
        }
    }

    TextureRegion xsf::TextureManager::get(const std::string &name) {
        auto atlasName = regionNameToAtlasName[name];
        auto iter = resources.find(atlasName);
        if (iter == resources.end())
            throw BadResourceNameException(name);

        auto &atlas = iter->second;
        if (!atlas.isLoaded())
            throw ResourceNotLoadedException(name);
        return atlas.ptr->regions[name];
    }

    BaseResourceManager<TextureAtlas, TextureRegion>::ResourcePtr &&xsf::TextureManager::getRawResource(const std::string &atlasFileName) {
        BaseResourceManager<TextureAtlas, TextureRegion>::ResourcePtr ptr(new TextureAtlas(atlasFileName));
        return std::move(ptr);
    }
}

