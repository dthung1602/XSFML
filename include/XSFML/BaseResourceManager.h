#ifndef XSFML_BASERESOURSEMANAGER_H
#define XSFML_BASERESOURSEMANAGER_H

#include <bits/shared_ptr.h>
#include <string>
#include <unordered_map>
#include <vector>

namespace xsf {
    /**
     * @brief Enum class indicates when to load a resource
     * @details There are 3 classes:
     *      - Start up:
     *          + loaded to memory at when resource manager is created
     *          + unloaded when resource manager is destroyed
     *          + most common resources: GUI, etc
     *          + store by share_ptr in \longLiveResourcePtrs
     *      - Manual:
     *          + loaded with load method of Resource Manager
     *          + unloaded with unload method
     *          + resources for a specific level: map, background, etc
     *          + store by share_ptr in \longLiveResourcePtrs
     *      - On demand:
     *          + loaded when first requested
     *          + unloaded when there's no share_ptr ref left
     *          + one time use resources
     *          + store by weak_ptr in \onDemandResourcePtrs
     * Error: default value, for error checking
     */
    enum class ResourceLoadTime {
        ERROR, START_UP, MANUAL, ON_DEMAND
    };

    /**
     * @brief Base class for other resource managers
     * @tparam ResourceType: type of resource: sf::Texture, sf::Audio
     */
    template<typename ResourceType>
    class BaseResourceManager {

        using ResourcePtr = std::shared_ptr<ResourceType>;
        using ResourceWPtr = std::weak_ptr<ResourceType>;
        template<typename T>
        using Container = std::vector<T>;
        using NameContainer = Container<std::string>;

    public:

        /**
         * @param configFileName: relative file path of config file with respect to the client code executable
         */
        explicit BaseResourceManager(const std::string &configFileName);

        virtual ~BaseResourceManager();

        /**
         * @brief load resource with given name to memory
         * @param name: name of resource
         * @return true on success, false otherwise
         *         note: on demand resource will NOT be loaded -> failure
         */
        bool load(const std::string &name);

        /**
         * @brief load resources with names in container to memory
         * @param container: contains names of resources
         * @return true if all resources are loaded, false otherwise
         */
        bool loadMultiple(const NameContainer &container);

        /**
         * @brief get resource of given name
         * @param name: name of resource
         * @return share_ptr of resource type
         */
        ResourcePtr getResource(const std::string &name);

    protected:
        /**
         * @brief read config file and save resources data to \resourceInfo
         *        file structure: each resource has one line
         *        [load time] [resource name] [file path]
         * @param configFileName: relative file path of config file with respect to the client code executable
         */
        virtual void loadConfigFile(const std::string &configFileName);

        /**
         * @brief load all resources with STARTUP load time listed in resourceInfo
         */
        virtual void loadStartUpResources();

        /**
         * @brief open resource file, load to dynamic memory and return ptr to it
         * @param fileName: resource file name
         * @return share_ptr of resource
         */
        virtual ResourcePtr getRawResource(const std::string &fileName) = 0;

        /**
         * @brief open resource files, load to dynamic memory and return ptr to them
         * @param fileNameContainer: container of resource file names
         * @return container of share_ptr of resource
         */
        Container<ResourcePtr> getMultipleRawResource(const NameContainer &fileNameContainer);

        /**
         * @brief structure to hold resource info
         */
        struct ResourceInfo {
            /**
             * Default constructor
             * name = path = empty string
             * loadTime = ERROR
             */
            ResourceInfo();

            ResourceInfo(std::string name, std::string path, std::string loadTimeStr);

            std::string name;             /** name of resource */
            std::string path;             /** file path to the resource*/
            ResourceLoadTime loadTime;    /** indicate when to load resource*/
        };

        std::unordered_map<std::string, ResourceInfo> resourceInfo;         /** maps resource name to resource info obj */

        std::unordered_map<std::string, ResourcePtr> longLiveResourcePtrs;  /** maps resource name to resource share ptr */
        std::unordered_map<std::string, ResourceWPtr> onDemandResourcePtrs; /** maps resource name to resource weak ptr */
    };
}

#include "BaseResourceManager.tpp" // include actual implementation of this template class

#endif //XSFML_BASERESOURSEMANAGER_H
