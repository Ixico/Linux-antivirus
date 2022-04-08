#include <iostream>
#include <vector>
#include <array>
#include "Headers/FileController.h"
#include "Headers/FileHasher.h"
#include <filesystem>
#include <cstring>
#include <string.h>
#include "Headers/QuarantineController.h"

using std::string;
using std::cout;
using std::endl;
using std::vector;
using std::array;
using std::cerr;
using recursive_directory_iterator = std::filesystem::recursive_directory_iterator;


extern const int MD5_LENGTH = 16; //because its constant

int main(int argc, char* argcv[]) {
    FileController controller("../Resources/hash_database.txt");    //TODO: sprawdz, czy plik istnieje - jak rozdzielic deklaracje od inicjalizacji?
    //TODO: dodac rozpoznawanie inputu - sprawdzac czy directory
    if (argc != 3) {
        cerr << "Invalid number of arguments! Usage:" << endl << "./Antivirus [-f or -d] [file or directory name]"<<endl;
        return -1;
    } else if (string("-f") == argcv[1]) {
        string file_path = argcv[2];
        bool is_dangerous;
        try {
            is_dangerous = controller.isFileDangerous(file_path);
        } catch (std::invalid_argument &e) {
            cerr << e.what() << endl;
            return -2;
        }
        if (is_dangerous) cout << "Don't open the file. It may be dangerous for your system!" << endl;
        else cout << "File is considered to be safe." << endl;
    } else if (string("-d") == argcv[1]) {
        string directory_path = argcv[2];
        vector<string> detected = controller.findDangerousFiles(directory_path);
        for (const auto &file : detected){
            cout << file << endl;
        }
    } else {
        cerr << "Invalid specifier argument! Usage:" << endl << "./Antivirus [-f or -d] [file or directory name]"
             << endl;
        return -3;
    }
    cout << calculatePartially("../Resources/dangerous_file.txt") << endl;
    QuarantineController quarantineController("/home/ixico/Desktop/quarantino");
    quarantineController.init();
    return 0;
}
