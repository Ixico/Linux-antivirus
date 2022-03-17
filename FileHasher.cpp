//
// Created by ixico on 17.03.2022.
//

#include "FileHasher.h"
#include "FileHasher.h"
#include <iostream>
#include <openssl/md5.h>
#include <sstream>
#include <cstring>
#include "FileManager.h"

using std::string;
extern const int MD5_LENGTH;



string hashToHexString(unsigned char *digest){
    std::stringstream ss;
    for (int i=0; i < MD5_LENGTH; i++){
        ss << std::hex << (int)digest[i];
    }
    return ss.str();
}
unsigned char * prepareContent(string content){
    //TODO: moze zamienic?
    unsigned char *prepared = new unsigned char[content.length()+1]; //dobra alokacja?
    strcpy(reinterpret_cast<char *>(prepared), content.c_str()); //czy to rzutowanie jest dobre?
    return prepared;
}


string calculateFileHash(string file_name){
    unsigned char digest[MD5_LENGTH];

    const string file_content = readFile(file_name);
    const int content_length = file_content.length();
    const unsigned char * prepared_content = prepareContent(file_content);

    MD5(prepared_content, content_length,digest);

    delete[](prepared_content); // dobre zarzadzanie pamiecia?

    return hashToHexString(digest);
}

