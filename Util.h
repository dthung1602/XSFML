//
// Created by hung on 24/04/18.
//

#ifndef XSFML_UTIL_H
#define XSFML_UTIL_H

#include <string>
#include <fstream>

namespace xsf {
    std::string getPath();

    std::fstream openFile(const std::string &fileName);
}


#endif //XSFML_UTIL_H
