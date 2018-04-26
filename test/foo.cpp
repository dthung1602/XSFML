#include <iostream>
#include <unordered_map>
#include <memory>

//#include "XSFML/BaseResourceManager.h"
//#include "XSFML/Util.h"

using namespace std;

class Foo {
public:
    Foo() { cout << "begin" << endl; }

    ~Foo() { cout << "end" << endl; }
};

int main() {
    auto s = new Foo();
    unique_ptr<Foo> foo{s};
    foo.reset();
    cout << "hello" << endl;
    return 0;
}