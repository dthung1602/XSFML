//
// Created by hung on 04/05/18.
//

#ifndef XSFML_EXCEPTION_H
#define XSFML_EXCEPTION_H

#include <stdexcept>

/**
 * @brief base exception class
 */
class ResourceManagerException : public std::runtime_error {
public:
    explicit ResourceManagerException(const std::string &error)
            : std::runtime_error(error) {}
};

/**
 * @brief exception thrown when given resource name is not in config file
 */
class BadResourceNameException : public ResourceManagerException {
public:
    explicit BadResourceNameException(const std::string &resourceName)
            : ResourceManagerException(resourceName + " is an invalid resource name") {}
};

/**
 * @brief exception thrown when an error happen while loading resource to memory
 */
class ResourceLoadingException : public ResourceManagerException {
public:
    explicit ResourceLoadingException(const std::string &fileName)
            : ResourceManagerException("Cannot open file " + fileName) {}
};

/**
 * @brief exception thrown when client code request for a resource that has not been loaded
 */
class ResourceNotLoadedException : public ResourceManagerException {
public:
    explicit ResourceNotLoadedException(const std::string &resourceName)
            : ResourceManagerException("Resource " + resourceName + " has not been loaded") {}
};

/**
 * @brief exception thrown when client code request for a resource that has not been loaded
 */
class BadConfigFileException : public ResourceManagerException {
public:
    explicit BadConfigFileException()
            : ResourceManagerException("Config file is corrupted") {}
};

#endif //XSFML_EXCEPTION_H
