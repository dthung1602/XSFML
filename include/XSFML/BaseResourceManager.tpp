#include <sstream>

#include "BaseResourceManager.h"
#include "Util.h"
#include "Exception.h"

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
            resources[name].ptr = getRawResource(resource.path);
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
            auto &ptr = resources[name].ptr;
            delete ptr;
            ptr = nullptr;
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

    template<typename RawResourceType, typename ResourceHandler>
    void BaseResourceManager<RawResourceType, ResourceHandler>::loadConfigFile(const std::string &configFileName) {
        // open file
        auto fileStream = openFile(configFileName);
        if (!fileStream.is_open())
            throw ResourceLoadingException(configFileName);

        // turn format errors to exceptions
        fileStream.exceptions();

        // read resource lists
        std::string loadTimeStr;
        std::string filePath;
        std::string name;

        try {
            while (fileStream >> loadTimeStr >> filePath) {
                name = extractResourceName(filePath);
                resources[name] = Resource(name, filePath, loadTimeStr);
            }
        } catch (std::ios_base::failure &failure) {
            throw BadConfigFileException();
        }
    }

    template<typename RawResourceType, typename ResourceHandler>
    void BaseResourceManager<RawResourceType, ResourceHandler>::loadAutoResources() {
        NameContainer list;
        for (auto &iter: resources)
            if (iter.second.loadTime == ResourceLoadTime::AUTO)
                list.push_back(iter.second.name);
        loadMultiple(list);
    }

    template<typename RawResourceType, typename ResourceHandler>
    BaseResourceManager<RawResourceType, ResourceHandler>::Container<ResourceHandler>
    BaseResourceManager<RawResourceType, ResourceHandler>::getMultipleRawResource(
            const BaseResourceManager::NameContainer &fileNameContainer) {
        BaseResourceManager<RawResourceType, ResourceHandler>::Container<ResourceHandler> container;
        for (auto &fileName: fileNameContainer)
            container.push_back(get(fileName));
        return container;
    }

    template<typename RawResourceType, typename ResourceHandler>
    BaseResourceManager<RawResourceType, ResourceHandler>::Resource::Resource()
            : name(), path(), loadTime(ResourceLoadTime::ERROR), ptr(nullptr) {}

    template<typename RawResourceType, typename ResourceHandler>
    BaseResourceManager<RawResourceType, ResourceHandler>::Resource::Resource(
            const std::string &name, const std::string &path, const std::string &loadTimeStr)
            : name(name), path(path), loadTime(loadTimeConvert[loadTimeStr]), ptr(nullptr) {
        if (loadTime == ResourceLoadTime::ERROR)
            throw BadConfigFileException();
    }

    template<typename RawResourceType, typename ResourceHandler>
    typename BaseResourceManager<RawResourceType, ResourceHandler>::Resource &
    BaseResourceManager<RawResourceType, ResourceHandler>::Resource::operator=(
            BaseResourceManager<RawResourceType, ResourceHandler>::Resource &&resource) noexcept {
        name = std::move(resource.name);
        path = std::move(resource.path);
        loadTime = resource.loadTime;
        ptr = resource.ptr;
        resource.ptr = nullptr;
        return *this;
    }
}