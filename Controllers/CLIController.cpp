//
// Created by ixico on 15.04.2022.
//

#include "../Headers/CLIController.h"
#include <iostream>
using std::cout;
using std::endl;

void CLIController::printWelcomePage() {
    cout << "Welcome in Linux Antivirus" << endl;
    cout << "Use -help flag for usage details:" << endl;
    cout << "./Antivirus -help" << endl;
}

void CLIController::printHelp() {
    cout << "Linux Antivirus man page" << endl;
    cout << "USAGE" << endl;
    cout << "./Antivirus -flag [argument]" << endl;
    cout << "FLAGS" << endl;
    cout << "-scan" << endl;
    cout << "-quarantine" << endl;
    cout << "-restore" << endl;
//    cout <<  << endl;

}

void CLIController::printDangerous() {
    cout << "This file my be dangerous!" << endl;
}

void CLIController::printSafe() {
    cout << "File is considered to be safe" << endl;
}

void CLIController::printInitFailure() {
    cout << "Initialization fatal error!" << endl;

}
