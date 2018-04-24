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

    public:

        explicit BaseResourceManager(const std::string &configFileName);

        virtual ~BaseResourceManager();

        ResourcePtr getResource(const std::string &name);

    protected:

        virtual void loadConfigFile(const std::string &configFileName);

        virtual void loadStartUpResources();

        virtual ResourcePtr load(const std::string &fileName);

        template<typename Container>
        virtual Container loadMultiple(const Container &nameList);

        enum class ResourceLoadTime {
            START_UP, MANUAL, ON_DEMAND
        };

        std::unordered_map<std::string, ResourceLoadTime> types;

        std::unordered_map<std::string, ResourcePtr> startUpResources;
        std::unordered_map<std::string, ResourcePtr> manualResources;
        std::unordered_map<std::string, ResourcePtr> onDemandResources;
    };
}

#include "BaseResourceManager.tpp"

#endif //XSFML_BASERESOURSEMANAGER_H
