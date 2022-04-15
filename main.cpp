#include <iostream>
#include <vector>
#include <array>
#include "Headers/FileController.h"
#include "Headers/FileHasher.h"
#include <filesystem>
#include "Headers/QuarantineController.h"
#include "Headers/FileManager.h"
#include <unistd.h>
#include "Headers/CLIController.h"

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
    CLIController cli_controller;
    FileController file_controller;
    QuarantineController quarantine_controller;
//    cout << getlogin();
    try {
        file_controller.init();
        quarantine_controller.init();
    } catch (std::exception &e){
        cli_controller.printInitFailure();
        return EXIT_FAILURE;
    }

    if (argc == 1) {
        cli_controller.printWelcomePage();
        return EXIT_SUCCESS;
    }

    if (argcv[1] == string("-scanf")){
        //print sth
        if (argc != 3) return EXIT_FAILURE;
        path file_path = argcv[2];
        try {
            file_controller.isFileDangerous(file_path) ? cli_controller.printDangerous() : cli_controller.printSafe();
        } catch (std::exception &e) {

        }
    }

    if (argcv[1] == string("-scand")){
        //print sth
        if (argc != 3) return EXIT_FAILURE;
        path directory_path = argcv[2];
        try {
            vector<path> dangerous;
            dangerous = file_controller.findDangerousFiles(directory_path);
            cli_controller.printDangerous(dangerous);
        } catch (std::exception &e) {

        }
    }

    else if (argcv[1] == string("-quarantine")){

    }

    else if (argcv[1] == string("-restore")){

    }

    else {
        //print sth
        return EXIT_FAILURE;
    }
    cli_controller.printHelp();


    return 0;
}
