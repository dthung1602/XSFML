#include<iostream>
#include <unordered_map>
using namespace std;

int main() {
    unordered_map<int, string> s = {
            {1, "s"},
            {3, "u"}
    };

    for (auto &iter : s)
        cout << iter.first << " -> " << iter.second << endl;
    return 0;
}