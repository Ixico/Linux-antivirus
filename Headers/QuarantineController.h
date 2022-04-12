//
// Created by ixico on 23.03.2022.
//

#ifndef ANTIVIRUS_QUARANTINECONTROLLER_H
#define ANTIVIRUS_QUARANTINECONTROLLER_H

#include <iostream>
#include <filesystem>
#include <vector>
#include "../QuarantineRecord.h"

class QuarantineController {
public:

    QuarantineController();

    void imposeQuarantine(std::filesystem::path file_path);
    //TODO: to be considered
    void removeQuarantine(std::string file_name);
    void useCipher(std::filesystem::path file_path, std::filesystem::path destination_path);
private:
    std::vector<QuarantineRecord> quarantineRecords;
    std::filesystem::path quarantine_path;
    const int AES_BLOCK_SIZE = 16;

    std::string convertToString(unsigned char* a, int size);

};


#endif //ANTIVIRUS_QUARANTINECONTROLLER_H
