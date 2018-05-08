#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include "XSFML/SoundManager.h"

using namespace std;
using namespace sf;
using namespace xsf;

void wait(long sec = 2) {
    this_thread::sleep_for(chrono::milliseconds(sec * 1000));
}

void playAll(vector<Sound> sounds) {
    cout << sounds.size() << " SOUND OBJECTs" << endl;
    wait(3);
    for (auto &sound: sounds) {
        sound.play();
        wait();
    }
}

int main() {
    /*
     * RESULT
     *
     * 2 sounds should be heard
     * 2 SOUND OBJECTs
     * bad file name caught
     * file not loaded caught
     * 2
     * 4 sounds should be heard
     * 4 SOUND OBJECTs
     * 1
     * 3 sounds should be heard
     * 4 SOUND OBJECTs
     * 2
     * 1 sounds should be heard
     * 4 SOUND OBJECTs
     * end of main
     *
     */

    SoundManager manager("../test/sound_manager/config.txt");
    // odd = manual, even = auto

    vector<Sound> sounds = {
            manager.get("sound2"),
            manager.get("sound4"),
    };
    cout << "2 sounds should be heard" << endl;
    playAll(sounds);

    // wrong file name
    try {
        auto sound = manager.get("abc");
    } catch (BadResourceNameException &e) {
        cout << "bad file name caught" << endl;
    }

    // not loaded
    try {
        auto sound = manager.get("sound1");
    } catch (ResourceNotLoadedException &e) {
        cout << "file not loaded caught" << endl;
    }

    // load multiple
    cout << manager.loadMultiple({"sound1", "sound3"}) << endl;

    sounds.push_back(manager.get("sound1"));
    sounds.push_back(manager.get("sound3"));
    cout << "4 sounds should be heard" << endl;
    playAll(sounds);

    // unload
    cout << manager.unload("sound1") << endl;
    cout << "3 sounds should be heard" << endl;
    playAll(sounds);

    // unload multiple
    cout << manager.unloadMultiple({"sound1", "sound2", "sound3"}) << endl;
    cout << "1 sounds should be heard" << endl;
    playAll(sounds);

    cout << "end of main" << endl;
    return 0;
}
