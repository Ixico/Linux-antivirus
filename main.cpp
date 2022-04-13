#include <iostream>
#include <vector>
#include <array>
#include "Headers/FileController.h"
#include "Headers/FileHasher.h"
#include <filesystem>
#include "Headers/QuarantineController.h"
#include "Headers/FileManager.h"
#include <unistd.h>

using std::string;
using std::cout;
using std::endl;
using std::vector;
using std::array;
using std::cerr;
using std::filesystem::path;


extern const int MD5_LENGTH = 16; //because its constant

//TODO change
//extern const path QUARANTINE_PATH = "/var/antivirus/quarantine/";
extern const path QUARANTINE_PATH = "/home/ixico/Desktop/antivirus/quarantino_test";
extern const path DATABASE_PATH = "/var/antivirus/database";
//extern const path QUARANTINE_LIST_PATH = "/var/antivirus/list";
extern const path QUARANTINE_LIST_PATH = "/home/ixico/Desktop/antivirus/quarantino_list";


int main(int argc, char* argcv[]) {
    QuarantineController quarantineController;
    quarantineController.useCipher("/home/ixico/Desktop/qtestdest","/home/ixico/Desktop/qtestgood","pogchamp");
    return 0;
}
