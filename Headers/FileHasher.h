//
// Created by ixico on 17.03.2022.
//

#include <iostream>
#ifndef ANTIVIRUS_FILEHASHER_H
#define ANTIVIRUS_FILEHASHER_H

std::string calculateFileHash(std::string file_name);
std::string hashToHexString(unsigned char *digest);


#endif //ANTIVIRUS_FILEHASHER_H
