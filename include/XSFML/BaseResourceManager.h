#ifndef XSFML_BASERESOURSEMANAGER_H
#define XSFML_BASERESOURSEMANAGER_H

#include <bits/unique_ptr.h>
#include <functional>
#include <string>
#include <unordered_map>
#include <vector>

namespace xsf {
    /**
     * @brief Enum class indicates when to load a resource
     * @details There are 2 classes:
     *      - Automatic:
     *          + loaded to memory at when resource manager is created
     *          + unloaded when resource manager is destroyed
     *          + most common resources: GUI, etc
     *      - Manual:
     *          + loaded with load method of Resource Manager
     *          + unloaded with unload method
     *          + resources for a specific level: map, background, etc
     * Error: default value, for error checking
     */
    enum class ResourceLoadTime {
        ERROR, AUTO, MANUAL
    };

    /**
     * @brief exception thrown when given resource name is not in config file
     */
    class BadResourceNameException : public std::runtime_error {
    public:
        explicit BadResourceNameException(const std::string &resourceName)
                : runtime_error(resourceName + " is an invalid resource name") {}
    };

    /**
     * @brief exception thrown when an error happen while loading resource to memory
     */
    class ResourceLoadingException : public std::runtime_error {
    public:
        explicit ResourceLoadingException(const std::string &fileName)
                : runtime_error("Cannot open file " + fileName) {}
    };

    /**
     * @brief exception thrown when client code request for a resource that has not been loaded
     */
    class ResourceNotLoadedException : public std::runtime_error {
    public:
        explicit ResourceNotLoadedException(const std::string &resourceName)
                : runtime_error("Resource " + resourceName + " has not been loaded") {}
    };

    /**
     * @brief exception thrown when client code request for a resource that has not been loaded
     */
    class BadConfigFileException : public std::runtime_error {
    public:
        explicit BadConfigFileException()
                : runtime_error("Config file is corrupted") {}
    };

    /**
     * @brief Base class for other resource managers
     * @tparam RawResourceType: type of resource: sf::Texture, sf::Audio
     */
    template<typename RawResourceType, typename ResourceHandler>
    class BaseResourceManager {

    public:
        template<typename T>
        using Container = std::vector<T>;
        using NameContainer = Container<std::string>;
        using ResourcePtr = std::unique_ptr<RawResourceType>;

        /**
         * @param configFileName: relative file path of config file with respect to the client code executable
         */
        explicit BaseResourceManager(const std::string &configFileName);

        virtual ~BaseResourceManager();

        /**
         * @brief load resource with given name to \resources container
         * @param name: name of resource
         * @return 1  if resource has just been loaded
         *         0  if resource has already been loaded before
         */
        int load(const std::string &name);

        /**
         * @brief load resources with names in container to \resources container
         * @param container: contains names of resources
         * @return number of resources have just been loaded with this function call
         */
        int loadMultiple(const NameContainer &container);

        /**
        * @brief unload resource with given name from \resources container
        * @param name: name of resource
        * @return 1  if the resource has just been unloaded
        *         0  if the resource has already been unloaded
        */
        int unload(const std::string &name);

        /**
         * @brief unload resources with names in container from \resources container
         * @param container: contains names of resources
         * @return number of resources unloaded with this function call
         */
        int unloadMultiple(const NameContainer &container);

        /**
         * @brief get handler of the resource of given name
         * @param name: name of resource
         * @return handler of resource
         */
        virtual ResourceHandler get(const std::string &name) = 0;

    protected:
        /**
         * @brief read config file and save resources data to \resourceInfo
         *        config file structure: each resource is described with one line
         *        [AUTO/MANUAL] [resource_name] [file_path]
         *        resource_name and file_path must not contain space
         * @param configFileName: relative file path of config file with respect to the client code executable
         */
        virtual void loadConfigFile(const std::string &configFileName);

        /**
         * @brief load all resources with AUTO load time listed in resourceInfo
         */
        virtual void loadAutoResources();

        /**
         * @brief open resource file, load to memory
         * @param fileName: resource file name
         * @return unique_ptr of resource
         */
        virtual ResourcePtr getRawResource(const std::string &fileName) = 0;

        /**
         * @brief load multiple resources at once
         * @param fileNameContainer: container of resource file names
         * @return container of unique_ptr of resource
         */
        Container<ResourceHandler> getMultipleRawResource(const NameContainer &fileNameContainer);

        /**
         * @brief structure to hold resource info and ptr to actual data
         */
        struct Resource {
            /**
             * Default constructor
             * name = path = ""
             * loadTime = ERROR
             */
            Resource();

            Resource(const std::string &name, const std::string &path, const std::string &loadTimeStr);

            /**
             * @brief check whether resource has been loaded
             * @return true if loaded
             */
            bool isLoaded() { return (bool) ptr; };

            std::string name;             /** name of resource */
            std::string path;             /** file path to the resource*/
            ResourceLoadTime loadTime;    /** indicate when to load resource*/
            ResourcePtr ptr;              /** pointer to actual resource*/
        };

        std::unordered_map<std::string, Resource> resources;         /** maps resource name to resource obj */
    };
}

#include "BaseResourceManager.tpp" // include actual implementation of this template class

#endif //XSFML_BASERESOURSEMANAGER_H
