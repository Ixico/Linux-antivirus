//
// Created by ixico on 17.03.2022.
//

#ifndef ANTIVIRUS_HASHESDATABASE_H
#define ANTIVIRUS_HASHESDATABASE_H
#include <iostream>
#include <unordered_set>

class HashesDatabase {
public:
     explicit HashesDatabase(std::string file_path);
     bool isInDatabase(std::string digest);

private:
    std::unordered_set <std::string> hashes;
};
#endif //ANTIVIRUS_HASHESDATABASE_H
