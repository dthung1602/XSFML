//
// Created by hung on 24/04/18.
//

#include "BaseResourceManager.h"
#include "Util.h"

namespace xsf {
    namespace {
        std::unordered_map<std::string, ResourceLoadTime> typeConvert = {
                {"STARTUP",  ResourceLoadTime::START_UP},
                {"MANUAL",   ResourceLoadTime::MANUAL},
                {"ONDEMAND", ResourceLoadTime::ON_DEMAND},
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
    bool BaseResourceManager<ResourceType>::load(const std::string &name) {
        auto &info = resourceInfo[name];
        switch (info.loadTime) {
            case ResourceLoadTime::MANUAL: // only load manual resources
                auto ptr = getRawResource(info.path);
                longLiveResourcePtrs[name] = std::move(ptr);
            case ResourceLoadTime::START_UP: // startup resource is always ready
                return true;
            default: // error or on-demand resource will not be loaded
                return false;
        }
    }

    template<typename ResourceType>
    bool BaseResourceManager<ResourceType>::loadMultiple(const NameContainer &container) {
        bool result = true;
        for (auto &iter: container)
            result &= load(iter);
        return result;
    }

    template<typename ResourceType>
    typename BaseResourceManager<ResourceType>::ResourcePtr
    BaseResourceManager<ResourceType>::getResource(const std::string &name) {
        auto info = resourceInfo[name];

        switch (info.loadTime) {
            case ResourceLoadTime::START_UP:
            case ResourceLoadTime::MANUAL:
                return longLiveResourcePtrs[name];
            case ResourceLoadTime::ON_DEMAND:
                auto &wptr = onDemandResourcePtrs[name]; // weak ref of resource
                if (wptr.expired()) { // resource not found or expired
                    ResourcePtr ptr = getRawResource(name); // get raw resource
                    wptr = ResourceWPtr(ptr); // point weak ref to it
                    return ptr;
                } else { // resource found & not expired, return share ptr to it
                    return ResourcePtr(wptr);
                }
            default: // error, return nullptr
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
            resourceInfo[name] = {name, filePath, loadTimeStr};
        }
    }

    template<typename ResourceType>
    void BaseResourceManager<ResourceType>::loadStartUpResources() {
        for (auto &iter : resourceInfo) {
            auto &info = iter.second;
            if (info.loadTime == ResourceLoadTime::START_UP) {
                auto ptr = getRawResource(info.name);
                longLiveResourcePtrs[info.name] = std::move(ptr);
            }
        }
    }

//    template<typename ResourceType>
//    typename BaseResourceManager<ResourceType>::ResourcePtr BaseResourceManager<ResourceType>::getRawResource(const std::string &fileName) {
        // pure virtual method
//        return xsf::BaseResourceManager::ResourcePtr();
//    }

    template<typename ResourceType>
    BaseResourceManager<ResourceType>::Container<std::shared_ptr<ResourceType>>
    BaseResourceManager<ResourceType>::getMultipleRawResource(
            const BaseResourceManager::NameContainer &fileNameContainer) {
        // check if all names are valid
        for (auto &fileName : fileNameContainer) {
            auto loadTime = resourceInfo[fileName].loadTime;
            if (loadTime == ResourceLoadTime::ERROR)
                throw std::runtime_error("Cannot find resource with given name");
        }

        // load resources
        Container <ResourcePtr> container;
        for (auto &fileName: fileNameContainer) {
            auto ptr = getRawResource(fileName);
            container.push_back(std::move(ptr));
        }
    }

    template<typename ResourceType>
    BaseResourceManager<ResourceType>::ResourceInfo::ResourceInfo()
            : name(), path(), loadTime(ResourceLoadTime::ERROR) {}

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