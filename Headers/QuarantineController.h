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

    QuarantineController(const std::string &password);

    void imposeQuarantine(std::filesystem::path file_path);
    //TODO: to be considered
    bool removeQuarantine(std::string file_name);
    void saveQuarantineRecords();
    void useCipher(std::filesystem::path file_path, std::filesystem::path destination_path);
private:
    std::vector<QuarantineRecord> quarantine_records;
    const int AES_BLOCK_SIZE = 16;
    std::string password;
};


#endif //ANTIVIRUS_QUARANTINECONTROLLER_H
