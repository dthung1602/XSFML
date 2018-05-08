//
// Created by hung on 24/04/18.
//

#ifndef XSFML_UTIL_H
#define XSFML_UTIL_H

#include <string>
#include <fstream>

namespace xsf {

    /**
     * @return absolute path of directory of the client executable
     */
    std::string getPath();

    /**
     * open a file
     * @param fileName: relative file path with respect to the client executable
     * @return a file stream, which may or may not opened, i.e. the success of this function is not checked
     */
    std::fstream openFile(const std::string &fileName);

    /**
     * extract resource name from its file path, i.e remove path & extension
     * @param fileName
     * @return
     */
    std::string extractResourceName(const std::string &fileName);

}


#endif //XSFML_UTIL_H
