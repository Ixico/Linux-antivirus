#include <iostream>
#include <vector>
#include <array>
#include "FileHasher.h"
#include "HashesDatabase.h"
#include <filesystem>

using std::string;
using std::cout;
using std::endl;
using std::vector;
using std::array;
using std::cerr;
using recursive_directory_iterator = std::filesystem::recursive_directory_iterator;


extern const int MD5_LENGTH = 16; //because its constant

int main(int argc, char* argcv[]) {
    if (argc != 2) {
        cerr << "You need to specify exactly one argument - file name." << endl;
        return -1;
    }
    string file_path = argcv[1];
    try {
        cout << calculateFileHash(file_path) << endl;
    } catch (std::invalid_argument &e) {
        cerr << e.what();
    }
//    HashesDatabase database("hello");
    return 0;
}
