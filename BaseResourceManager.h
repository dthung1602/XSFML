//
// Created by hung on 24/04/18.
//

#ifndef XSFML_BASERESOURSEMANAGER_H
#define XSFML_BASERESOURSEMANAGER_H

#include <string>
#include <unordered_map>
#include <bits/shared_ptr.h>
#include <vector>

namespace xsf {
    enum class ResourceLoadTime {
        ERROR, START_UP, MANUAL, ON_DEMAND
    };

    template<typename ResourceType>
    class BaseResourceManager {

        using ResourcePtr = std::shared_ptr<ResourceType>;
        using ResourceWPtr = std::weak_ptr<ResourceType>;
        template <typename T>
        using Container = std::vector<T>;
        using NameContainer = Container<std::string>;

    public:

        explicit BaseResourceManager(const std::string &configFileName);

        virtual ~BaseResourceManager();

        bool load(const std::string &name);

        bool loadMultiple(const NameContainer &container);

        ResourcePtr getResource(const std::string &name);

    protected:

        virtual void loadConfigFile(const std::string &configFileName);

        virtual void loadStartUpResources();

        virtual ResourcePtr getRawResource(const std::string &fileName) = 0;

        Container<ResourcePtr> getMultipleRawResource(const NameContainer &fileNameContainer);

        struct ResourceInfo {
            ResourceInfo();

            ResourceInfo(std::string name, std::string path, std::string loadTimeStr);

            std::string name;
            std::string path;
            ResourceLoadTime loadTime;
        };

        std::unordered_map<std::string, ResourceInfo> resourceInfo;

        std::unordered_map<std::string, ResourcePtr> longLiveResourcePtrs;
        std::unordered_map<std::string, ResourceWPtr> onDemandResourcePtrs;
    };
}

#include "BaseResourceManager.tpp"

#endif //XSFML_BASERESOURSEMANAGER_H
