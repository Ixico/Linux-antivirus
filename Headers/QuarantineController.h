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
    void init();
    void imposeQuarantine(std::filesystem::path file_path);
    bool removeQuarantine(std::string file_name);
    void saveQuarantineRecords();

    void setPassword(const std::string &password);

private:
    std::vector<QuarantineRecord> quarantine_records;
    const int AES_BLOCK_SIZE = 16;
    std::string password;
    void useCipher(std::filesystem::path file_path, std::filesystem::path destination_path);
};


#endif //ANTIVIRUS_QUARANTINECONTROLLER_H
