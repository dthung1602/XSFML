//
// Created by hung on 24/04/18.
//

#ifndef XSFML_BASERESOURSEMANAGER_H
#define XSFML_BASERESOURSEMANAGER_H

#include <string>
#include <unordered_map>
#include <bits/shared_ptr.h>

namespace xsf {

    template<typename ResourceType>
    class BaseResourceManager {

        using ResourcePtr = std::shared_ptr<ResourceType>;
        using ResourceWPtr = std::weak_ptr<ResourceType>;

    public:

        explicit BaseResourceManager(const std::string &configFileName);

        virtual ~BaseResourceManager();

        ResourcePtr getResource(const std::string &name);

        enum class ResourceLoadTime {
            ERROR, START_UP, MANUAL, ON_DEMAND
        };

    protected:

        virtual void loadConfigFile(const std::string &configFileName);

        virtual void loadStartUpResources();

        virtual ResourcePtr load(const std::string &fileName) = 0;

        template<typename Container>
        virtual Container loadMultiple(const Container &nameList);

        struct ResourceInfo {
            ResourceInfo() = default;

            ResourceInfo(std::string name, std::string path, std::string loadTimeStr);

            std::string name;
            std::string path;
            ResourceLoadTime loadTime;
        };

        std::unordered_map<std::string, ResourceInfo> types;

        std::unordered_map<std::string, ResourcePtr> longLiveResourcePtrs;
        std::unordered_map<std::string, ResourceWPtr> onDemandResourcePtrs;
    };
}

#include "BaseResourceManager.tpp"

#endif //XSFML_BASERESOURSEMANAGER_H
