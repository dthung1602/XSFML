//
// Created by hung on 24/04/18.
//

#include "BaseResourceManager.h"
#include "Util.h"

namespace xsf {
    namespace {
        const std::unordered_map<std::string, BaseResourceManager::ResourceLoadTime> typeConvert = {
                {"STARTUP",  BaseResourceManager::ResourceLoadTime::START_UP},
                {"MANUAL",   BaseResourceManager::ResourceLoadTime::MANUAL},
                {"ONDEMAND", BaseResourceManager::ResourceLoadTime::ON_DEMAND},
        };
    }

    template<typename ResourceType>
    BaseResourceManager<ResourceType>::BaseResourceManager(const std::string &configFileName) {
        loadConfigFile(configFileName);
        loadStartUpResources();
    }

    template<typename ResourceType>
    BaseResourceManager<ResourceType>::~BaseResourceManager() {
        // todo add sth here
    }

    template<typename ResourceType>
    BaseResourceManager::ResourcePtr BaseResourceManager<ResourceType>::getResource(const std::string &name) {
        auto resourceInfo = types[name];

        switch (resourceInfo.loadTime) {
            case ResourceLoadTime::START_UP:
            case ResourceLoadTime::MANUAL:
                return longLiveResourcePtrs[name];
            case ResourceLoadTime::ON_DEMAND:
                auto wptr = onDemandResourcePtrs[name];
                if (wptr.expired()) {
                    std::shared_ptr ptr(load(name));
                    onDemandResourcePtrs[name] = std::weak_ptr(ptr);
                    return ptr;
                }
            default:
                return ResourcePtr();
        }
    }

    template<typename ResourceType>
    void BaseResourceManager<ResourceType>::loadConfigFile(const std::string &configFileName) {
        auto fileStream = openFile(configFileName);

        std::string loadTimeStr;
        std::string name;
        std::string filePath;

        while (!fileStream.eof()) {
            fileStream >> loadTimeStr >> name >> filePath;
            fileStream.ignore();
            types[name] = {name, filePath, loadTimeStr};
        }
    }

    template<typename ResourceType>
    void BaseResourceManager<ResourceType>::loadStartUpResources() {
        for (auto &iter : types) {
            auto &resourceInfo = iter.second;
            if (resourceInfo.loadTime == ResourceLoadTime::START_UP) {
                auto ptr = load(resourceInfo.name);
                longLiveResourcePtrs[resourceInfo.name] = std::move(ptr);
            }
        }
    }

    template<typename ResourceType>
    BaseResourceManager::ResourcePtr BaseResourceManager<ResourceType>::load(const std::string &fileName) {
        // pure virtual method
        return xsf::BaseResourceManager::ResourcePtr();
    }

    template<typename ResourceType>
    template<typename Container>
    Container BaseResourceManager<ResourceType>::loadMultiple(const Container &nameList) {
        for (auto &iter : nameList)
            load(*iter);
    }

    template<typename ResourceType>
    BaseResourceManager<ResourceType>::ResourceInfo::ResourceInfo(
            std::string name, std::string path,
            std::string loadTimeStr) : name(name),
                                       path(path),
                                       loadTime(typeConvert[loadTimeStr]) {
        if (loadTime == ResourceLoadTime::ERROR)
            throw std::runtime_error("Invalid ResourceLoadTime");
    }
}