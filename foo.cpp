#include <iostream>
#include <unordered_map>
#include <memory>

using namespace std;

int main() {
    shared_ptr<int> s(new int);
    shared_ptr<int> t(new int);
    shared_ptr<int> u(new int);

    unordered_map<int, weak_ptr<int>> map = {
            {1, weak_ptr<int>(s)},
            {2, weak_ptr<int>(t)},
            {3, weak_ptr<int>(u)}
    };

    for(auto &iter : map) {
        cout << iter.first << endl;
    }

    cout << boolalpha << map[1].expired() << endl;
    cout << boolalpha << map[0].expired() << endl;
    return 0;
}