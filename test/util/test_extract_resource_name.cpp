#include<iostream>
#include "XSFML/Util.h"

using namespace std;
using namespace xsf;

int main() {
    cout << extractResourceName("/sldf/asdf/as/df/file.name.agc") << endl;
    cout << extractResourceName("file.name.agc") << endl;
    cout << extractResourceName("/sldf/asdf/as/df/filenameagc") << endl;
    cout << extractResourceName("filenameagc") << endl;

    cout << extractResourceName(R"(\sldf\asdf\as\df\file.name.agc)") << endl;
    cout << extractResourceName("file.name.agc") << endl;
    cout << extractResourceName(R"(\sldf\asdf\as\df\filenameagc)") << endl;
    cout << extractResourceName("filenameagc") << endl;
    return 0;
}