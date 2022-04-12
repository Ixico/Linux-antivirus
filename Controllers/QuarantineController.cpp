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
#include "../Headers/ConfigurationVariables.h"

using std::filesystem::path;


void QuarantineController::imposeQuarantine(path file_path) {
    if(!exists(file_path)) throw std::invalid_argument("File not found!");//check if file exists
    std::string file_name = file_path.stem();//get file name
    std::filesystem::path destination_path = QUARANTINE_PATH + file_name;//create new path
    useCipher(file_path,destination_path);//encrypt file
    std::filesystem::remove(file_path);//remove from current location
    quarantine_records.push_back(file_path);//save source path
}

void QuarantineController::removeQuarantine(std::string file_name) {
    int position = 0;
    bool found = false;
    for (const auto &item : quarantine_records){
        if (item.stem() == file_name){
            found = true;
            break;
        }
        position++;
    }
    if (!found) throw std::invalid_argument("File is not on quarantine!");
    path destination = quarantine_records.at(position);
    useCipher(QUARANTINE_PATH+file_name,destination);
    std::filesystem::remove(QUARANTINE_PATH+file_name);
    quarantine_records.erase(quarantine_records.begin() + position);
}





void QuarantineController::useCipher(path file_path, path destination_path) {
    int bytes_read, bytes_written;
    unsigned char indata[AES_BLOCK_SIZE];
    unsigned char outdata[AES_BLOCK_SIZE];

    unsigned char ckey[] = KEY;
//    RAND_bytes(ckey, sizeof(ckey));

    unsigned char ivec[] = IV;
//    RAND_bytes(ivec, sizeof(ivec));

    AES_KEY key;
    AES_set_encrypt_key(ckey, 128, &key);

    int num = 0;
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
    if (std::filesystem::exists(QUARANTINE_LIST_PATH))
        quarantine_records = readQuarantinePaths();
}

void QuarantineController::saveQuarantineList() {
    saveQuarantinePaths(quarantine_records);

}



