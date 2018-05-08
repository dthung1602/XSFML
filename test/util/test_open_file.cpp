#include<iostream>
#include "XSFML/Util.h"

using namespace std;
using namespace xsf;

int main() {
    cout << "------------------------------------" << endl;
    cout << getPath() << endl;
    auto f = openFile("../test/util/abc.txt");
    if (!f.is_open())
        exit(2);
    while (!f.eof()) {
        string s;
        f >> s;
        cout << s << " ";
    }
    return 0;
}