//
// Created by ixico on 17.03.2022.
//

#ifndef ANTIVIRUS_FILECONTROLLER_H
#define ANTIVIRUS_FILECONTROLLER_H
#include <iostream>
#include <unordered_set>
#include <vector>

class FileController {
public:
     explicit FileController(std::string database_path);
     bool isFileDangerous(std::string file_name);
     std::vector<std::string> findDangerousFiles(std::string directory_path);

private:
    std::unordered_set <std::string> hashes;
};
#endif //ANTIVIRUS_FILECONTROLLER_H
