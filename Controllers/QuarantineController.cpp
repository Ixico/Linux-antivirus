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
#include <openssl/sha.h>
#include "../Headers/FileHasher.h"

using std::filesystem::path;
using std::string;

void QuarantineController::imposeQuarantine(path file_path) {
    if(!exists(file_path)) throw std::invalid_argument("File not found!");//check if file exists
    if(!std::filesystem::is_regular_file(file_path)) throw std::invalid_argument("File is not regular!");
    std::string file_name = file_path.stem();//get file name
    std::filesystem::path destination_path = QUARANTINE_PATH + file_name;//create new path
    std::cout <<"impose: " << calculateFileHash(file_path) << std::endl;
    quarantine_records.push_back(QuarantineRecord(file_path, calculateFileHash(file_path)));//save source path and hash
    useCipher(file_path,destination_path);//encrypt file
    std::filesystem::remove(file_path);//remove from current location
}

bool QuarantineController::removeQuarantine(std::string file_name) {
    int position = 0;
    bool found = false;
    for (const auto &item : quarantine_records){
        if (item.file_path.stem() == file_name){
            found = true;
            break;
        }
        position++;
    }
    if (!found) throw std::invalid_argument("File is not on quarantine!");
    QuarantineRecord record = quarantine_records.at(position);
    useCipher(QUARANTINE_PATH+file_name,record.file_path);
    std::cout << "remove: " << calculateFileHash(record.file_path) << std::endl;
    std::cout << "remove: " << record.digest << std::endl;
    if (calculateFileHash(record.file_path) == record.digest) {
        std::filesystem::remove(QUARANTINE_PATH+file_name);
        quarantine_records.erase(quarantine_records.begin() + position);
        return true;
    }
    std::filesystem::remove(record.file_path);
    return false;
}





void QuarantineController::useCipher(path file_path, path destination_path) {
    int bytes_read, bytes_written;
    unsigned char indata[AES_BLOCK_SIZE];
    unsigned char outdata[AES_BLOCK_SIZE];


    unsigned char hash[SHA256_DIGEST_LENGTH];
    unsigned char *prepared = new unsigned char[password.length()]; //dobra alokacja?
    strcpy(reinterpret_cast<char *>(prepared), password.c_str()); //czy to rzutowanie jest dobre?
    SHA256(prepared,password.length(),hash);
    unsigned char ckey[16];
    unsigned char ivec[16];
    std::copy(std::begin(hash),std::begin(hash)+16,ckey);
    std::copy(std::begin(hash)+16,std::end(hash),ivec);

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
    fclose(ifp);
    fclose(ofp);
}



void QuarantineController::saveQuarantineRecords() {
    ::saveQuarantineRecords(quarantine_records);

}

//TODO: set 0 permissions
QuarantineController::QuarantineController(const string &password) : password(password) {
    std::filesystem::create_directories(QUARANTINE_PATH);
    if (std::filesystem::exists(QUARANTINE_LIST_PATH))
        quarantine_records = readQuarantineRecords();
}



