//
// Created by ixico on 17.03.2022.
//

#include "../Headers/FileController.h"
#include "../Headers/FileManager.h"
#include "../Headers/FileHasher.h"
#include <iostream>
#include <vector>
#include <filesystem>

using std::string;
using std::unordered_set;
using std::vector;
using std::filesystem::path;
unordered_set <std::string> hashes;

bool FileController::isFileDangerous(path file_path) {
    if (!std::filesystem::is_regular_file(file_path)) throw std::invalid_argument("File is not regular one!");
    string digest = calculateFileHash(file_path);
    return hashes.find(digest) != hashes.end();
}

vector<path> FileController::findDangerousFiles(path directory_path){
    vector<path> files = findFilesInDirectory(directory_path);
    vector<path> dangerous_files;
    for (const auto &file : files){
        if (isFileDangerous(file)) dangerous_files.push_back(file);
    }
    return dangerous_files;
}

FileController::FileController(path database_path) {
    hashes = readDatabaseRecords(database_path);
}
