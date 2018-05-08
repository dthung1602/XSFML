#include "XSFML/Util.h"

/**
 *      Platform independent code
 */

namespace xsf {

    std::fstream openFile(const std::string &fileName) {
        return std::fstream(getPath() + "/" + fileName);
    }


    std::string extractResourceName(const std::string &fileName) {
        std::string tmp = fileName;

        // replace \ in window by /
        for (auto &c : tmp)
            if (c == '\\') c = '/';

        // find / and .
        auto lastSlash = tmp.rfind('/') + 1;
        auto lastDot = tmp.rfind('.');

        if (lastDot == -1)
            lastDot = tmp.size();

        return tmp.substr(lastSlash, lastDot - lastSlash);
    }

}

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


