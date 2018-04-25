//
// Created by hung on 24/04/18.
//

#include "XSFML/Util.h"

/**
 *      Platform independent code
 */


/**
 *      Platform - dependent code
 */

#ifdef _WIN64

#include <window.h>

namespace xsf {
    std::string getPath() {
        HMODULE hModule = GetModuleHandleW(NULL);
        WCHAR path[MAX_PATH];
        GetModuleFileNameW(hModule, path, MAX_PATH);
        return std::string(path);
    }
}

#elif _WIN32

#include <window.h>

namespace xsf {
    std::string getPath() {
        HMODULE hModule = GetModuleHandleW(NULL);
        WCHAR path[MAX_PATH];
        GetModuleFileNameW(hModule, path, MAX_PATH);
        return std::string(path);
    }
}

#elif __APPLE__
#error No apple support yet
#elif __linux

#include <zconf.h>
#include <libgen.h>

namespace xsf {
    std::string getPath() {
        char buf[PATH_MAX + 1];
        if (readlink("/proc/self/exe", buf, sizeof(buf) - 1) == -1)
            throw std::runtime_error("Cannot open config file");
        return dirname(buf);
    }
}

#endif


