//
// Created by ixico on 17.03.2022.
//
#include <iostream>
#include <unordered_set>
#include <vector>

#ifndef ANTIVIRUS_FILEMANAGER_H
#define ANTIVIRUS_FILEMANAGER_H

std::string readFileToString(std::string);
std::unordered_set <std::string> readFileLines(std::string);
std::vector<std::string> findFilesInDirectory(std::string);
#endif //ANTIVIRUS_FILEMANAGER_H
