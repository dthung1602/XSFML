//
// Created by hung on 24/04/18.
//

#include <sstream>
#include "BaseResourceManager.h"
#include "Util.h"

//namespace xsf {
//    template<typename ResourceType>
//    BaseResourceManager<ResourceType>::BaseResourceManager(const std::string &configFileName) {
//        loadConfigFile(configFileName);
//        loadStartUpResources();
//    }
//
//    template<typename ResourceType>
//    BaseResourceManager<ResourceType>::~BaseResourceManager() {
//        // todo add sth here
//    }
//
//    template<typename ResourceType>
//    bool BaseResourceManager<ResourceType>::load(const std::string &name) {
//        // try to get info
//        // if no info with given name, a Resource object with loadTime = ERROR is created
//        auto &info = resourceInfo[name];
//
//        switch (info.loadTime) {
//            case ResourceLoadTime::MANUAL:     // only load manual resources
//                // TODO prevent duplicate resource
//                auto ptr = getRawResource(info.path);
//                longLiveResourcePtrs[name] = std::move(ptr);
//
//            case ResourceLoadTime::AUTO:   // startup resource has already loaded
//                return true;
//
//            default:                           // name is invalid or on-demand resource will not be loaded
//                return false;
//        }
//    }
//
//    template<typename ResourceType>
//    bool BaseResourceManager<ResourceType>::loadMultiple(const NameContainer &container) {
//        bool result = true;
//        for (auto &iter: container)
//            result &= load(iter);
//        return result;
//    }
//
//    template<typename ResourceType>
//    typename BaseResourceManager<ResourceType>::ResourcePtr
//    BaseResourceManager<ResourceType>::get(const std::string &name) {
//        // try to get info
//        // if no info with given name, a Resource object with loadTime = ERROR is created
//        auto info = resourceInfo[name];
//
//        switch (info.loadTime) {
//            // start up & manual resources stored in the same place: longLiveResources
//            case ResourceLoadTime::AUTO:
//            case ResourceLoadTime::MANUAL:
//                return longLiveResourcePtrs[name];
//
//            case ResourceLoadTime::ON_DEMAND:  // one-time-use resources
//                // weak ref of resource
//                auto &wptr = onDemandResourcePtrs[name];
//                // resource not found or expired
//                if (wptr.expired()) {
//                    ResourcePtr ptr = getRawResource(name); // get raw resource
//                    wptr = ResourceWPtr(ptr); // point weak ref to it
//                    return ptr;
//                } else {
//                    // resource found & not expired, return share ptr to it
//                    return ResourcePtr(wptr);
//                }
//
//            default: // invalid name -> return nullptr
//                return ResourcePtr();
//        }
//    }
//
//    template<typename ResourceType>
//    void BaseResourceManager<ResourceType>::loadConfigFile(const std::string &configFileName) {
//        auto fileStream = openFile(configFileName);
//
//        std::string loadTimeStr;
//        std::string name;
//        std::string filePath;
//
//        while (!fileStream.eof()) {
//            fileStream >> loadTimeStr >> name >> filePath;
//            fileStream.ignore(); // skip '\n'
//            resourceInfo[name] = {name, filePath, loadTimeStr};
//        }
//    }
//
//    template<typename ResourceType>
//    void BaseResourceManager<ResourceType>::loadStartUpResources() {
//        // save all name of resource with STARTUP load time to names
//        NameContainer names;
//        for (auto &iter : resourceInfo) {
//            auto &info = iter.second;
//            if (info.loadTime == ResourceLoadTime::AUTO)
//                names.push_back(info.name);
//        }
//
//        // load all
//        loadMultiple(names);
//    }
//
//    template<typename RawResourceType>
//    typename BaseResourceManager<RawResourceType>::ResourcePtr BaseResourceManager<RawResourceType>::getRawResource(const std::string &fileName) {
//        // pure virtual method
//        return xsf::BaseResourceManager::ResourcePtr();
//    }
//
//    template<typename ResourceType>
//    BaseResourceManager<ResourceType>::Container<std::shared_ptr<ResourceType>>
//    BaseResourceManager<ResourceType>::getMultipleRawResource(
//            const BaseResourceManager::NameContainer &fileNameContainer) {
//        // check if all names are valid
//        for (auto &fileName : fileNameContainer) {
//            auto loadTime = resourceInfo[fileName].loadTime;
//            if (loadTime == ResourceLoadTime::ERROR)
//                throw std::runtime_error("Cannot find resource: " + fileName);
//        }
//
//        // load resources
//        Container<ResourcePtr> container;
//        for (auto &fileName: fileNameContainer) {
//            auto ptr = getRawResource(fileName);
//            container.push_back(std::move(ptr));
//        }
//
//        return container;
//    }
//
//    template<typename ResourceType>
//    BaseResourceManager<ResourceType>::ResourceInfo::ResourceInfo()
//            : name(), path(), loadTime(ResourceLoadTime::ERROR) {}
//
//    template<typename ResourceType>
//    BaseResourceManager<ResourceType>::ResourceInfo::ResourceInfo(
//            std::string name, std::string path, std::string loadTimeStr)
//            : name(name),
//              path(path),
//              loadTime(typeConvert[loadTimeStr]) {
//        // check if loadTime is valid
//        if (loadTime == ResourceLoadTime::ERROR)
//            throw std::runtime_error("Invalid ResourceLoadTime");
//    }
//}

///
///
///
///
///
///
///
///
///
///

namespace xsf {
    namespace {
        /**
         * @brief convert string in config file to \ResourceLoadTime enum
         */
        std::unordered_map<std::string, ResourceLoadTime> loadTimeConvert = {
                {"AUTO",   ResourceLoadTime::AUTO},
                {"MANUAL", ResourceLoadTime::MANUAL},
        };
    }


    template<typename RawResourceType, typename ResourceHandler>
    BaseResourceManager<RawResourceType, ResourceHandler>::BaseResourceManager(const std::string &configFileName) {
        loadConfigFile(configFileName);
        loadAutoResources();
    }

    template<typename RawResourceType, typename ResourceHandler>
    BaseResourceManager<RawResourceType, ResourceHandler>::~BaseResourceManager() {
        // todo add sth here
    }

    template<typename RawResourceType, typename ResourceHandler>
    int BaseResourceManager<RawResourceType, ResourceHandler>::load(const std::string &name) {
        // try to get resource
        auto iter = resources.find(name);

        // resource name not found
        if (iter == resources.end())
            throw BadResourceNameException(name);

        auto &resource = iter->second;

        // load raw resource if not loaded
        if (!resource.isLoaded()) {
            auto ptr = getRawResource(resource.path);
            resources[name] = std::move(ptr);
            return 1;
        }

        return 0;
    }

    template<typename RawResourceType, typename ResourceHandler>
    int BaseResourceManager<RawResourceType, ResourceHandler>::loadMultiple(
            const BaseResourceManager::NameContainer &container) {
        int count = 0;
        for (auto &name : container)
            count += load(name);
        return count;
    }

    template<typename RawResourceType, typename ResourceHandler>
    int BaseResourceManager<RawResourceType, ResourceHandler>::unload(const std::string &name) {
        // try to get resource
        auto iter = resources.find(name);

        // resource name not found
        if (iter == resources.end())
            throw BadResourceNameException(name);

        auto &resource = iter->second;

        // unload raw resource if not unloaded
        if (resource.isLoaded()) {
            resources[name].ptr.release();
            return 1;
        }

        return 0;
    }

    template<typename RawResourceType, typename ResourceHandler>
    int BaseResourceManager<RawResourceType, ResourceHandler>::unloadMultiple(
            const BaseResourceManager::NameContainer &container) {
        int count = 0;
        for (auto &name : container)
            count += unload(name);
        return count;
    }

//    template<typename RawResourceType, typename ResourceHandler>
//    ResourceHandler BaseResourceManager<RawResourceType, ResourceHandler>::get(const std::string &name) {
//        return nullptr;
//    }

    template<typename RawResourceType, typename ResourceHandler>
    void BaseResourceManager<RawResourceType, ResourceHandler>::loadConfigFile(const std::string &configFileName) {
        auto fileStream = openFile(configFileName);
        fileStream.exceptions();

        std::string loadTimeStr;
        std::string name;
        std::string filePath;

        try {
            while (!fileStream.eof()) {
                fileStream >> loadTimeStr >> name >> filePath;
                resources[name] = Resource(name, filePath, loadTimeStr);
            }
        } catch (std::ios_base::failure &failure) {
            throw BadConfigFileException();
        }
    }

    template<typename RawResourceType, typename ResourceHandler>
    void BaseResourceManager<RawResourceType, ResourceHandler>::loadAutoResources() {

    }

    template<typename RawResourceType, typename ResourceHandler>
    BaseResourceManager<RawResourceType, ResourceHandler>::Container<ResourceHandler>
    BaseResourceManager<RawResourceType, ResourceHandler>::getMultipleRawResource(
            const BaseResourceManager::NameContainer &fileNameContainer) {
        return BaseResourceManager<RawResourceType, ResourceHandler>::Container<ResourceHandler>();
    }

    template<typename RawResourceType, typename ResourceHandler>
    BaseResourceManager<RawResourceType, ResourceHandler>::Resource::Resource()
            : name(), path(), loadTime(ResourceLoadTime::ERROR) {}

    template<typename RawResourceType, typename ResourceHandler>
    BaseResourceManager<RawResourceType, ResourceHandler>::Resource::Resource(const std::string &name,
                                                                              const std::string &path,
                                                                              const std::string &loadTimeStr)
            : name(name), path(path), loadTime(loadTimeConvert[loadTimeStr]) {
        if (loadTime == ResourceLoadTime::ERROR)
            throw BadConfigFileException();
    }
}