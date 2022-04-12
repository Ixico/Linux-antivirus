//
// Created by ixico on 10.04.2022.
//

#ifndef ANTIVIRUS_QUARANTINERECORD_H
#define ANTIVIRUS_QUARANTINERECORD_H

#include <iostream>
#include <filesystem>

class QuarantineRecord {
public:
    std::filesystem::path file_path;
    std::string key;
    std::string iv;

    friend std::ostream &operator<<(std::ostream &os, const QuarantineRecord &record) {
        os << "file_path: " << record.file_path << " key: " << record.key << " iv: " << record.iv;
        return os;
    }

    QuarantineRecord() {};

    QuarantineRecord(const std::filesystem::path &filePath, const std::string &key, const std::string &iv) : file_path(
            filePath), key(key), iv(iv) {}

private:

};


#endif //ANTIVIRUS_QUARANTINERECORD_H
