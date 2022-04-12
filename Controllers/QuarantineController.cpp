//
// Created by ixico on 23.03.2022.
//

#include "../Headers/QuarantineController.h"
#include "openssl/aes.h"
#include <filesystem>
#include <openssl/rand.h>
#include <fstream>
#include <cstring>
#include "../Headers/FileManager.h"

using std::filesystem::path;
extern const path QUARANTINE_PATH;


void QuarantineController::imposeQuarantine(path file_path) {
    if(!exists(file_path)) throw std::invalid_argument("File not found!");
    std::string file_name = file_path.stem();
    std::filesystem::path destination_path = QUARANTINE_PATH/file_name;
//    QuarantineRecord record = encrypt(file_path,destination_path);
//    quarantineRecords.push_back(record);
    std::filesystem::remove(file_path);
}

void QuarantineController::useCipher(path file_path, path destination_path) {
    int bytes_read, bytes_written;
    unsigned char indata[AES_BLOCK_SIZE];
    unsigned char outdata[AES_BLOCK_SIZE];

    unsigned char ckey[] = "thisisverybadkey";
//    RAND_bytes(ckey, sizeof(ckey));

    unsigned char ivec[] = "dontusethisinput";
//    RAND_bytes(ivec, sizeof(ivec));

    AES_KEY key;
    AES_set_encrypt_key(ckey, 128, &key);

    std::cout << ckey << std::endl;
    std::cout << ivec << std::endl;
    int num = 0;
    std::cout << file_path.c_str();
    std::cout << destination_path.c_str();
    FILE *ifp = fopen(file_path.c_str(), "rb");
    FILE *ofp = fopen(destination_path.c_str(), "wb");

    while (1) {
        bytes_read = fread(indata, 1, AES_BLOCK_SIZE, ifp);
        AES_cfb128_encrypt(indata, outdata, bytes_read, &key, ivec, &num,
                           AES_ENCRYPT);

        bytes_written = fwrite(outdata, 1, bytes_read, ofp);
        if (bytes_read < AES_BLOCK_SIZE)
            break;

    }
}


//TODO: set 0 permissions
QuarantineController::QuarantineController() {
    std::filesystem::create_directories(QUARANTINE_PATH);
    quarantineRecords = readQuarantineRecords();
}

void QuarantineController::removeQuarantine(std::string file_name) {
    int position = 0;
    for (const auto &item : quarantineRecords){
        if (item.file_path.stem() == file_name)
            break;
        position++;
    }
    QuarantineRecord temp = quarantineRecords.at(position);
    quarantineRecords.erase(quarantineRecords.begin() + position);

}

std::string QuarantineController::convertToString(unsigned char* a, int size)
{
    int i;
    std::string s;
    for (i = 0; i < size; i++) {
        s.push_back(a[i]);
    }
    return s;
}

