//
// Created by hung on 24/04/18.
//

#include "BaseResourceManager.h"

namespace xsf {
    template<typename ResourceType>
    BaseResourceManager<ResourceType>::BaseResourceManager(const std::string &configFileName) {

    }

    template<typename ResourceType>
    BaseResourceManager<ResourceType>::~BaseResourceManager() {

    }

    template<typename ResourceType>
    BaseResourceManager::ResourcePtr BaseResourceManager<ResourceType>::getResource(const std::string &name) {
        return xsf::BaseResourceManager::ResourcePtr();
    }

    template<typename ResourceType>
    void BaseResourceManager<ResourceType>::loadConfigFile(const std::string &configFileName) {

    }

    template<typename ResourceType>
    void BaseResourceManager<ResourceType>::loadStartUpResources() {

    }

    template<typename ResourceType>
    BaseResourceManager::ResourcePtr BaseResourceManager<ResourceType>::load(const std::string &fileName) {
        return xsf::BaseResourceManager::ResourcePtr();
    }

    template<typename ResourceType>
    template<typename Container>
    Container BaseResourceManager<ResourceType>::loadMultiple(const Container &nameList) {
        return nullptr;
    }
}