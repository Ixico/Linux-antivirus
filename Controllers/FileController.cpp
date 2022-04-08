//
// Created by ixico on 17.03.2022.
//

#include "../Headers/FileController.h"
#include "../Headers/FileManager.h"
#include "../Headers/FileHasher.h"
#include <iostream>
#include <vector>

using std::string;
using std::unordered_set;
using std::vector;
unordered_set <std::string> hashes;

bool FileController::isFileDangerous(string file_name) {
    string digest = calculateFileHash(file_name);
    return hashes.find(digest) != hashes.end();
}

vector<string> FileController::findDangerousFiles(string directory_path){
    vector<string> files = findFilesInDirectory(directory_path);
    vector<string> dangerous_files;
    for (const auto &file : files){
        if (isFileDangerous(file)) dangerous_files.push_back(file);
    }
    return dangerous_files;
}

FileController::FileController(std::string database_path) {
    hashes = readFileLines(database_path);
}
