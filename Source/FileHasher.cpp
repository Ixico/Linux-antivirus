//
// Created by ixico on 17.03.2022.
//

#include "../Headers/FileHasher.h"
#include "../Headers/FileHasher.h"
#include <iostream>
#include <openssl/md5.h>
#include <sstream>
#include <cstring>
#include <iomanip>
#include <fstream>
#include "../Headers/FileManager.h"

using std::string;
extern const int MD5_LENGTH;



string hashToHexString(unsigned char *digest){
    std::stringstream ss;
    ss << std::hex << std::setfill('0');
    for (int i=0; i < MD5_LENGTH; i++){
        ss << std::setw(2) << static_cast<unsigned>(digest[i]);
    }
    return ss.str();
}
unsigned char * prepareContent(string content){
    //TODO: moze zamienic?
    unsigned char *prepared = new unsigned char[content.length()+1]; //dobra alokacja?
    strcpy(reinterpret_cast<char *>(prepared), content.c_str()); //czy to rzutowanie jest dobre? na const unsigned
    return prepared;
}


string calculateFileHash(string file_name){
    unsigned char digest[MD5_LENGTH];

    const string file_content = readFileToString(file_name);
    const int content_length = file_content.length();
    const unsigned char * prepared_content = prepareContent(file_content);

    MD5(prepared_content, content_length,digest);//FIXME: to zly pomysl, podziel na kawalki, pomysl na jakie (zalecenia)
    delete[](prepared_content); // dobre zarzadzanie pamiecia?

    return hashToHexString(digest);
}

string calculatePartially(string file_name){
    MD5_CTX ctx;
    MD5_Init(&ctx);

    std::ifstream is(file_name);
    char buf[4096];
    do {
        is.read(buf, sizeof(buf));
        MD5_Update(&ctx, buf, is.gcount());
    } while(is);
    unsigned char digest[MD5_LENGTH];
    MD5_Final(digest, &ctx);
    return hashToHexString(digest);
}
